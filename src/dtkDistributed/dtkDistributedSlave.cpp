/* dtkDistributedSlave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: lun. déc.  9 18:09:51 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 249
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedMessage.h"
#include "dtkDistributedSlave.h"
#include "dtkDistributedSocket.h"
#include "dtkDistributedCommunicatorTcp.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkLog/dtkLog.h>

#include <QtNetwork>
#include <iostream>

class dtkDistributedSlavePrivate
{
public:
    dtkDistributedCommunicatorTcp *communicator;
};

dtkDistributedSlave::dtkDistributedSlave(void) : d(new dtkDistributedSlavePrivate)
{
    d->communicator = new dtkDistributedCommunicatorTcp();
}

dtkDistributedSlave::dtkDistributedSlave(dtkDistributedCommunicatorTcp *communicator) : d(new dtkDistributedSlavePrivate)
{
    d->communicator = communicator;
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
    if (!d->communicator->socket())
        return false;
    return (d->communicator->socket()->state() == QAbstractSocket::ConnectedState);
}

bool dtkDistributedSlave::isDisconnected(void)
{
    if (!d->communicator->socket())
        return false;
    return (d->communicator->socket()->state() == QAbstractSocket::UnconnectedState);
}


void dtkDistributedSlave::read(void)
{
    dtkDistributedSocket *socket = d->communicator->socket();
    dtkDistributedMessage *request = socket->parseRequest();

    if( request->method() == dtkDistributedMessage::DATA) {
        dtkInfo() << DTK_PRETTY_FUNCTION << "DATA received in slave, unimplemented";
    } else {
        dtkWarn() << DTK_PRETTY_FUNCTION << "WARNING: Unknown data";
    }
    if (socket->bytesAvailable() > 0)
        this->read();
}


void dtkDistributedSlave::connect(const QUrl& server)
{
    d->communicator->connectToHost(server.host(), server.port());

    if(d->communicator->socket()->waitForConnected()) {

//        QObject::connect(d->communicator->socket(), SIGNAL(readyRead()), this , SLOT(read()));
        QObject::connect(d->communicator->socket(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

        emit connected(server);

    } else {
        dtkWarn() << "Unable to connect to" << server.toString();
    }
}

void dtkDistributedSlave::disconnect(const QUrl& server)
{
    dtkDebug() << "disconnect from connect" << server.toString();
    d->communicator->disconnectFromHost();

    emit disconnected(server);
}

void dtkDistributedSlave::onStarted(void)
{
    QString jobid = "unknown"; //FIXME
    d->communicator->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::STARTJOB,jobid));
}

void dtkDistributedSlave::onEnded(void)
{
    QString jobid = "unknown"; //FIXME
    d->communicator->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::ENDJOB,jobid));
}

dtkDistributedCommunicatorTcp *dtkDistributedSlave::communicator(void)
{
    return d->communicator;
}


void dtkDistributedSlave::error(QAbstractSocket::SocketError error)
{
    switch(error) {
    case QAbstractSocket::ConnectionRefusedError:
        dtkError() << DTK_PRETTY_FUNCTION << "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        dtkError() << DTK_PRETTY_FUNCTION << "The remote host closed the connection. Note that the slave socket (i.e., this socket) will be closed after the remote close notification has been sent.";
        break;
    case QAbstractSocket::HostNotFoundError:
        dtkError() << DTK_PRETTY_FUNCTION << "The host address was not found.";
        break;
    case QAbstractSocket::SocketAccessError:
        dtkError() << DTK_PRETTY_FUNCTION << "The socket operation failed because the application lacked the required privileges.";
        break;
    case QAbstractSocket::SocketResourceError:
        dtkError() << DTK_PRETTY_FUNCTION << "The local system ran out of resources (e.g., too many sockets).";
        break;
    case QAbstractSocket::SocketTimeoutError:
        dtkError() << DTK_PRETTY_FUNCTION << "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        dtkError() << DTK_PRETTY_FUNCTION << "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes).";
        break;
    case QAbstractSocket::NetworkError:
        dtkError() << DTK_PRETTY_FUNCTION << "An error occurred with the network (e.g., the network cable was accidentally plugged out).";
        break;
    case QAbstractSocket::AddressInUseError:
        dtkError() << DTK_PRETTY_FUNCTION << "The address specified to QUdpSocket::bind() is already in use and was set to be exclusive.";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        dtkError() << DTK_PRETTY_FUNCTION << "The address specified to QUdpSocket::bind() does not belong to the host.";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        dtkError() << DTK_PRETTY_FUNCTION << "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support).";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        dtkError() << DTK_PRETTY_FUNCTION << "The socket is using a proxy, and the proxy requires authentication.";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        dtkError() << DTK_PRETTY_FUNCTION << "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        dtkError() << DTK_PRETTY_FUNCTION << "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background).";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        dtkError() << DTK_PRETTY_FUNCTION << "Could not contact the proxy server because the connection to that server was denied";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        dtkError() << DTK_PRETTY_FUNCTION << "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        dtkError() << DTK_PRETTY_FUNCTION << "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase.";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        dtkError() << DTK_PRETTY_FUNCTION << "The proxy address set with setProxy() (or the application proxy) was not found.";
        break;
    case QAbstractSocket::ProxyProtocolError:
        dtkError() << DTK_PRETTY_FUNCTION << "The connection negotiation with the proxy server because the response from the proxy server could not be understood.";
        break;
    case QAbstractSocket::UnknownSocketError:
        dtkError() << DTK_PRETTY_FUNCTION << "An unidentified error occurred.";
        break;
    default:
        break;
    }
}
