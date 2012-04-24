/* dtkDistributedServerManagerTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. avril 24 18:19:58 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 1009
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


// /////////////////////////////////////////////////////////////////
// dtkDistributedServerManagerTorque implementation
// /////////////////////////////////////////////////////////////////

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

    QString cores  = "1"; //FIXME
    QString ncpus  = "1";
    QString njobs  = "0";
    QString ngpus   = "0";

    node.insert("cores", cores );
    node.insert("cpus", ncpus);
    node.insert("cores_busy", njobs);
    node.insert("gpus", ngpus);
    node.insert("gpus_busy", 0);
    node.insert("properties", props);

    node.insert("state", state);
    jnodes << node;
    result.insert("nodes", jnodes);

    return dtkJson::serialize(result);
}

QString dtkDistributedServerManagerSsh::submit(QString input)
{
    QString qsub = "bash ";

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
            QTextStream out(&script);
            out << "#!/bin/bash\n";
            //FIXME: hardcoded for the IS
            out << "/usr/local/bin/cluster-run "
                + qApp->applicationDirPath()
                + "/"
                + json["application"].toString();
        }

        script.close();

        qsub += " " + scriptName;
        qsub += "& " ;

    } else {
        dtkError() << "no script and no application";
        return QString("ERROR");
    }

    dtkDebug() << DTK_PRETTY_FUNCTION << qsub;
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
        dtkError() << "Error running bash command :" << error;
        return QString("ERROR");
    } else {
        QString jobid = stat.readAll();
        dtkDebug() << DTK_PRETTY_FUNCTION << jobid;
        return jobid.split(" ").at(1);
    }
}

QString dtkDistributedServerManagerSsh::deljob(QString jobid)
{
    QString qdel = "kill " + jobid;
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
        dtkDebug() << DTK_PRETTY_FUNCTION << msg;
        return QString("OK");
    }
}
