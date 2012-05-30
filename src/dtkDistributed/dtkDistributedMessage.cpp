/* dtkDistributedMessage.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: mar. oct. 11 10:46:57 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. mai 30 12:56:16 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 358
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedMessage.h"

#include <dtkComposer/dtkComposerTransmitterVariant.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

#include <dtkLog/dtkLog.h>

#include <dtkMath/dtkMath.h>

class dtkDistributedMessagePrivate
{
public:
    dtkDistributedMessage::Method method;
    QString jobid;
    qint16 rank ;
    dtkDistributedMessage::dtkDistributedHeaders headers;
    qint64 size ;
    QString type;
    QByteArray content;
};

dtkDistributedMessage::dtkDistributedMessage(void) :  d(new dtkDistributedMessagePrivate)
{
}

dtkDistributedMessage::~dtkDistributedMessage(void)
{
    delete d;
}


dtkDistributedMessage::dtkDistributedMessage(Method method, QString jobid, qint16 rank, qint64 size, QString type, const QByteArray  &content,  const QHash<QString,QString>  &headers ) :  d(new dtkDistributedMessagePrivate)
{
    d->method = method;
    d->size = size;
    d->type = type;
    d->jobid = jobid;
    d->rank = rank;
    d->headers = headers;
    d->content = content;

}

// set method, and also, if necessary, jobid and rank
void dtkDistributedMessage::setMethod(QString method)
{
    QStringList tokens = QString(method).split(QRegExp("/"));
    if (method.startsWith("GET /status")) {
        d->method = STATUS;
    } else if (method.startsWith("OK /status")) {
        d->method = OKSTATUS;
    } else if (method.startsWith("PUT /job")) {
        d->method = NEWJOB;
    } else if (method.startsWith("OK /job")) {
        d->method = OKJOB;
        d->jobid  = tokens[2].trimmed();
    } else if (method.startsWith("DELETE /job")) {
        d->method = DELJOB;
        d->jobid  = tokens[2].trimmed();
    } else if (method.startsWith("OK /deleted")) {
        d->method = OKDEL;
        d->jobid  = tokens[2].trimmed();
    } else if (method.startsWith("ERROR /deleted")) {
        d->method = ERRORDEL;
        d->jobid  = tokens[2].trimmed();
    } else if (method.startsWith("STARTED /job")) {
        d->method = STARTJOB;
        d->jobid  = tokens[2].trimmed();
    } else if (method.startsWith("ENDED /job")) {
        d->method = ENDJOB;
        d->jobid  = tokens[2].trimmed();
    } else if (method.startsWith("POST /data")) {
        d->method = DATA;
        d->jobid  = tokens[2];
        if (tokens.size() > 2)
            d->rank  = tokens[3].toInt();
    } else if (method.startsWith("PUT /rank")) {
        d->method = SETRANK;
        d->jobid  = tokens[2];
        d->rank   = tokens[3].toInt();
    } else
        dtkWarn() << DTK_PRETTY_FUNCTION << "Unsupported method " << method;

}

void dtkDistributedMessage::setSize(const QString &header)
{
    QStringList tokens = header.split(QRegExp(":\\s*"));
    if (tokens[0].toLower() != "content-size") {
        dtkWarn() << "Error: Not a size header ! " << header;
        d->size = -1;
    } else
        d->size = tokens[1].toInt();
}

void dtkDistributedMessage::setType(const QString &header)
{
    QStringList tokens = header.split(QRegExp(":\\s*"));
    if (tokens[0].toLower() != "content-type") {
        dtkWarn() << "Error: Not a content type header ! " << header;
        d->type = "unknown";
    } else
        d->type = tokens[1].trimmed();
}

void dtkDistributedMessage::setContent(QByteArray &content)
{
    d->size    = content.size();
    d->content = content;
}

void dtkDistributedMessage::setHeader(const QString &headerString)
{
    QStringList tokens = headerString.split(QRegExp(":\\s*"));
    d->headers.insert(tokens[0], tokens[1].trimmed());
}

void dtkDistributedMessage::addHeader(QString name, QString value)
{
    d->headers.insert(name, value);
}

dtkDistributedMessage::Method dtkDistributedMessage::method(void)
{
    return d->method;
}

QString dtkDistributedMessage::req(void)
{
    QString req;
    switch (d->method) {
        case STATUS:
            req = "GET /status";
            break;
        case OKSTATUS:
            req = "OK /status/"+d->jobid;
            break;
        case NEWJOB:
            req = "PUT /job";
            break;
        case OKJOB:
            req = "OK /job/"+d->jobid;
            break;
        case DELJOB:
            req = "DELETE /job/"+d->jobid;
            break;
        case OKDEL:
            req = "OK /deleted/"+d->jobid;
            break;
        case ERRORDEL:
            req = "ERROR /deleted/"+d->jobid;
            break;
        case STARTJOB:
            req = "STARTED /job/"+d->jobid;
            break;
        case ENDJOB:
            req = "ENDED /job/"+d->jobid;
            break;
        case DATA:
            req = "POST /data/"+d->jobid+"/"+QString::number(d->rank) ;
            break;
        case SETRANK:
            req = "PUT /rank/"+d->jobid +"/"+QString::number(d->rank) ;
            break;
        default:
            dtkWarn() << "Unsupported method";
        };
    return req +"\n";
}

QString dtkDistributedMessage::jobid(void)
{
    return d->jobid;
}

qint16  dtkDistributedMessage::rank(void)
{
    return d->rank;
}

dtkDistributedMessage::dtkDistributedHeaders dtkDistributedMessage::headers()
{
    return d->headers;
}

QString dtkDistributedMessage::header(const QString& name)
{
    return d->headers[name];
}

QString dtkDistributedMessage::type(void)
{
    return d->type;
}

qint64  dtkDistributedMessage::size(void)
{
    return d->size;
}

QByteArray &dtkDistributedMessage::content(void)
{
    return d->content;
}

void dtkDistributedMessage::setTransmitterVariant(dtkComposerTransmitterVariant *t)
{

    if (d->type == "double") {
        double *data = reinterpret_cast<double*>(d->content.data());
        t->setTwinned(false);
        t->setData(*data);
        t->setTwinned(true);
    } else if (d->type == "qlonglong") {
        qlonglong *data = reinterpret_cast<qlonglong*>(d->content.data());
        t->setTwinned(false);
        t->setData(*data);
        t->setTwinned(true);
    } else if (d->type == "qstring") {
        t->setTwinned(false);
        t->setData(QString(d->content));
        t->setTwinned(true);
    } else if (d->type == "dtkVectorReal") {

        if (d->size > 0) {
            QByteArray array = d->content;
            int size;
            QDataStream stream(&array, QIODevice::ReadOnly);
            stream >> size;
            dtkVectorReal v(size);

            for (int i=0; i< size; i++)
                stream >> v[i];

            t->setTwinned(false);
            t->setData(qVariantFromValue(v));
            t->setTwinned(true);


            dtkDebug() << "received dtkVectorReal, set data in transmitter" << size;

        } else
            dtkWarn() << "warning: no content in dtkVectorReal transmitter";


    } else if (d->type == "dtkVector3DReal") {

        if (d->size > 0) {
            dtkVector3DReal v;

            QDataStream stream(&(d->content), QIODevice::ReadOnly);
            stream >> v[0];
            stream >> v[1];
            stream >> v[2];

            t->setTwinned(false);
            t->setData(qVariantFromValue(v));
            t->setTwinned(true);

            dtkDebug() << "received dtkVector3DReal, set data in transmitter" << v[0] << v[1] << v[2];

        } else
            dtkWarn() << "warning: no content in dtkVector3DReal transmitter";

    } else if (d->type == "dtkQuaternionReal") {

        if (d->size > 0) {
            dtkQuaternionReal q;

            QDataStream stream(&(d->content), QIODevice::ReadOnly);
            stream >> q[0];
            stream >> q[1];
            stream >> q[2];
            stream >> q[3];

            t->setTwinned(false);
            t->setData(qVariantFromValue(q));
            t->setTwinned(true);

            dtkDebug() << "received dtkQuaternionReal, set data in transmitter" << q[0] << q[1] << q[2] << q[3];

        } else
            dtkWarn() << "warning: no content in dtkQuaternionReal transmitter";

    } else { // assume a dtkAbstractData
        dtkDebug() << "received dtkAbstractData, deserialize";
        if (d->size > 0) {
            dtkAbstractData *data;
            data = dtkAbstractDataFactory::instance()->create(d->type)->deserialize(d->content);
            if (!data) {
                dtkError() << "Deserialization failed";
            } else {
                t->setTwinned(false);
                t->setData(qVariantFromValue(data));
                t->setTwinned(true);
            }
        } else
            dtkWarn() << "warning: no content in dtkAbstractData transmitter";
    }
}
