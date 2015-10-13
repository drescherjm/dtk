/* @(#)dtkDistributedResourceManagerSlurm.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/10/12 11:32:00
 */

#include "dtkDistributedResourceManagerSlurm.h"

#include <dtkLog>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedResourceManagerSlurm implementation
// /////////////////////////////////////////////////////////////////

QByteArray  dtkDistributedResourceManagerSlurm::status(void)
{
    QProcess stats;
    QString data;
    QVariantMap result;
    QVariantList jnodes;
    QVariantList jjobs;
    QMap <QString, bool> nodes_map;
    result.insert("version", protocol());
    qlonglong globalcores = 0;

    dtkTrace() << "slurm status";

    stats.start("sinfo -o \"%13n %8t %4c %8z %8m %18P\"");
    if (!stats.waitForStarted()) {
        dtkError() << "Unable to launch sinfo command";
        return QByteArray();
    }
    if (!stats.waitForFinished()) {
        dtkError() << "Unable to completed sinfo command";
        return QByteArray();
    }

    data = stats.readAll();
    QTextStream stream(&data);
    QString line = stream.readLine(); // skip first line
// HOSTNAMES     STATE    CPUS S:C:T    MEMORY   PARTITION
// server        idle     1    1:1:1    1        debug*
    QRegExp rx("(\\w+)\\s+(\\w+)\\s+(\\d+)\\s+(\\d+):(\\d+):(\\d+)\\s+(\\d+)\\s+(\\S+)\\s*");
    do {
        line = stream.readLine();
        if (rx.exactMatch(line)) {
            QVariantMap node;
            QStringList list = rx.capturedTexts();
            QString name = list.at(1);
            QString state = list.at(2);
            int np   = list.at(3).toInt();
            int socket  = list.at(4).toInt();
            int core    = list.at(5).toInt();
            int threads = list.at(6).toInt();
            int mem     = list.at(7).toInt();
            QString partition = list.at(8);
            if (nodes_map.contains(name)) {
                continue;
            }
            node.insert("name", name);
            nodes_map.insert(name, true);
            QVariantList cores;

            for (int c = 0; c<np; c++) {
                QVariantMap core;
                // slurm doesn't define a unique id per core, so assigned
                // a unique number to each core of the cluster
                core.insert("id",globalcores +c);
                cores << core;
            }
            node.insert("cores", cores );
            node.insert("cpus", socket);
            node.insert("gpus", 0); // FIXME: does slurm support gpu ?
            node.insert("gpus_busy", 0);
//            node.insert("properties", QVAriantMap());

            // available states:
            //ALLOC, ALLOCATED, COMP, COMPLETING, DOWN, DRAIN, DRAINED, DRAINING, FAIL, FAILING, IDLE, MAINT, NO_RESPOND, POWER_SAVE, UNK, and UNKNOWN.
            if (state.contains("alloc") || state.contains("comp")) {
                state="busy";
                node.insert("cores_busy", np);
            } else if (state.contains("idle")) {
                state="free";
                node.insert("cores_busy", 0);
            } else if (state.contains("power_save")) {
                state="standby";
                node.insert("cores_busy", 0);
            } else {
                node.insert("cores_busy", 0);
                state="down";
            }
            node.insert("state", state);
            jnodes << node;
            result.insert("nodes", jnodes);
            globalcores += np;

        } else {
            dtkInfo() << "slurm sinfo: skip line" << line;
        }

    } while (!line.isNull());

    // Now get the jobs
    stats.close();
    stats.start("squeue -o \"%.18i %.9P %.8j %.8u %.2t %.10l %S %.6D %R %C\" " );
    if (!stats.waitForStarted()) {
        dtkError() << "Unable to launch squeue command";
        return QByteArray();
    }
    if (!stats.waitForFinished()) {
        dtkError() << "Unable to completed squeue command";
        return QByteArray();
    }

    data = stats.readAll();
    stream.setString(&data);
    line = stream.readLine(); // skip first line

    rx.setPattern("\\s*(\\d+)\\s+(\\w+)\\s+(\\w+)\\s+(\\w+)\\s+(\\S+)\\s+(\\S+)\\s+(\\S+)\\s+(\\d+)\\s+(\\S+)\\s+(\\d+)\\s*");
    do {
        line = stream.readLine();
        if (rx.exactMatch(line)) {
            QStringList list = rx.capturedTexts();
            qlonglong id = list.at(1).toLongLong();
            QString partition = list.at(2);
            QString jobname = list.at(3);
            QString user = list.at(4);
            QString status = list.at(5);
            QString walltime = list.at(6);
            QString stime = list.at(7);
            int nodes = list.at(8).toInt();
            QString nodenames = list.at(9);
            int cores = list.at(10).toInt();

            QVariantMap job;
            QVariantMap jresources;
            QString state;
            // PD  (pending),  R (running), CA (cancelled), CF(configuring), CG (completing), CD (completed), F (failed), TO (timeout), and NF (node failure)
            if (status ==  "R" ) {
                state = "running";
            } else if (status == "PD") {
                state = "queued";
            } else if (status == "") {
                state = "blocked";
            } else if ((status == "CD") || (status == "CG")) {
                state = "exiting";
            } else if (status == "") {
                state = "scheduled";
            } else {
                state = "unknown";
            };

            jresources.insert("nodes",nodes);
            jresources.insert("cores",cores);
            job.insert("id", id);
            job.insert("username", user);
            job.insert("queue", partition);
//            job.insert("queue_time", qtime);
            job.insert("start_time", stime);
            job.insert("walltime", walltime);
            job.insert("resources", jresources);
            job.insert("state", state);
            jjobs << job;
            result.insert("jobs", jjobs);
        } else {
            dtkInfo() << "slurm squeue: skip line" << line;
        }
    } while (!line.isNull());

    dtkTrace() << "slurm status: done" << result;
    return QJsonDocument(QJsonObject::fromVariantMap(result)).toJson();
}

QString dtkDistributedResourceManagerSlurm::submit(QString input)
{
    QString qsub = "sbatch ";

    /* format: {"resources": {"nodes": 0..N, "cores": 1..M },
                "properties": {{"key": "value"}, ...},
                "walltime": "hh:mm:ss",
                "script": "script_path" | "application": "app_args",
                "queue": "queuename";
                "options": "string"
                }
    */

    QJsonDocument jsonDoc = QJsonDocument::fromJson(input.toUtf8());

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        dtkWarn() << "Error while parsing JSON document: not a json object" << input;
        return QString("ERROR");
    }
    QVariantMap json = jsonDoc.object().toVariantMap();

    // FIXME: we should read the properties mapping from a file instead of hardcoding it
    // Everything here is specific to nef setup.
    QVariantMap jprops = json["properties"].toMap();
    QString properties ;
    //FIXME: not used

    QVariantMap res = json["resources"].toMap();
    if (res["nodes"].toInt() == 0) {
        // no nodes, only cores; TODO
    } else if (res["cores"].toInt() == 0) {
        // no cores, only nodes; TODO
    } else {
        qlonglong tasks = res["nodes"].toInt() * res["cores"].toInt();
        qsub += " --nodes="+res["nodes"].toString()+properties+" --tasks="+QString::number(tasks);
    }

    // walltime, syntax=HH:MM:SS
    if (json.contains("walltime")) {
        qsub += " --time="+json["walltime"].toString();
    }

    // script
    if (json.contains("script")) {
        qsub += " "+json["script"].toString();
    } else if (json.contains("application")) {

        QString scriptName = qApp->applicationDirPath() + "/dtkDistributedServerScript.sh";
        QFile script(scriptName);

        if (!script.open(QFile::WriteOnly|QFile::Truncate)) {
            dtkWarn() << "unable to open script for writing";
        } else {
            QTextStream out(&script);
            QString app_path = json["application"].toString();
            out << "#!/bin/bash\n";
            if (QFileInfo(app_path).isAbsolute()) {
                out << json["application"].toString();
            } else {
                out << qApp->applicationDirPath()
                    + "/"
                    + app_path;
            }
        }

        script.close();

        qsub += " " + scriptName;

    } else {
        dtkError() << "no script and no application";
        return QString("ERROR");
    }

    // queue
    // if (json.contains("queue")) {
    //     qsub += " -q "+json["queue"].toString();
    // }

    // options
    if (json.contains("options")) {
        qsub += " "+json["options"].toString();
    }

    dtkDebug() << qsub;
    QProcess stat; stat.start(qsub);

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch sbatch command";
        return QString("ERROR");
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to completed sbatch command";
        return QString("ERROR");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkError() << "Error running sbatch :" << error;
        return QString("ERROR");
    } else {
        QString jobid = stat.readAll();
        dtkDebug() << jobid;
        return jobid.split(".").at(0);
    }
}

QString dtkDistributedResourceManagerSlurm::deljob(QString jobid)
{
    QString qcancel = "scancel " + jobid;
    QProcess stat; stat.start(qcancel);

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch qcancel command";
        return QString("ERROR");
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to complete qcancel command";
        return QString("ERROR");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkError() << "Error running qcancel :" << error;
        return QString("ERROR");
    } else {
        QString msg = stat.readAll();
        dtkDebug() << msg;
        return QString("OK");
    }
}






