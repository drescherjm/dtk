/* dtkDistributedServerManagerOar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. sept. 15 15:11:30 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 361
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedServerManager_p.h"
#include "dtkDistributedServerManagerOar.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>
#include <dtkJson/dtkJson.h>

QString dtkDistributedServerManagerOar::status(void)
{
    QProcess stat;
    bool success;
    QString data;
    QVariantMap json;
    QVariantMap result;

    // get the jobs
    stat.start("oarstat -fJ");

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch oarstat command";
        return QString();
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed oarstat command";
        return QString();
    }

    data = stat.readAll();
    json = dtkJson::parse(data,success).toMap();
    if(!success)
        dtkDebug() << "Error retrieving JSON output out of oar  "  ;
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

        QRegExp rx("/host=(\\d+|ALL|BEST)(?:/core=)?(\\d+)?.*(?:walltime=)?(\\d+:\\d+:\\d+)");
        int pos = rx.indexIn(job["wanted_resources"].toString());
        QStringList resources_list = rx.capturedTexts();
        QString nodes = resources_list.at(1);
        QString cores = resources_list.at(2);
        if (resources_list.count() > 3) {
            walltime = resources_list.at(3);
        } else {
            walltime = job["walltime"].toString(); //TODO: convert it to HH:MM:SS
            qDebug() << DTK_PRETTY_FUNCTION << "can't find walltime from wanted resources! " << walltime;
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
        dtkCritical() << "Unable to launch oarnodes command";
        return QString();
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed oarnodes command";
        return QString();
    }

    data = stat.readAll();
    json = dtkJson::parse(data,success).toMap();
    if(!success)
        dtkDebug() << "Error retrieving JSON output out of oar  "  ;
    stat.close();

    QVariantMap nodes;
    foreach(QVariant qv, json) {
        QVariantMap jcore = qv.toMap();
        if (nodes.contains(jcore["host"].toString())) {
            QVariantMap core;
            QVariantMap node = nodes[jcore["host"].toString()].toMap();
            QVariantList cores = node["cores"].toList();

            core.insert("id",jcore["core"].toString());
            if (!activecores[core["id"].toString()].isEmpty()) {
                core.insert("jobs",activecores[core["id"].toString()]);
            }
            cores.append(core);
            node["cores"] = cores;
            nodes[jcore["host"].toString()] = node;
        } else { // new node
            QVariantList cores;
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
            node.insert("corespercpu",jcore["cpucore"]); // temporary
            core.insert("id",jcore["core"]);
            if (!activecores[core["id"].toString()].isEmpty()) {
                core.insert("jobs",activecores[core["id"].toString()]);
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
        int corespercpu = map["corespercpu"].toInt();
        int cores = map["cores"].toList().count();
        map.insert("cpus", cores/corespercpu);
        map.remove("corespercpu");
        realnodes << map;
    }
    result.insert("nodes", realnodes);





    return dtkJson::serialize(result);
}

QString dtkDistributedServerManagerOar::submit(QString input)
{
    QString oarsub = "oarsub ";

    QVariantMap json = dtkJson::parse(input).toMap();

    QVariantMap jprops = json["properties"].toMap();
    QString properties ;
    if (jprops.contains("cpu_model")) {
        properties +=  " -p \"cputype='"+jprops["cpu_model"].toString()+"'\"";
    } else if (jprops.contains("cluster")) {
        properties +=  " -p \"cluster='"+jprops["cluster"].toString()+"'\"";
    }
    // TODO:handle other properties

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
    oarsub += " "+json["script"].toString();

    // queue
    if (json.contains("queue")) {
        oarsub += " -q "+json["queue"].toString();
    }
    // options
    if (json.contains("options")) {
        oarsub += " "+json["options"].toString();
    }

    qDebug() << DTK_PRETTY_FUNCTION << oarsub;
    QProcess stat; stat.start(oarsub);

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch oarsub command";
        return QString("error");
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed oarsub command";
        return QString("error");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkCritical() << "Error running oarsub :" << error;
        return QString("error");
    } else {
        QString oarsubout = stat.readAll();

        QRegExp rx("OAR_JOB_ID=(\\d+)");
        int pos = rx.indexIn(oarsubout);
        QStringList jobid = rx.capturedTexts();

        qDebug() << DTK_PRETTY_FUNCTION << jobid.at(0);
        return jobid.at(0);
    }
}

QString dtkDistributedServerManagerOar::deljob(QString jobid)
{

    QString oardel = "oardel " + jobid;
    QProcess stat; stat.start(oardel);

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch oardel command";
        return QString("error");
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to complete oardel command";
        return QString("error");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkCritical() << "Error running oardel :" << error;
        return QString("error");
    } else {
        QString msg = stat.readAll();
        qDebug() << DTK_PRETTY_FUNCTION << msg;
        return QString("OK");
    }
}
