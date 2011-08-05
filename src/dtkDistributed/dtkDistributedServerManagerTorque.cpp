/* dtkDistributedServerManagerTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. août  5 15:01:34 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 575
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"
#include "dtkDistributedNode.h"
#include "dtkDistributedServerManager_p.h"
#include "dtkDistributedServerManagerTorque.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>
#include <dtkJson/dtkJson.h>

#include <QtCore>
#include <QtXml>

QString dtkDistributedServerManagerTorque::submit(QString input)
{

    QString qsub = "qsub ";

    // format: ** submit **; resources; properties; walltime; script; queue ; options
    QStringList arglist = input.split(";");

    // properties, syntax: (arch=opteron,gpu=nvidia-T10)

    // FIXME: we should read the properties mapping from a file instead of hardcoding it
    // Everything here is specific to nef setup.
    QStringList proplist=arglist.at(2).split(",");
    QString properties = "";
    QString prop;
    foreach( prop, proplist ) {
        if (prop.contains("opteron")) {
            properties +=  ":opteron";
        } else if (prop.contains("xeon")) {
            properties += ":xeon";
        } else if (prop.contains("nvidia-C2050")) {
            properties += "C2050";
        } else if (prop.contains("nvidia-T10")) {
            properties += "T10";
        }
    }

    // resources   syntax: #cores,#nodes
    QStringList reslist=arglist.at(1).split(",");
    if (reslist.at(0) == 0) {
        // no nodes, only cores; TODO
    } else if (reslist.at(1) == 0) {
        // no cores, only nodes; TODO
    } else {
        qsub += " -l nodes="+reslist.at(0)+properties+":ppn="+reslist.at(1);
    }

    // walltime, syntax=HH:MM:SS
    if (!arglist.at(3).isEmpty()) {
        qsub += ",walltime="+arglist.at(3);
    }

    // script
    qsub += " "+arglist.at(4);

    // queue
    if (!arglist.at(5).isEmpty()) {
        qsub += " -q "+arglist.at(5);
    }

    // options
    if (!arglist.at(6).isEmpty()) {
        qsub += " "+arglist.at(6);
    }

    qDebug() << DTK_PRETTY_FUNCTION << qsub;
    QProcess stat; stat.start(qsub);

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch stat command";
        return QString("error");
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed stat command";
        return QString("error");
    }
    if (stat.exitCode() > 0) {
        QString error = stat.readAllStandardError();
        dtkCritical() << "Error running qsub :" << error;
        return QString("error");
    } else {
        QString jobid = stat.readAll();
        qDebug() << DTK_PRETTY_FUNCTION << jobid;
        return jobid.split(".").at(0);
    }
}

QDomDocument getXML(QString command)
{
    QDomDocument document; QString error;
    QProcess stat; stat.start(command);

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch stat command";
        return document;
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed stat command";
        return document;
    }

    QString data = stat.readAll();

    if(!document.setContent(data, false, &error))
        dtkDebug() << "Error retrieving xml output out of torque "  << error;

    stat.close();
    return document;

}

QString dtkDistributedServerManagerTorque::status(void)
{

    QDomDocument document = getXML("pbsnodes -x");
    QString result = "version=" + protocol() +"\n";

    QDomNodeList nodes = document.elementsByTagName("Node");
    for(int i = 0; i < nodes.count(); i++) {
        QString np = nodes.item(i).firstChildElement("np").text().simplified();
        QString name = nodes.item(i).firstChildElement("name").text().simplified();
        QString state = nodes.item(i).firstChildElement("state").text().simplified();

        // Each job is coreid/jobid, count the number of "/" to get the number of jobs
        int njobs  = nodes.item(i).firstChildElement("jobs").text().simplified().count("/");
        QString ngpus  = nodes.item(i).firstChildElement("gpus").text().simplified();
        // 2 cpus by default
        QString ncpus  = "2";

        // number of busy GPUs not implemented yet
        QStringList properties = nodes.item(i).firstChildElement("properties").text().simplified().split(",");

        QStringList outprops;
        QString prop;
        // FIXME: we should read the properties mapping from a file instead of hardcoding it
        // Everything here is specific to nef setup.
        outprops << "infiniband=QDR";
        outprops << "ethernet=1G";
        foreach( prop, properties ) {
            if (prop.contains("opteron")) {
                outprops << "arch=opteron";
            } else if (prop.contains("xeon")) {
                outprops << "arch=xeon";
            } else if (prop.contains("C2050")) {
                outprops << "gpu=nvidia-C2050";
            } else if (prop.contains("T10")) {
                outprops << "gpu=nvidia-T10";
            } else if (prop.contains("T10")) {
                outprops << "gpu=nvidia-T10";
            }
            if (prop.contains("dellr815")) {
                ncpus = "4";
            }
        }
        result += "node;"+name + ";" + np + ";" + QString::number(njobs) + ";"+ncpus+";" + ngpus + ";0;" + "("+outprops.join(",")+");";
        if (state.contains("job-exclusive")) {
            state="busy";
        } else if (state.contains("free")) {
            state="free";
        } else {
            state="down";
        }
        result += state+"\n";
    }

    // Now get the jobs
    document = getXML("qstat -x");
    QDomNodeList jobs = document.elementsByTagName("Job");
    for(int i = 0; i < jobs.count(); i++) {
        QString id = jobs.item(i).firstChildElement("Job_Id").text().simplified().split(".").at(0);
        QString user = jobs.item(i).firstChildElement("Job_Owner").text().simplified().split("@").at(0);
        QString queue = jobs.item(i).firstChildElement("queue").text().simplified();
        QString qtime = jobs.item(i).firstChildElement("ctime").text().simplified();
        QString stime ;
        QDomElement resources_list = jobs.item(i).firstChildElement("Resource_List") ;
        QString resources = resources_list.firstChildElement("nodes").text().simplified() ;
        QStringList rlist = resources.split(":") ;
        QStringList ppn = rlist.last().split("=") ;
        QString nodes = rlist.at(0);
        QString cores = ppn.last();
        resources = nodes+","+cores;

        QString walltime = resources_list.firstChildElement("walltime").text().simplified() ;
        QString state;
        char J= jobs.item(i).firstChildElement("job_state").text().simplified().at(0).toAscii();
        switch (J) {
        case 'R' :
            state = "running";   break;
        case 'Q' :
            state = "queued";    break;
        case 'S' :
            state = "suspended"; break;
        case 'H' :
            state = "blocked";   break;
        case 'E' :
            state = "exiting";   break;
        case 'W' :
            state = "scheduled"; break;
        default  :
            state = "unknown";   break;
        };
        result += "job;"+id + ";" + user + ";" + state+";"+qtime+";"+stime+";"+queue+";"+walltime+";"+resources+"\n";
    }

    return result;
}
