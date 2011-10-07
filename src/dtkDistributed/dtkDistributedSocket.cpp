/* dtkDistributedSocket.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: 2011/09/20 09:16:29
 * Version: $Id$
 * Last-Updated: ven. oct.  7 09:47:17 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 564
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkGlobal.h>

#include "dtkDistributedSocket.h"

class dtkDistributedSocketPrivate
{
public:
    QVariantMap *request;
};

dtkDistributedSocket::dtkDistributedSocket( QObject* parent ) :  d(new dtkDistributedSocketPrivate), QTcpSocket(parent)
{
}

dtkDistributedSocket::~dtkDistributedSocket( )
{
    delete d;
    d = NULL;
}


qint64 dtkDistributedSocket::sendRequest(QString method, QString path, qint64 size, QString type, const QByteArray  &content,  const QHash<QString,QString>  &headers )
{

    QString buffer;

    buffer += method +" "+ path +"\n";
    if (size == 0 ) {
        buffer += "content-size: 0\n\n";
        qint64 ret = this->write(buffer.toAscii());
        this->flush();
        return ret;
    } else if (size > 0) {
        buffer += "content-size: "+ QString::number(size) +"\n";
        if (!type.isEmpty() && !type.isNull())
            buffer += "content-type: " +type +"\n";

        foreach (const QString &key, headers.keys())
            buffer += key +": " + headers[key] +"\n";
        buffer += "\n";
    }

    qint64 ret;
    if (content.isNull() || content.isEmpty()) {
        // no content provided, the caller is supposed to send the content itself
        ret = this->write(buffer.toAscii());
    } else {
        ret = this->write(buffer.toAscii() + content);
        this->flush();
    }

    return ret;
}

/**
 * read and parse data from socket
 *
 * @return QVariantMap
 */
QVariantMap dtkDistributedSocket::parseRequest(void)
{
    QStringList tokens = QString(this->readLine()).split(" ");
    QVariantMap request;
    request.insert("method", tokens[0]);
    request.insert("path", tokens[1].trimmed());

    // read content-size
    tokens = QString(this->readLine()).split(QRegExp(":\\s*"));
    if (tokens[0].toLower() != "content-size") {
        request.insert("error", "No Content Size");
        return request;
    }

    int size = tokens[1].toInt();
    request.insert("size", size);

    if (size > 0) {
        //read content-type
        tokens = QString(this->readLine()).split(QRegExp(":\\s*"));

        if (tokens[0].toLower() != "content-type") {
            request.insert("error", "No Content Type");
            return request;
        }

        request.insert("type", tokens[1].trimmed());

        // read optional headers
        QByteArray line = this->readLine();
        while (!QString(line).trimmed().isEmpty()) {// empty line after last header
            tokens = QString(line).split(QRegExp(":\\s*"));
            request.insert(tokens[0], tokens[1].trimmed());
            line=this->readLine();
        }

        // read content
        QByteArray buffer;
        buffer.append(this->read(size));
        while (buffer.size() < size ) {
            if (this->waitForReadyRead()) {
                buffer.append(this->read(size-buffer.size()));
            } else {
                qDebug() << "not enough data received, only  " << buffer.size() << "out of " << size ;
                request.insert("content", buffer);
                request.insert("missing_data", size-buffer.size());
                break;
            }
        }
        request.insert("content", buffer);
    } else
        // end of request == empty line
        this->readLine();

    return request;
}
