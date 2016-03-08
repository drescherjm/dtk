/* @(#)dtkDistributedResourceManagerOar.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 08:18:49
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributedResourceManagerOar.h"

#include <dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkDistributedResourceManagerOar implementation
// /////////////////////////////////////////////////////////////////

QString  dtkDistributedResourceManagerOar::submit(QString input)
{
    QString oarsub = "oarsub ";

    QJsonDocument jsonDoc = QJsonDocument::fromJson(input.toUtf8());

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        dtkWarn() << "Error while parsing JSON document: not a json object" << input;
        return QString("ERROR");
    }
    QVariantMap json = jsonDoc.object().toVariantMap();


    QVariantMap jprops = json["properties"].toMap();
    QString properties ;
    if (jprops.contains("cpu_model")) {
        properties +=  " -p \"cputype='"+jprops["cpu_model"].toString()+"'\"";
    } else if (jprops.count() > 0 ) {
        QVariantMap::const_iterator iter = jprops.begin();
        properties +=  " -p \""+iter.key()+"='"+iter.value().toString()+"'";
        iter++;
        for(;iter != jprops.end(); ++iter) {
            properties +=  " and "+iter.key()+"='"+iter.value().toString()+"'";
        }
        properties +=  "\"";
    }
    oarsub += properties;

    QVariantMap res = json["resources"].toMap();

    if (res["nodes"].toInt() == 0) {
        // no nodes, only cores;
        oarsub += " -l /core="+res["cores"].toString();
    } else if (res["cores"].toInt() == 0) {
        // no cores, only nodes;
        oarsub += " -l /nodes="+res["nodes"].toString();
    } else {
        oarsub += " -l /nodes="+res["nodes"].toString()+"/core="+res["cores"].toString();
    }

    // walltime, syntax=HH:MM:SS
    if (json.contains("walltime")) {
        oarsub += ",walltime="+json["walltime"].toString();
    }


    // script
    if (json.contains("script")) {
        oarsub += " "+json["script"].toString();
    } else if (json.contains("application")) {

        QString scriptName = qApp->applicationDirPath() + "/dtkDistributedServerScript.sh";
        QFile script(scriptName);

        if (!script.open(QFile::WriteOnly|QFile::Truncate)) {
            dtkWarn() << "unable to open script for writing";
        } else {
            script.setPermissions(QFile::ExeOwner|QFile::ReadOwner|QFile::WriteOwner);
            QTextStream out(&script);
            QString app_path = json["application"].toString();
            out << "#!/bin/bash\n";
            if (QFileInfo(app_path).isAbsolute()) {
                out << json["application"].toString();
            } else {
                out <<  qApp->applicationDirPath()
                    + "/"
                    + app_path;
            }
        }

        script.close();

        oarsub += " " + scriptName;

    } else {
        dtkError() << "no script and no application";
        return QString("ERROR");
    }

    // queue
    if (json.contains("queue")) {
        oarsub += " -q "+json["queue"].toString();
    }
    // options
    if (json.contains("options")) {
        oarsub += " "+json["options"].toString();
    }

    dtkDebug() << oarsub;
    QProcess stat; stat.start(oarsub);

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch oarsub command";
        return QString("error");
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to completed oarsub command";
        return QString("error");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkError() << "Error running oarsub :" << error;
        return QString("error");
    } else {
        QString oarsubout = stat.readAll();

        QRegExp rx("OAR_JOB_ID=(\\d+)");
        int pos = rx.indexIn(oarsubout);
        QStringList jobid = rx.capturedTexts();

        Q_UNUSED(pos);

        dtkDebug() << jobid.at(1);
        return jobid.at(1);
    }
}

QString dtkDistributedResourceManagerOar::deljob(QString jobid)
{

    QString oardel = "oardel " + jobid;
    QProcess stat; stat.start(oardel);

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch oardel command";
        return QString("ERROR");
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to complete oardel command";
        return QString("ERROR");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkError() << "Error running oardel :" << error;
        return QString("ERROR");
    } else {
        QString msg = stat.readAll();
        dtkDebug() << msg;
        return QString("OK");
    }
}

QByteArray dtkDistributedResourceManagerOar::status(void)
{
    QProcess stat;
    QString data;
    QVariantMap json;
    QVariantMap result;

    // get the jobs
    stat.start("oarstat -fJ");

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch oarstat command";
        return QByteArray();
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to completed oarstat command";
        return QByteArray();
    }

    data = stat.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8());

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        dtkError() << "Error while parsing JSON document (OAR) : not a json object" << data;
        return QByteArray();
    }
    json = jsonDoc.object().toVariantMap();

    stat.close();

    QVariantList jobs;
    QHash<QString, QString> activecores; //key is core id, value is jobid

    foreach(QVariant qv, json) {
        QVariantMap job = qv.toMap();
        QVariantMap dtkjob;
        QString id = job["Job_Id"].toString();
        QString user = job["job_user"].toString();
        QString queue = job["queue"].toString();
        QString qtime = job["submissionTime"].toString();
        QString stime = job["scheduledStart"].toString();
        QString walltime ;
        QString state =job["state"].toString();
        if (state == "Running")
            state = "running";
        else if ((state == "Waiting") && (job["reservation"].toString() == "scheduled"))
            state = "scheduled";
        else if (state == "Waiting")
            state = "queued";
        else if (state == "Suspended")
            state = "suspended";
        else if (state == "Hold")
            state = "blocked";
        else if (state == "Finishing")
            state = "exiting";
        else
            state = "unknown";

        foreach(QVariant coreid, job["assigned_resources"].toList()) {
            activecores[coreid.toString()] = id;
        }

        QRegExp rx("/network_address=(\\d+|ALL|BEST)(?:/core=)?(\\d+)?.*(?:walltime=)?(\\d+:\\d+:\\d+)");

        int pos = rx.indexIn(job["wanted_resources"].toString());

        Q_UNUSED(pos);

        QStringList resources_list = rx.capturedTexts();
        qlonglong nodes = resources_list.at(1).toInt();
        qlonglong cores = resources_list.at(2).toInt();
        if (cores == 0) {// all resources reserved
            cores = job["assigned_resources"].toList().count();
        }
        if (resources_list.count() > 3) {
            walltime = resources_list.at(3);
        } else {
            walltime = job["walltime"].toString(); //TODO: convert it to HH:MM:SS
            dtkDebug() << "can't find walltime from wanted resources! " << walltime;
        }

        QVariantMap jresources;

        jresources.insert("nodes",nodes);
        jresources.insert("cores",cores);

        dtkjob.insert("id", id);
        dtkjob.insert("username", user);
        dtkjob.insert("queue", queue);
        dtkjob.insert("queue_time", qtime);
        dtkjob.insert("start_time", stime);
        dtkjob.insert("walltime", walltime);
        dtkjob.insert("resources", jresources);
        dtkjob.insert("state", state);
        jobs << dtkjob;
        result.insert("jobs", jobs);
    }

    // Now get the nodes

    stat.start("oarnodes -J --sql \"host!=''\"");

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch oarnodes command";
        return QByteArray();
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to completed oarnodes command";
        return QByteArray();
    }

    data = stat.readAll();

    jsonDoc = QJsonDocument::fromJson(data.toUtf8());

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        dtkError() << "Error while parsing JSON document (OAR) : not a JSON object" << data;
        return QByteArray();
    }
    json = jsonDoc.object().toVariantMap();

    stat.close();

    QVariantMap nodes;
    foreach(QVariant qv, json) {
        QVariantMap jcore = qv.toMap();
        if (nodes.contains(jcore["host"].toString())) {
            QVariantMap core;
            QVariantMap node = nodes[jcore["host"].toString()].toMap();
            QVariantList cores = node["cores"].toList();
            QVariantList cpuids = node["cpuids"].toList();

            core.insert("id",jcore["resource_id"].toString());
            if (!activecores[core["id"].toString()].isEmpty()) {
                core.insert("job",activecores[core["id"].toString()]);
                int current_busy_cores = node["cores_busy"].toInt();
                node.insert("cores_busy", current_busy_cores+1);
            }
            qlonglong cpuid =  jcore["cpu"].toLongLong();
            if (!cpuids.contains(cpuid)) {
                cpuids <<  cpuid;
            }
            cores.append(core);
            node["cores"] = cores;
            node["cpuids"] = cpuids;
            nodes[jcore["host"].toString()] = node;
        } else { // new node
            QVariantList cores;
            QVariantList cpuids;
            QVariantList props;
            QVariantMap prop;
            QVariantMap core;
            QVariantMap node;
            if (jcore["cputype"].toString().contains("opteron")) {
                prop.insert("cpu_model","opteron");
                prop.insert("cpu_arch","x86_64");
            } else if (jcore["cputype"].toString().contains("xeon")) {
                prop.insert("cpu_model","xeon");
                prop.insert("cpu_arch","x86_64");
            }
            node.insert("name",jcore["host"]);
            QString state;
            if (jcore["state"].toString() == "Absent")
                if (jcore["available_upto"].toLongLong() > 0)
                    state = "standby";
                else
                    state = "absent";
            else if (jcore["state"].toString() == "Dead")
                state = "down";
            else if (jcore["state"].toString() == "Suspected")
                state = "absent";
            else if (jcore["state"].toString() == "Alive") {
                if (jcore["jobs"].toString().isEmpty())
                    state = "free";
                else
                    state = "busy";
            }
            node.insert("state", state);
            cpuids << jcore["cpu"].toLongLong();
            node.insert("cpuids",cpuids);
            core.insert("id",jcore["resource_id"]);
            if (!activecores[core["id"].toString()].isEmpty()) {
                core.insert("job",activecores[core["id"].toString()]);
                node.insert("cores_busy",1);
            } else {
                node.insert("cores_busy",0);
            }
            cores << core;
            props << prop;
            node.insert("cores",cores);
            node.insert("properties",props);
            nodes.insert(jcore["host"].toString(), node);
        }
    }

    QVariantList realnodes;
    // now we can compute the number of cpus per node
    foreach(QVariant qv, nodes) {
        QVariantMap map = qv.toMap();
        qlonglong cpus  = map["cpuids"].toList().count();
//        qlonglong cores = map["cores"].toList().count();
        map.insert("cpus", cpus);
        map.remove("cpuids");
        realnodes << map;
    }
    result.insert("nodes", realnodes);

    return QJsonDocument(QJsonObject::fromVariantMap(result)).toJson();
}
