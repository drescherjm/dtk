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
#include <dtkDistributed/dtkDistributedSlave.h>
#include <dtkDistributed/dtkDistributedMessage.h>
#include <dtkLog/dtkLogger.h>

#include <QCoreApplication>

class simpleSlave : public dtkDistributedSlave
{
public:
    int exec(void) {
        if (this->isConnected()) {
            dtkDistributedMessage msg(dtkDistributedMessage::STARTJOB,this->jobId(),0);
            msg.send(this->socket());
        }
        qDebug() << "I'm the simple slave" ;
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

    qDebug() << "slave connecting to server " << url;


    simpleSlave *slave = new simpleSlave;
    slave->connect(url);
    qDebug() << "slave connected to server " << slave->isConnected();

    int status = slave->exec();

    delete slave;

    return status;
}
