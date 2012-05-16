/* dtkDistributedServerManagerSsh.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. mai  3 16:56:17 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 224
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
#include "dtkDistributedServerManagerSsh.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkCpuid.h>

#include <dtkJson/dtkJson.h>

#include <dtkLog/dtkLog.h>

#include <QtCore>
#include <QHostInfo>

class dtkDistributedServerManagerSshPrivate
{
public:
    QHash<QString,QProcess *> slaves;
};


// /////////////////////////////////////////////////////////////////
// dtkDistributedServerManagerSsh implementation
// /////////////////////////////////////////////////////////////////

dtkDistributedServerManagerSsh::dtkDistributedServerManagerSsh(void) :  d(new dtkDistributedServerManagerSshPrivate)
{
}

dtkDistributedServerManagerSsh::~dtkDistributedServerManagerSsh(void)
{
    delete d;
}


QByteArray  dtkDistributedServerManagerSsh::status(void)
{
    QVariantMap result;
    QVariantList jnodes;
    QVariantList jjobs;
    result.insert("version", protocol());

    QVariantMap node;
    QVariantMap props;
    QVariantList cores;

    QString name = "localhost";
    QString state = "free";
    node.insert("name", name);

    QString ncpus  = "1";
    QString njobs  = "0";
    QString ngpus   = "0";

    for (int c=0;c< QThread::idealThreadCount();c++) {
        QVariantMap core;
        core.insert("id",c);
        cores << core;
    }

    node.insert("cores", cores );
    node.insert("cpus", ncpus);
    node.insert("cores_busy", njobs);
    node.insert("gpus", ngpus);
    node.insert("gpus_busy", 0);

    dtkCpuid cpuID;
    QString vendor = cpuID.vendor();
    if  (vendor == "GenuineIntel") {
        props.insert("cpu_model", "xeon");
        props.insert("cpu_arch", "x86_64");
    } else if (vendor == "AuthenticAMD") {
        props.insert("cpu_model", "opteron");
        props.insert("cpu_arch", "x86_64");
    }
    props.insert("ethernet", "1G");

    foreach(QString id, d->slaves.keys()) {
        QVariantMap job;
        job.insert("id", id);
        job.insert("username", "me");
        job.insert("queue", "default");
        job.insert("queue_time", "");
        job.insert("start_time", "");
        job.insert("walltime", "12:0:0");
        job.insert("state", "running");
        jjobs << job;
    }

    result.insert("jobs", jjobs);
    node.insert("state", state);
    node.insert("properties", props);
    jnodes << node;
    result.insert("nodes", jnodes);


    return dtkJson::serialize(result);
}

QString dtkDistributedServerManagerSsh::submit(QString input)
{
    QString qsub;
    QString args;

    /* format: {"resources": {"nodes": 0..N, "cores": 1..M },
                "properties": {{"key": "value"}, ...},
                "walltime": "hh:mm:ss",
                "script": "script_path" | "application": "app_args",
                "queue": "queuename";
                "options": "string"
                }
    */
    QVariantMap json = dtkJson::parse(input).toMap();

    // script
    if (json.contains("script")) {
        qsub += " "+json["script"].toString();
    } else if (json.contains("application")) {
        QSettings settings("inria", "dtk");
        settings.beginGroup("distributed");
        QString server = QHostInfo::localHostName ();
#if defined(Q_WS_MAC)
        server.replace(".", "_");
#endif
        if (settings.contains(server +"_server_mpirun_path")) {
            dtkDebug() << "found specific command for this server:" << settings.value(server +"_server_mpirun").toString();
            qsub = settings.value(server +"_server_mpirun_path").toString();
        } else
            qsub = "mpirun";

        QVariantMap res = json["resources"].toMap();
        if (res["nodes"].toInt() == 0) {
            // no nodes, only cores; TODO
        } else if (res["cores"].toInt() == 0) {
            // no cores, only nodes; TODO
        } else {
            int procs = res["nodes"].toInt()*res["cores"].toInt();
            if (procs > 1)
                args += "-np "+ QString::number(procs) + " ";
        }

        if (settings.contains(server +"_server_mpirun_args"))
            args += settings.value(server +"_server_mpirun_args").toString();
        args += qApp->applicationDirPath()
            + "/"
            + json["application"].toString();
    } else {
        dtkError() << "no script and no application";
        return QString("ERROR");
    }

    QProcess *stat = new QProcess;
    QStringList rargs= args.split(" ");
    dtkDebug() << DTK_PRETTY_FUNCTION << qsub << rargs;
    // stat->setStandardErrorFile("/tmp/slave-err.log");
    // stat->setStandardOutputFile("/tmp/slave-out.log");
    stat->start(qsub,rargs);
    if (stat->waitForStarted(5000))
        dtkDebug() << DTK_PRETTY_FUNCTION << "process started";
    else
        return QString("ERROR");

    QString jobid = QString::number(stat->pid());
    d->slaves.insert(jobid,stat);
    dtkDebug() << DTK_PRETTY_FUNCTION << jobid;
    return jobid;
}

QString dtkDistributedServerManagerSsh::deljob(QString jobid)
{
    if (!d->slaves.contains(jobid)) {
        dtkError() << "Unknown job to delete" << jobid;
        return QString("ERROR");
    }

    d->slaves[jobid]->close();
    d->slaves.remove(jobid);

    return QString("OK");
}
