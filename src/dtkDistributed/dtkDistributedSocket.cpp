/* dtkDistributedSocket.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: 2011/09/20 09:16:29
 * Version: $Id$
 * Last-Updated: mer. mai 30 14:55:38 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 791
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedSocket.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkMath/dtkMath.h>

#include <dtkLog/dtkLog.h>

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

void dtkDistributedSocket::send(dtkAbstractData *data, QString jobid, qint16 target)
{
    QByteArray *array;
    QString type = "dtkAbstractData/"+data->identifier();

    array = data->serialize();
    if (!array->isNull()) {
        dtkDistributedMessage msg = dtkDistributedMessage(dtkDistributedMessage::DATA,jobid, target, array->size(), type);
        this->sendRequest(&msg);
        this->write(*array);
    } else {
        dtkError() << "serialization failed";
    }
}

void dtkDistributedSocket::send(QVariant variant, QString jobid, qint16 target)
{
    QByteArray *array;

    QString type = variant.typeName();

    if(type == "dtkVector3DReal") {
        dtkVector3DReal v = variant.value<dtkVector3DReal>();
        array = new QByteArray;
        QDataStream stream(array, QIODevice::WriteOnly);
        stream << v[0] << v[1] << v[2];

    } else if(type == "dtkVectorReal") {
        dtkVectorReal v = variant.value<dtkVectorReal>();
        int size = v.getRows();
        array = new QByteArray;
        QDataStream stream(array, QIODevice::WriteOnly);
        stream << size ;
        for  (int i =0; i < size ; i++)
            stream << v[i] ;

    } else if(type == "dtkQuaternionReal") {
        dtkQuaternionReal v = variant.value<dtkQuaternionReal>();
        array = new QByteArray;
        QDataStream stream(array, QIODevice::WriteOnly);
        stream << v[0] << v[1] << v[2] << v[3];

    } else {
        if (type != "dtkAbstractData")
            dtkInfo() << "type is unknown ("<< type<<  "), assume it inherit from dtkAbstractData";
        if (type.endsWith("*")) { // pointer, remote the * character
            type.chop(1);
            dtkDebug() << "pointer type, remove *"<< type;
        }
        dtkAbstractData *data = dtkAbstractDataFactory::instance()->create(type)->fromVariant(variant);
        qDebug() << __func__ << data->identifier();
        array = data->serialize();
    }

    if (!array->isNull()) {
        dtkTrace() << "Array size is"<< array->size();
        dtkDistributedMessage msg = dtkDistributedMessage(dtkDistributedMessage::DATA,jobid, target, array->size(), type);
        this->sendRequest(&msg);
        this->write(*array);
        this->flush();
    } else {
        dtkError() << "serialization failed";
    }
}

qint64 dtkDistributedSocket::sendRequest( dtkDistributedMessage *msg)
{

    QString buffer;

    buffer += msg->req();
    if (msg->size() == 0 ) {
        buffer += "content-size: 0\n\n";
        qint64 ret = this->write(buffer.toAscii());
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
        ret = this->write(buffer.toAscii());
    } else {
        ret = this->write(buffer.toAscii());
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
                dtkWarn() << "not enough data received, only  " << buffer.size() << "out of " << msg->size() ;
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
