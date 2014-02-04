/* dtkDistributedSocket.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: 2011/09/20 09:16:29
 * Version: $Id$
 * Last-Updated: lun. févr.  3 16:40:59 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 816
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedSocket.h"

#include <dtkCoreSupport/dtkAbstractData.h>
#include <dtkCoreSupport/dtkAbstractDataFactory.h>
#include <dtkCoreSupport/dtkGlobal.h>

// #include <dtkMath/dtkMath.h>

#include <dtkLog/dtkLogger.h>

class dtkDistributedSocketPrivate
{
};

dtkDistributedSocket::dtkDistributedSocket( QObject* parent ) :  QTcpSocket(parent), d(new dtkDistributedSocketPrivate)
{
}

dtkDistributedSocket::~dtkDistributedSocket(void)
{
    delete d;
    d = NULL;
}


// force flush
void dtkDistributedSocket::fflush(void)
{
    while (this->bytesToWrite() > 0) {
        this->flush();
        this->waitForBytesWritten();
    }
}

qint64 dtkDistributedSocket::sendRequest( dtkDistributedMessage *msg)
{

    QString buffer;

    buffer += msg->req();
    if (msg->size() == 0 ) {
        buffer += "content-size: 0\n\n";
        qint64 ret = this->write(buffer.toUtf8());
        this->flush();
        return ret;
    } else if (msg->size() > 0) {
        buffer += "content-size: "+ QString::number(msg->size()) +"\n";
        if (!msg->type().isEmpty() && !msg->type().isNull())
            buffer += "content-type: " +msg->type() +"\n";

        foreach (const QString &key, (msg->headers()).keys())
            buffer += key +": " + msg->header(key) +"\n";
        buffer += "\n";
    }

    qint64 ret;
    if (msg->content().isNull() || msg->content().isEmpty()) {
        // no content provided, the caller is supposed to send the content itself
        ret = this->write(buffer.toUtf8());
    } else {
        ret = this->write(buffer.toUtf8());
        ret += this->write(msg->content());
    }

    return ret;
}

/**
 * read and parse data from socket
 *
 * @return dtkDistributedMessage
 */
dtkDistributedMessage *dtkDistributedSocket::parseRequest(void)
{
    dtkDistributedMessage *msg = new dtkDistributedMessage;

    msg->setMethod(this->readLine());

    // read content-size
    msg->setSize(this->readLine());

    if (msg->size() > 0) {
        //read content-type
        msg->setType(this->readLine());

        // read optional headers
        QByteArray line = this->readLine();
        while (!QString(line).trimmed().isEmpty()) {// empty line after last header
            msg->setHeader(QString(line));
            line=this->readLine();
        }

        // read content
        QByteArray buffer;
        buffer.append(this->read(msg->size()));
        while (buffer.size() < msg->size() ) {
            if (this->waitForReadyRead()) {
                buffer.append(this->read(msg->size()-buffer.size()));
            } else {
                dtkWarning() << "not enough data received, only  " << buffer.size() << "out of " << msg->size() ;
                msg->setContent(buffer);
                msg->addHeader("missing_data",QString::number(msg->size()-buffer.size()));
                break;
            }
        }
        msg->setContent(buffer);
    } else
        // end of request == empty line
        this->readLine();

    return msg;
}
