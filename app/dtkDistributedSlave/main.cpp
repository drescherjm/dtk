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




#include <dtkDistributed>
#include <dtkLog>

#include <QtCore>

#include <iostream>

class slaveWork : public QRunnable
{
public:
    QString server;

public:
    void run(void) {
        QTime time;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qDebug() << comm->wid();
        qDebug() << comm->size();
        dtkDistributedSlave slave;

        if (dtkDistributed::app()->isMaster()) {
            // the server waits for the jobid in stdout
            std::cout << QString("DTK_JOBID="+dtkDistributedSlave::jobId()).toStdString() << std::endl << std::flush;

            QUrl url(server);

            qDebug() << "Running on master, connect to remote server" << server;
            slave.connect(url);
            qDebug() << "slave connected to server " << slave.isConnected();

            if (slave.isConnected()) {
                dtkDistributedMessage msg(dtkDistributedMessage::SETRANK,slave.jobId(),dtkDistributedMessage::SLAVE_RANK);
                msg.send(slave.socket());
            }

        }

        qDebug() << "I'm the simple slave " << comm->wid() ;

        QThread::sleep(5);

        if (dtkDistributed::app()->isMaster()) {
            if (slave.isConnected()) {
                dtkDistributedMessage msg(dtkDistributedMessage::ENDJOB,slave.jobId(),dtkDistributedMessage::SLAVE_RANK);
                msg.send(slave.socket());
            }
        }

    }
};

int main(int argc, char **argv)
{
    dtkDistributedCoreApplication application(argc, argv);
    application.setApplicationName("dtkDistributedSlave");
    application.setApplicationVersion("1.0.0");


    QCommandLineParser *parser = application.parser();
    parser->setApplicationDescription("DTK distributed slave example application: it connect to the DTK distributed server and waits for 1 minute before exiting.");

    QCommandLineOption serverOption("server", "DTK distributed server URL", "URL");
    parser->addOption(serverOption);

    application.initialize();

     if (!parser->isSet(serverOption)) {
         qCritical() << "Error: no server set ! Use --server <url> " ;
         return 1;
     }


    // work
    slaveWork work;
    work.server = parser->value(serverOption);

    application.exec(&work);

    return 0;
}
