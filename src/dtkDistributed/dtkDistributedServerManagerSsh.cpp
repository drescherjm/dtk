/* dtkDistributedServerManagerSsh.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 25 16:48:14 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 118
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

#include <dtkJson/dtkJson.h>

#include <dtkLog/dtkLog.h>

#include <QtCore>
#include <QHostInfo>

class dtkDistributedServerManagerSshPrivate
{
public:
    QList<QString> slaves;
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
    QString name = "localhost";
    QString state = "free";
    node.insert("name", name);

    QString ncpus  = "1";
    QString njobs  = "0";
    QString ngpus   = "0";

    node.insert("cores",  QThread::idealThreadCount() );
    node.insert("cpus", ncpus);
    node.insert("cores_busy", njobs);
    node.insert("gpus", ngpus);
    node.insert("gpus_busy", 0);
    node.insert("properties", props);

    foreach(QString id, d->slaves) {
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
    jnodes << node;
    result.insert("nodes", jnodes);
    return dtkJson::serialize(result);
}

QString dtkDistributedServerManagerSsh::submit(QString input)
{
    QString qsub;

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

        QString scriptName = qApp->applicationDirPath() + "/dtkDistributedServerScript.sh";

        QFile script(scriptName);

        if (!script.open(QFile::WriteOnly|QFile::Truncate)) {
            dtkWarn() << "unable to open script for writing";
        } else {
            script.setPermissions(QFile::ExeOwner|QFile::ReadOwner|QFile::WriteOwner);
            QTextStream out(&script);
            out << "#!/bin/bash\n";
            QSettings settings("inria", "dtk");
            settings.beginGroup("distributed");
            QString server = QHostInfo::localHostName ();
#if defined(Q_WS_MAC)
            server.replace(".", "_");
#endif
            if (settings.contains(server +"_server_mpirun")) {
                out << settings.value(server +"_server_mpirun").toString() << " ";
            } else
                out << "mpirun ";

            QVariantMap res = json["resources"].toMap();
            if (res["nodes"].toInt() == 0) {
                // no nodes, only cores; TODO
            } else if (res["cores"].toInt() == 0) {
                // no cores, only nodes; TODO
            } else {
                int procs = res["nodes"].toInt()*res["cores"].toInt();
                if (procs > 1)
                    out << " -np "+ QString::number(procs) + " ";
            }

            out << qApp->applicationDirPath()
                + "/"
                + json["application"].toString();
        }
        script.close();
        qsub = scriptName;
    } else {
        dtkError() << "no script and no application";
        return QString("ERROR");
    }

    QProcess stat;
    qint64 pid;
    QStringList args;
    QString wd =  qApp->applicationDirPath();
    if (stat.startDetached(qsub,args,wd,&pid))
        dtkDebug() << DTK_PRETTY_FUNCTION << "process started";
    else
        return QString("ERROR");

    QString jobid = QString::number(pid);
    d->slaves << jobid;
    dtkDebug() << DTK_PRETTY_FUNCTION << jobid;
    return jobid;
}

QString dtkDistributedServerManagerSsh::deljob(QString jobid)
{
    QString qdel = "kill " + jobid;
    QProcess stat; stat.start(qdel);
    d->slaves.removeOne(jobid);

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
        dtkDebug() << DTK_PRETTY_FUNCTION << msg;
        return QString("OK");
    }
}
