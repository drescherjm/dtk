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

class slaveWork : public QRunnable
{
public:
    QString server;

public:
    void run(void) {
        QTime time;
        dtkDistributedCommunicator *comm = dtkDistributed::communicator::instance();
        qDebug() << comm->wid();
        qDebug() << comm->size();
        dtkDistributedSlave slave;

        slave.connectFromJob(server);
        qDebug() << "I'm the simple slave " << comm->wid() ;

        QThread::sleep(5);

        slave.disconnectFromJob(server);
    }
};

int main(int argc, char **argv)
{
    dtkDistributedAbstractApplication *app = dtkDistributed::create(argc, argv);
    app->setApplicationName("dtkDistributedSlave");
    app->setApplicationVersion("1.0.0");

    QCommandLineParser *parser = app->parser();
    parser->setApplicationDescription("DTK distributed slave example application: it connect to the DTK distributed server and waits for 1 minute before exiting.");

    QCommandLineOption serverOption("server", "DTK distributed server URL", "URL");
    parser->addOption(serverOption);

    app->initialize();

     if (!parser->isSet(serverOption)) {
         qCritical() << "Error: no server set ! Use --server <url> " ;
         return 1;
     }


    // work
    slaveWork work;
    work.server = parser->value(serverOption);

    app->spawn();
    app->exec(&work);
    app->unspawn();

    return 0;
}
