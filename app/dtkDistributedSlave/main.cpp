/* @(#)main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 16:28:19
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */



#include <dtkCore/dtkCore.h>

#include <dtkDistributed/dtkDistributed.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedSettings.h>
#include <dtkDistributed/dtkDistributedSlave.h>
#include <dtkDistributed/dtkDistributedPolicy.h>
#include <dtkDistributed/dtkDistributedMessage.h>
#include <dtkDistributed/dtkDistributedWork.h>
#include <dtkDistributed/dtkDistributedWorker.h>
#include <dtkDistributed/dtkDistributedWorkerManager.h>
#include <dtkLog/dtkLogger.h>

#include <QCoreApplication>

#include <iostream>

class simpleWork : public dtkDistributedWork
{
public:
    simpleWork *clone(void) { return new simpleWork(*this); };

public:
    void run(void) {

        QTime time;
        qDebug() << wid();
        qDebug() << wct();

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "Running on master, connect to remote server" ;


        DTK_DISTRIBUTED_END_GLOBAL;

        qDebug() << "I'm the simple slave " << wid() ;

        QThread::sleep(60);

    }
};

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);


    QUrl url;
    if (dtkApplicationArgumentsContain(qApp,"--server")) {
        url=QUrl(dtkApplicationArgumentsValue(qApp,"--server"));
    } else {
        qCritical() << "no server set! use --server <url> " ;
        return 1;
    }

    dtkDistributedSlave slave;
    slave.connect(url);

    std::cout << QString("DTK_JOBID="+slave.jobId()).toStdString() << std::endl << std::flush;

    // the server waits for the jobid in stdout
    qDebug() << "slave connected to server " << slave.isConnected();

    if (slave.isConnected()) {
        dtkDistributedMessage msg(dtkDistributedMessage::STARTJOB,slave.jobId(),0);
        msg.send(slave.socket());
    }

    // plugins

    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    qDebug() << "initialize plugin manager "<< settings.value("plugins").toString();
    dtkDistributed::communicator::pluginManager().initialize(settings.value("plugins").toString());
    qDebug() << "initialization done ";
    settings.endGroup();

    qDebug() << dtkDistributed::communicator::pluginManager().plugins();
    qDebug() << dtkDistributed::communicator::pluginFactory().keys();


    // work

    simpleWork *work = new simpleWork;

    dtkDistributedPolicy policy;

    QString policyType = "qthread";
    if (dtkApplicationArgumentsContain(qApp,"--policy")) {
        policyType = dtkApplicationArgumentsValue(qApp,"--policy");
    }
    policy.setType(policyType);

    dtkDistributedWorkerManager manager;

    manager.setPolicy(&policy);
    manager.spawn();
    manager.exec(work);

    return 0;
}
