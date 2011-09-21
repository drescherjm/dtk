/* dtkDistributedSlave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. sept. 21 10:08:02 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 107
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedSlave.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkGlobal.h>

#include <QtNetwork>

class dtkDistributedSlavePrivate : public dtkDistributedSocket
{
public:
    dtkDistributedSocket *socket;
};

dtkDistributedSlave::dtkDistributedSlave(void) : d(new dtkDistributedSlavePrivate)
{
    d->socket = new dtkDistributedSocket(this);
}

dtkDistributedSlave::~dtkDistributedSlave(void)
{
    delete d;

    d = NULL;
}

int dtkDistributedSlave::run(void)
{
    this->onStarted();

    int status = this->exec();

    this->onEnded();

    return status;
}

int dtkDistributedSlave::exec(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return DTK_FAILURE;
}

bool dtkDistributedSlave::isConnected(void)
{
    return (d->socket->state() == QAbstractSocket::ConnectedState);
}

bool dtkDistributedSlave::isDisconnected(void)
{
    return (d->socket->state() == QAbstractSocket::UnconnectedState);
}

void dtkDistributedSlave::connect(const QUrl& server)
{
    d->socket->connectToHost(server.host(), server.port());

    if(d->socket->waitForConnected()) {

        QObject::connect(d->socket, SIGNAL(readyRead()), this, SLOT(read()));
        QObject::connect(d->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

        emit connected(server);

    } else {
        qDebug() << "Unable to connect to" << server.toString();
    }
}

void dtkDistributedSlave::disconnect(const QUrl& server)
{
    d->socket->disconnectFromHost();

    emit disconnected(server);
}

void dtkDistributedSlave::onStarted(void)
{
    QString jobid = "unknown"; //FIXME
    d->socket->sendRequest("STARTED","/job/"+jobid);
}

void dtkDistributedSlave::onEnded(void)
{
    QString jobid = "unknown"; //FIXME
    d->socket->sendRequest("ENDED","/job/"+jobid);
}

void dtkDistributedSlave::read(void)
{
    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();

    Q_UNUSED(socket);
}

void dtkDistributedSlave::write(const QByteArray& array)
{
    d->socket->write(array);
}

qint64 dtkDistributedSlave::sendRequest(QString method, QString path, int size , QString type, const QByteArray& content,  const QHash<QString,QString>& headers )
{
    return d->socket->sendRequest(method,path,size,type,content,headers);
}

bool  dtkDistributedSlave::flush(void)
{
    return d->socket->flush();
}

void  dtkDistributedSlave::close(void)
{
    return d->socket->close();
}


void dtkDistributedSlave::error(QAbstractSocket::SocketError error)
{
    switch(error) {
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << DTK_PRETTY_FUNCTION << "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << DTK_PRETTY_FUNCTION << "The remote host closed the connection. Note that the slave socket (i.e., this socket) will be closed after the remote close notification has been sent.";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << DTK_PRETTY_FUNCTION << "The host address was not found.";
        break;
    case QAbstractSocket::SocketAccessError:
        qDebug() << DTK_PRETTY_FUNCTION << "The socket operation failed because the application lacked the required privileges.";
        break;
    case QAbstractSocket::SocketResourceError:
        qDebug() << DTK_PRETTY_FUNCTION << "The local system ran out of resources (e.g., too many sockets).";
        break;
    case QAbstractSocket::SocketTimeoutError:
        qDebug() << DTK_PRETTY_FUNCTION << "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        qDebug() << DTK_PRETTY_FUNCTION << "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
        break;
    case QAbstractSocket::NetworkError:
        qDebug() << DTK_PRETTY_FUNCTION << "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
        break;
    case QAbstractSocket::AddressInUseError:
        qDebug() << DTK_PRETTY_FUNCTION << "The address specified to QUdpSocket::bind() is already in use and was set to be exclusive.";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        qDebug() << DTK_PRETTY_FUNCTION << "The address specified to QUdpSocket::bind() does not belong to the host.";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        qDebug() << DTK_PRETTY_FUNCTION << "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        qDebug() << DTK_PRETTY_FUNCTION << "The socket is using a proxy, and the proxy requires authentication.";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        qDebug() << DTK_PRETTY_FUNCTION << "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        qDebug() << DTK_PRETTY_FUNCTION << "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background).";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        qDebug() << DTK_PRETTY_FUNCTION << "Could not contact the proxy server because the connection to that server was denied";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        qDebug() << DTK_PRETTY_FUNCTION << "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        qDebug() << DTK_PRETTY_FUNCTION << "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase.";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        qDebug() << DTK_PRETTY_FUNCTION << "The proxy address set with setProxy() (or the application proxy) was not found.";
        break;
    case QAbstractSocket::ProxyProtocolError:
        qDebug() << DTK_PRETTY_FUNCTION << "The connection negotiation with the proxy server because the response from the proxy server could not be understood.";
        break;
    case QAbstractSocket::UnknownSocketError:
        qDebug() << DTK_PRETTY_FUNCTION << "An unidentified error occurred.";
        break;
    default:
        break;
    }
}
