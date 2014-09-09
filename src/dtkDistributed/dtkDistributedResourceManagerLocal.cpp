/* @(#)dtkDistributedResourceManagerLocal.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 11:39:38
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedResourceManagerLocal.h"

// #include <dtkCore/dtkCpuid.h>

#include <dtkLog>

#include <QtCore>
#include <QHostInfo>

class dtkDistributedResourceManagerLocalPrivate
{
public:
    QHash<QString,QProcess *> slaves;

public:
    QTemporaryFile tmp_err;
};


// /////////////////////////////////////////////////////////////////
// dtkDistributedResourceManagerLocal implementation
// /////////////////////////////////////////////////////////////////

dtkDistributedResourceManagerLocal::dtkDistributedResourceManagerLocal(void) :  d(new dtkDistributedResourceManagerLocalPrivate)
{
}

dtkDistributedResourceManagerLocal::~dtkDistributedResourceManagerLocal(void)
{
    delete d;
}


QByteArray  dtkDistributedResourceManagerLocal::status(void)
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

    qlonglong ncpus  = 1;
    qlonglong njobs  = d->slaves.keys().count();
    qlonglong ngpus  = 0;

    for (int c=0;c< QThread::idealThreadCount();c++) {
        QVariantMap core;
        core.insert("id",c);
        if (c < njobs) {
            core.insert("job",d->slaves.keys().at(c));
        }
        cores << core;
    }

    node.insert("cores", cores );
    node.insert("cpus", ncpus);
    node.insert("cores_busy", njobs);
    node.insert("gpus", ngpus);
    node.insert("gpus_busy", 0);

#if defined(Q_PROCESSOR_ARM)
    props.insert("cpu_arch", "arm");
#elif defined(Q_PROCESSOR_X86_64)
    props.insert("cpu_arch", "x86_64");
#elif defined(Q_PROCESSOR_X86_32)
    props.insert("cpu_arch", "x86_32");
#endif

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
        QVariantMap jresources;
        jresources.insert("nodes",1);
        //FIXME: how many cores ?
        jresources.insert("cores",1);
        job.insert("resources", jresources);
        jjobs << job;
    }

    result.insert("jobs", jjobs);
    node.insert("state", state);
    node.insert("properties", props);
    jnodes << node;
    result.insert("nodes", jnodes);


    return QJsonDocument(QJsonObject::fromVariantMap(result)).toJson();
}

QString dtkDistributedResourceManagerLocal::submit(QString input)
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
    QJsonDocument jsonDoc = QJsonDocument::fromJson(input.toUtf8());

    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        dtkWarn() << "Error while parsing JSON document: not a json object" << input;
        return QString("ERROR");
    }
    QVariantMap json = jsonDoc.object().toVariantMap();

    QSettings settings("inria", "dtk");
    settings.beginGroup("distributed");

    // script
    if (json.contains("script")) {
        qsub += " "+json["script"].toString();
    } else if (json.contains("application")) {
        QString server = QHostInfo::localHostName ();
#if defined(Q_OS_MAC)
        server.replace(".", "_");
#endif
        dtkDebug() << "looking for setup in " << server;

        QVariantMap res = json["resources"].toMap();
        int nodes;
        int threads;
        if (res["nodes"].toInt() == 0) {
            // no nodes, only cores; TODO
        } else if (res["cores"].toInt() == 0) {
            // no cores, only nodes; TODO
        } else {
            nodes = res["nodes"].toInt();
            threads = res["cores"].toInt();
        }

        if (settings.contains(server +"_server_mpirun_path")) {
            dtkDebug() << "found specific command for this server:" << settings.value(server +"_server_mpirun").toString();
            qsub = settings.value(server +"_server_mpirun_path").toString();

            if (nodes > 1)
                args += "-np " + QString::number(nodes*threads) + " ";


            if (settings.contains(server +"_server_mpirun_args")) {
                args += settings.value(server +"_server_mpirun_args").toString();
            }

            args += qApp->applicationDirPath()
                  + "/"
                  + json["application"].toString();

        } else {
            QStringList app = json["application"].toString().split(" ");
            qsub = qApp->applicationDirPath()
                + "/"
                + app.takeFirst();

            args += app.join(" ");

            if (nodes > 1)
                args += " -np "+ QString::number(nodes)+ " ";
            if (threads > 1)
                args += " -nt "+ res["cores"].toString();
        }

    } else {
        dtkError() << "no script and no application";
        return QString("ERROR");
    }

    QProcess *stat = new QProcess;
    QStringList rargs= args.split(" ");
    QString err_filename;

    dtkDebug() << qsub << rargs;

    if (d->tmp_err.open()) {
        if (settings.contains("keep_output_files") && settings.value("keep_output_files").toBool() ) {
            d->tmp_err.setAutoRemove(false);
        }
        err_filename = d->tmp_err.fileName();
        stat->setStandardErrorFile(err_filename);
        dtkInfo() << "std error file of job is" << err_filename;
    } else {
        return QString("ERROR");
    }

    stat->start(qsub,rargs);
    if (stat->waitForStarted(5000))
        dtkDebug() << "process started";
    else
        return QString("ERROR");

    // Wait for jobid in stdout
    QEventLoop loop;
    loop.connect(stat,SIGNAL(readyRead()),&loop,SLOT(quit()));
    loop.connect(qApp, SIGNAL(aboutToQuit()), &loop, SLOT(quit()));
    loop.exec();

    QString tmp = stat->readLine();
    if (tmp.isEmpty()) {
        dtkError() << "empty output file";
        return QString("ERROR");
    }
    QString jobid = tmp.simplified().split("=").at(1);

    d->slaves.insert(jobid,stat);
    dtkDebug() << jobid;
    return jobid;
}

QString dtkDistributedResourceManagerLocal::deljob(QString jobid)
{
    if (!d->slaves.contains(jobid)) {
        dtkError() << "Unknown job to delete" << jobid;
        return QString("ERROR");
    }

    d->slaves[jobid]->close();
    d->slaves.remove(jobid);

    return QString("OK");
}
