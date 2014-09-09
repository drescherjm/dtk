/* dtkDistributedSlave.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedMessage.h"
#include "dtkDistributedSlave.h"

#include <dtkCore>
#include <dtkLog>

#include <QtNetwork>

class dtkDistributedSlavePrivate
{
public:
    QTcpSocket *socket;
};

dtkDistributedSlave::dtkDistributedSlave(void) : d(new dtkDistributedSlavePrivate)
{
    d->socket = new QTcpSocket;
}

dtkDistributedSlave::dtkDistributedSlave(QTcpSocket *socket) : d(new dtkDistributedSlavePrivate)
{
    d->socket = socket;
}

dtkDistributedSlave::~dtkDistributedSlave(void)
{
    delete d;

    d = NULL;
}

QString dtkDistributedSlave::jobId(void)
{
    if(!(QString(getenv("PBS_JOBID")).isEmpty()))
        return QString(getenv("PBS_JOBID")).split(".").first();

    if(!(QString(getenv("OAR_JOBID")).isEmpty()))
        return QString(getenv("OAR_JOBID"));

    return QString::number(QCoreApplication::applicationPid());
}

bool dtkDistributedSlave::isConnected(void)
{
    if (!d->socket)
        return false;
    return (d->socket->state() == QAbstractSocket::ConnectedState);
}

bool dtkDistributedSlave::isDisconnected(void)
{
    if (!d->socket)
        return false;
    return (d->socket->state() == QAbstractSocket::UnconnectedState);
}

void dtkDistributedSlave::connect(const QUrl& server)
{
    d->socket->connectToHost(server.host(), server.port());

    if(d->socket->waitForConnected()) {

        QObject::connect(d->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

        emit connected(server);

    } else {
        dtkWarn() << "Unable to connect to" << server.toString();
    }
}

void dtkDistributedSlave::disconnect(const QUrl& server)
{
    dtkDebug() << "disconnect from connect" << server.toString();
    d->socket->disconnectFromHost();

    emit disconnected(server);
}

QTcpSocket *dtkDistributedSlave::socket(void)
{
    return d->socket;
}


void dtkDistributedSlave::error(QAbstractSocket::SocketError error)
{
    switch(error) {
    case QAbstractSocket::ConnectionRefusedError:
        dtkError() <<  "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        dtkError() <<  "The remote host closed the connection. Note that the slave socket (i.e., this socket) will be closed after the remote close notification has been sent.";
        break;
    case QAbstractSocket::HostNotFoundError:
        dtkError() <<  "The host address was not found.";
        break;
    case QAbstractSocket::SocketAccessError:
        dtkError() <<  "The socket operation failed because the application lacked the required privileges.";
        break;
    case QAbstractSocket::SocketResourceError:
        dtkError() <<  "The local system ran out of resources (e.g., too many sockets).";
        break;
    case QAbstractSocket::SocketTimeoutError:
        dtkError() <<  "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        dtkError() <<  "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
        break;
    case QAbstractSocket::NetworkError:
        dtkError() <<  "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
        break;
    case QAbstractSocket::AddressInUseError:
        dtkError() <<  "The address specified to QUdpSocket::bind() is already in use and was set to be exclusive.";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        dtkError() <<  "The address specified to QUdpSocket::bind() does not belong to the host.";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        dtkError() <<  "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        dtkError() <<  "The socket is using a proxy, and the proxy requires authentication.";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        dtkError() <<  "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        dtkError() <<  "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background).";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        dtkError() <<  "Could not contact the proxy server because the connection to that server was denied";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        dtkError() <<  "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        dtkError() <<  "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase.";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        dtkError() <<  "The proxy address set with setProxy() (or the application proxy) was not found.";
        break;
    case QAbstractSocket::ProxyProtocolError:
        dtkError() <<  "The connection negotiation with the proxy server because the response from the proxy server could not be understood.";
        break;
    case QAbstractSocket::UnknownSocketError:
        dtkError() <<  "An unidentified error occurred.";
        break;
    default:
        break;
    }
}
