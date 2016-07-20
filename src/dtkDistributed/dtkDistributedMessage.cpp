/* dtkDistributedMessage.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: mar. oct. 11 10:46:57 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:18:12 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 376
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedMessage.h"

#include <dtkCore/dtkCore.h>
#include <dtkMeta/dtkMeta.h>

#include <dtkLog>

class dtkDistributedMessagePrivate
{
public:
    dtkDistributedMessage::Method method;
    QString jobid;
    int rank ;
    dtkDistributedMessage::dtkDistributedHeaders headers;
    qint64 size ;
    QString type;
    QByteArray content;
    QVariant variant;
};


/*! \class dtkDistributedMessage
    \inmodule dtkDistributed

    \brief dtkDistributedMessage encapsulate the JSON based protocol used between the client and the resource manager in a high level C++ API.
*/

dtkDistributedMessage::dtkDistributedMessage(void) :  d(new dtkDistributedMessagePrivate)
{
}

dtkDistributedMessage::~dtkDistributedMessage(void)
{
    delete d;
}


dtkDistributedMessage::dtkDistributedMessage(Method method, QString jobid, int rank, qint64 size, QString type, const QByteArray&  content,  const QHash<QString, QString>&  headers ) :  d(new dtkDistributedMessagePrivate)
{
    d->method = method;
    d->size = size;
    d->type = type;
    d->jobid = jobid;
    d->rank = rank;
    d->headers = headers;
    d->content = content;

}

dtkDistributedMessage::dtkDistributedMessage(Method method, QString jobid, int rank, const QVariant&  v, const QHash<QString, QString>&  headers ) :  d(new dtkDistributedMessagePrivate)
{
    d->method = method;
    d->jobid = jobid;
    d->rank = rank;
    d->headers = headers;
    QDataStream stream(&d->content, QIODevice::WriteOnly);
    stream << v;
    d->size = d->content.size();
    d->type = "qvariant";

}

// set method, and also, if necessary, jobid and rank
void dtkDistributedMessage::setMethod(QString method)
{
    QStringList tokens = QString(method).split(QRegExp("/"));

    if (method.startsWith("GET /status")) {
        d->method = STATUS;
    } else if (method.startsWith("PUT /job HTTP")) {
        d->method = NEWJOB;
    } else if (method.startsWith("DELETE /job")) {
        d->jobid  = tokens[2].remove("HTTP").trimmed();

        if (d->headers.contains("x-dtk-finished")) {
            d->method = ENDJOB;
        } else {
            d->method = DELJOB;
        }
    } else if (method.startsWith("DELETE /")) {
        d->method = STOP;
    } else if (method.startsWith("POST /data")) {
        d->method = DATA;
        d->jobid  = tokens[2];

        if (tokens.size() > 2)
            d->rank  = tokens[3].remove("HTTP").toInt();
    } else if (method.startsWith("PUT /rank")) {
        d->method = SETRANK;
        d->jobid  = tokens[2];
        d->rank   = tokens[3].remove("HTTP").toInt();
    } else if (method.startsWith("HTTP/1.1 200 OK")) {
        if (d->headers.contains("x-dtk-status")) {
            d->method = OKSTATUS;
        } else {
            dtkWarn() << "Unsupported method " << method;
        }
    } else if (method.startsWith("HTTP/1.1 201 OK")) {
        d->method = OKJOB;
    } else if (method.startsWith("HTTP/1.1 204 OK")) {
        d->method = OKDEL;
    } else if (method.startsWith("HTTP/1.1 400 OK")) {
        d->method = ERRORJOB;
    } else if (method.startsWith("HTTP/1.1 410 OK")) {
        d->method = ERRORDEL;
    } else {
        dtkWarn() << "Unsupported method " << method;
    }

}

void dtkDistributedMessage::setSize(void)
{
    if (d->headers.contains("content-length")) {
        d->size = d->headers["content-length"].toInt();
    } else {
        d->size = -1;
    }
}

void dtkDistributedMessage::setType(void)
{
    if (d->headers.contains("content-type")) {
        d->type = d->headers["content-type"].trimmed();
    } else {
        d->type = "unknown";
    }
}

void dtkDistributedMessage::setContent(QByteArray& content)
{
    d->size    = content.size();
    d->content = content;
}

void dtkDistributedMessage::setHeader(const QString& headerString)
{
    QStringList tokens = headerString.split(QRegExp(":\\s*"));
    d->headers.insert(tokens[0].toLower(), tokens[1].trimmed());
}

void dtkDistributedMessage::addHeader(QString name, QString value)
{
    d->headers.insert(name, value);
}

dtkDistributedMessage::Method dtkDistributedMessage::method(void)
{
    return d->method;
}

QString dtkDistributedMessage::methodString(void)
{
    switch (d->method) {
    case STATUS:   return "STATUS";

    case OKSTATUS: return "OKSTATUS";

    case NEWJOB:   return "NEWJOB";

    case OKJOB:    return "OKJOB";

    case ERRORJOB: return "ERRORJOB";

    case DELJOB:   return "DELJOB";

    case OKDEL:    return "OKDEL";

    case ERRORDEL: return "ERRORDEL";

    case ENDJOB:   return "ENDJOB";

    case DATA:     return "DATA";

    case SETRANK:  return "SETRANK";

    case STOP:     return "STOP";

    case ERROR_UNKNOWN: return "ERROR_UNKNOWN";

    default: return "Unsupported method";
    };
}

QString dtkDistributedMessage::req(void)
{
    QString req;

    switch (d->method) {
    case STATUS:
        req = "GET /status HTTP/1.1";
        break;

    case OKSTATUS:
        req = "HTTP/1.1 200 OK\nX-DTK-Status: OK";
        break;

    case NEWJOB:
        req = "PUT /job HTTP/1.1";
        break;

    case OKJOB:
        req = "HTTP/1.1 201 OK\nX-DTK-JobId: " + d->jobid;
        break;

    case ERRORJOB:
        req = "HTTP/1.1 400 OK";
        break;

    case DELJOB:
        req = "DELETE /job/" + d->jobid + " HTTP/1.1";
        break;

    case OKDEL:
        req = "HTTP/1.1 204 OK\nX-DTK-JobId: " + d->jobid;
        break;

    case ERRORDEL:
        req = "HTTP/1.1 410 OK\nX-DTK-JobId: " + d->jobid;
        break;

    case ENDJOB:
        req = "DELETE /job/" + d->jobid + "\nX-DTK-Finished: " + d->jobid;
        break;

    case DATA:
        req = "POST /data/" + d->jobid + "/" + QString::number(d->rank)  + " HTTP/1.1" ;
        break;

    case SETRANK:
        req = "PUT /rank/" + d->jobid + "/" + QString::number(d->rank) + " HTTP/1.1" ;
        break;

    case STOP:
        req = "DELETE / HTTP/1.1" ;
        break;

    case ERROR_UNKNOWN:
        req = "HTTP/1.1 404 OK" ;
        break;

    default:
        dtkWarn() << "Unsupported method";
    };

    return req + "\n";
}

QString dtkDistributedMessage::jobid(void)
{
    return d->jobid;
}

int  dtkDistributedMessage::rank(void)
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

QByteArray& dtkDistributedMessage::content(void)
{
    return d->content;
}

QVariant& dtkDistributedMessage::variant(void)
{
    d->variant.clear();
    QDataStream stream(&(d->content), QIODevice::ReadOnly);
    stream >> d->variant;
    return d->variant;
}

qlonglong dtkDistributedMessage::send(QTcpSocket *socket)
{
    QString buffer;
    qlonglong ret;

    buffer += this->req();

    if (d->size == 0 ) {
        buffer += "Content-Length: 0\n\n";
        ret = socket->write(buffer.toUtf8());
        socket->flush();
        return ret;
    } else if (d->size > 0) {
        buffer += "Content-Length: " + QString::number(d->size) + "\n";

        if (!d->type.isEmpty() && !d->type.isNull())
            buffer += "Content-Type: " + d->type + "\n";

        foreach (const QString& key, d->headers.keys() ) {
            if ((key != "content-length") && (key != "content-type" )) {
                buffer += key + ": " + d->headers[key] + "\n";
            }
        }

        buffer += "\n";
    }

    if (d->content.isNull() || d->content.isEmpty()) {
        // no content provided, the caller is supposed to send the content itself
        ret = socket->write(buffer.toUtf8());
    } else {
        ret = socket->write(buffer.toUtf8());
        ret += socket->write(d->content);
    }

    return ret;
}

qlonglong dtkDistributedMessage::parse(QTcpSocket *socket)
{
    QString resp = socket->readLine();
    dtkTrace() << "parse first line" << resp;

    // read optional headers
    QByteArray line = socket->readLine();
    dtkTrace() << "parse second line" << line;

    while (!QString(line).trimmed().isEmpty()) {// empty line after last header
        this->setHeader(QString(line));
        line = socket->readLine();
        dtkTrace() << "parse: line" << line;
    }

    this->setMethod(resp);

    this->setSize();

    if (d->headers.contains("x-dtk-jobid")) {
        d->jobid = d->headers["x-dtk-jobid"].trimmed();;
    }

    dtkTrace() << "parse: jobid is" << d->jobid << "size:" << d->size << "method:" << this->methodString();

    if (d->size > 0) {
        //read content-type
        this->setType();

        dtkTrace() << "parse: read content" << d->size ;
        // read content
        QByteArray buffer;
        buffer.append(socket->read(d->size));

        while (buffer.size() < d->size ) {
            if (socket->waitForReadyRead()) {
                buffer.append(socket->read(d->size - buffer.size()));
            } else {
                dtkWarn() << "not enough data received, only  " << buffer.size() << "out of " << d->size ;
                this->setContent(buffer);
                this->addHeader("missing_data", QString::number(d->size - buffer.size()));
                break;
            }
        }

        dtkTrace() << "parse: set content" << buffer.size() ;
        this->setContent(buffer);
    }

    return 0;
}
