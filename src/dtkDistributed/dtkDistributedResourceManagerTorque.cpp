/* dtkDistributedResourceManagerTorque.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 08:26:07
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkDistributedResourceManagerTorque.h"

#include <dtkLog>

#include <QtCore>
#include <QtXml>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QDomDocument getXML(QString command);

// /////////////////////////////////////////////////////////////////
// dtkDistributedResourceManagerTorque implementation
// /////////////////////////////////////////////////////////////////

QByteArray  dtkDistributedResourceManagerTorque::status(void)
{
    QDomDocument document = getXML("pbsnodes -x");
    QVariantMap result;
    QVariantList jnodes;
    QVariantList jjobs;
    result.insert("version", protocol());
    qint64 globalcores = 0;

    QDomNodeList nodes = document.elementsByTagName("Node");
    for(int i = 0; i < nodes.count(); i++) {
        QVariantMap node;
        QVariantMap props;
        int np = nodes.item(i).firstChildElement("np").text().toInt();
        QString name = nodes.item(i).firstChildElement("name").text().simplified();
        QString state = nodes.item(i).firstChildElement("state").text().simplified();

        node.insert("name", name);

        qlonglong ngpus  = nodes.item(i).firstChildElement("gpus").text().toInt();
        // 2 cpus by default
        qlonglong ncpus  = 2;
        // number of busy GPUs not implemented yet

        // properties
        QStringList properties = nodes.item(i).firstChildElement("properties").text().simplified().split(",");

        QStringList outprops;
        QString prop;
        // FIXME: we should read the properties mapping from a file instead of hardcoding it
        // Everything here is specific to nef setup.
        props.insert("infiniband", "QDR");
        props.insert("ethernet", "1G");
        foreach( prop, properties ) {
            if (prop.contains("opteron")) {
                props.insert("cpu_model", "opteron");
                props.insert("cpu_arch", "x86_64");
            } else if (prop.contains("xeon")) {
                props.insert("cpu_model", "xeon");
                props.insert("cpu_arch", "x86_64");
            } else if (prop.contains("C2050")) {
                props.insert("gpu_model", "C2050");
                props.insert("gpu_arch", "nvidia-2.0");
            } else if (prop.contains("C2070")) {
                props.insert("gpu_model", "C2070");
                props.insert("gpu_arch", "nvidia-2.0");
            } else if (prop.contains("T10")) {
                props.insert("gpu_model", "T10");
                props.insert("gpu_arch", "nvidia-1.3");
            }
            if (prop.contains("dellr815")) {
                ncpus = 4;
            }
        }

        // Each job is coreid/jobid
        QStringList rjobs  = nodes.item(i).firstChildElement("jobs").text().simplified().split(",");
        QRegExp rx("(\\d+)/(\\d+)\\[?(\\d*)\\]?\\..*");
        QVariantList cores;
        qint64 njobs = 0;
        for (int c=0;c<np;c++) {
            QVariantMap core;
            // torque doesn't define a unique id per core, so assigned
            // a unique number to each core of the cluster
            core.insert("id",globalcores +c);
            cores << core;
        }
        if (rjobs.at(0).count() > 0) { // running jobs ?
            foreach( QString rjob, rjobs ) {
                rx.indexIn(rjob);
                QStringList list = rx.capturedTexts();
                njobs++;
                qint64 jobcore = list.at(1).toInt();
                QVariantMap q = cores[jobcore].toMap();
                if (list.at(3).isEmpty())
                    q.insert("job",list.at(2));
                else
                    q.insert("job",list.at(2)+"[]"); // array job
                cores[jobcore] = q;
            }
        }
        node.insert("cores", cores );
        node.insert("cpus", ncpus);
        node.insert("cores_busy", njobs);
        node.insert("gpus", ngpus);
        node.insert("gpus_busy", 0);
        node.insert("properties", props);

        if (state.contains("job-exclusive")) {
            state="busy";
        } else if (state.contains("free")) {
            state="free";
        } else {
            state="down";
        }
        node.insert("state", state);
        jnodes << node;
        result.insert("nodes", jnodes);
        globalcores += np;
    }

    // Now get the jobs
    document = getXML("qstat -x");
    QDomNodeList jobs = document.elementsByTagName("Job");
    for(int i = 0; i < jobs.count(); i++) {
        QVariantMap job;
        QVariantMap jresources;

        QString id = jobs.item(i).firstChildElement("Job_Id").text().simplified().split(".").at(0);
        QString user = jobs.item(i).firstChildElement("Job_Owner").text().simplified().split("@").at(0);
        QString queue = jobs.item(i).firstChildElement("queue").text().simplified();
        QString qtime = jobs.item(i).firstChildElement("ctime").text().simplified();
        QString stime ;
        QDomElement resources_list = jobs.item(i).firstChildElement("Resource_List") ;
        QString resources = resources_list.firstChildElement("nodes").text().simplified() ;
        QStringList rlist = resources.split(":") ;
        QStringList ppn = rlist.last().split("=") ;
        qlonglong nodes = rlist.at(0).toInt();
        qlonglong cores = ppn.last().toInt();

        jresources.insert("nodes",nodes);
        jresources.insert("cores",cores);

        QString walltime = resources_list.firstChildElement("walltime").text().simplified() ;
        QString state;
        char J= jobs.item(i).firstChildElement("job_state").text().simplified().at(0).unicode();
        switch (J) {
        case 'R' : {
            state = "running";
            stime = jobs.item(i).firstChildElement("start_time").text().simplified();
            break;
        }
        case 'Q' :
            state = "queued";    break;
        case 'S' :
            state = "suspended"; break;
        case 'H' :
            state = "blocked";   break;
        case 'E' : {
            state = "exiting";
            stime = jobs.item(i).firstChildElement("start_time").text().simplified();
            break;
        }
        case 'W' :
            state = "scheduled"; break;
        default  :
            state = "unknown";   break;
        };
        job.insert("id", id);
        job.insert("username", user);
        job.insert("queue", queue);
        job.insert("queue_time", qtime);
        job.insert("start_time", stime);
        job.insert("walltime", walltime);
        job.insert("resources", jresources);
        job.insert("state", state);

        jjobs << job;
        result.insert("jobs", jjobs);
    }

    return QJsonDocument(QJsonObject::fromVariantMap(result)).toJson();
}

QString dtkDistributedResourceManagerTorque::submit(QString input)
{
    QString qsub = "qsub ";

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
    if (jprops.contains("cpu_model")) {
        properties +=  ":"+jprops["cpu_model"].toString();
    } else if (jprops.contains("nvidia-C2050")) {
        properties += ":C2050";
    } else if (jprops.contains("nvidia-C2070")) {
        properties += ":C2070";
    } else if (jprops.contains("nvidia-T10")) {
        properties += ":T10";
    }

    QVariantMap res = json["resources"].toMap();
    if (res["nodes"] == 0) {
        // no nodes, only cores; TODO
    } else if (res["cores"] == 0) {
        // no cores, only nodes; TODO
    } else {
        qsub += " -l nodes="+res["nodes"].toString()+properties+":ppn="+res["cores"].toString();
    }

    // walltime, syntax=HH:MM:SS
    if (json.contains("walltime")) {
        qsub += ",walltime="+json["walltime"].toString();
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
            out << "#!/bin/bash\n";
            out << qApp->applicationDirPath()
                    + "/"
                    + json["application"].toString();
        }

        script.close();

        qsub += " " + scriptName;

    } else {
        dtkError() << "no script and no application";
        return QString("ERROR");
    }

    // queue
    if (json.contains("queue")) {
        qsub += " -q "+json["queue"].toString();
    }

    // options
    if (json.contains("options")) {
        qsub += " "+json["options"].toString();
    }

    dtkDebug() << qsub;
    QProcess stat; stat.start(qsub);

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch stat command";
        return QString("ERROR");
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to completed stat command";
        return QString("ERROR");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkError() << "Error running qsub :" << error;
        return QString("ERROR");
    } else {
        QString jobid = stat.readAll();
        dtkDebug() << jobid;
        return jobid.split(".").at(0);
    }
}

QString dtkDistributedResourceManagerTorque::deljob(QString jobid)
{
    QString qdel = "qdel " + jobid;
    QProcess stat; stat.start(qdel);

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch qdel command";
        return QString("ERROR");
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to complete qdel command";
        return QString("ERROR");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkError() << "Error running qdel :" << error;
        return QString("ERROR");
    } else {
        QString msg = stat.readAll();
        dtkDebug() << msg;
        return QString("OK");
    }
}

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QDomDocument getXML(QString command)
{
    QDomDocument document; QString error;
    QProcess stat; stat.start(command);

    if (!stat.waitForStarted()) {
        dtkError() << "Unable to launch stat command";
        return document;
    }

    if (!stat.waitForFinished()) {
        dtkError() << "Unable to completed stat command";
        return document;
    }

    QString data = stat.readAll();

    if(!document.setContent(data, false, &error)) {
        dtkDebug() << "Error retrieving xml output out of torque "  << error;
    }

    stat.close();

    return document;
}
