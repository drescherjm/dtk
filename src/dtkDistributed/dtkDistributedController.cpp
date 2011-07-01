/* dtkDistributedController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 15:17:29 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 481
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedServerManager.h"
#include "dtkDistributedCore.h"
#include "dtkDistributedNode.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <QtNetwork>
#include <QtXml>

class dtkDistributedControllerPrivate
{
public:
    QHash<QString, QTcpSocket *> sockets;
    QHash<QString, QList<dtkDistributedNode *> > nodes;
};

dtkDistributedController::dtkDistributedController(void) : d(new dtkDistributedControllerPrivate)
{

}

dtkDistributedController::~dtkDistributedController(void)
{
    delete d;

    d = NULL;
}

bool dtkDistributedController::isConnected(const QUrl& server)
{
    if(d->sockets.keys().contains(server.toString())) {

        QTcpSocket *socket = d->sockets.value(server.toString());

        return (socket->state() == QAbstractSocket::ConnectedState);
    }  

    return false;
}

bool dtkDistributedController::isDisconnected(const QUrl& server)
{
    if(d->sockets.keys().contains(server.toString())) {

        QTcpSocket *socket = d->sockets.value(server.toString());

        return (socket->state() == QAbstractSocket::UnconnectedState);
    }  

    return true;
}

void dtkDistributedController::connect(const QUrl& server)
{
    if(!d->sockets.keys().contains(server.toString())) {

        QTcpSocket *socket = new QTcpSocket(this);
        socket->connectToHost(server.host(), server.port());

        if(socket->waitForConnected()) {

            QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
            QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
            
            d->sockets.insert(server.toString(), socket);
            
            emit connected(server);

            socket->write("** status **");

        } else {

            qDebug() << "Unable to connect to" << server.toString();
        }
    }
}

void dtkDistributedController::disconnect(const QUrl& server)
{
    if(d->sockets.keys().contains(server.toString())) {

        QTcpSocket *socket = d->sockets.value(server.toString());
        socket->disconnectFromHost();

        d->sockets.remove(server.toString());

        emit disconnected(server);
    }
}

QList<dtkDistributedNode *> dtkDistributedController::nodes(void)
{
    QList<dtkDistributedNode *> n;

    foreach(QList<dtkDistributedNode *> nodeset, d->nodes)
        n << nodeset;

    return n;
}

QList<dtkDistributedNode *> dtkDistributedController::nodes(const QString& cluster)
{
    return d->nodes.value(cluster);
}

void dtkDistributedController::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    static QString status_contents;

    QString buffer = socket->readAll();

    if(buffer.startsWith("!! status !!")) {

        status_contents.clear();
        status_contents += buffer.remove("!! status !!");
    }

    if(buffer.endsWith("!! endstatus !!")) {

      if(!buffer.startsWith("version="+dtkDistributedServerManager::protocol())) {
        qDebug() << "WARNING: Bad protocol version";
      }

        status_contents = buffer.remove("!! endstatus !!");
        QStringList nodes = status_contents.split("\n");
        // skip the first item (version=XXX), so start at 1 :
        for(int i = 1; i < nodes.size(); i++) {
            QStringList nodestr = nodes.at(i).split(";");

            if  (nodestr.size() < 8) {
                qDebug() << "Skipping line ";
                continue;
            }

            QString name  = nodestr.at(0);
            int ncores    = nodestr.at(1).toInt();
            int usedcores = nodestr.at(2).toInt();
            int ncpus     = nodestr.at(3).toInt();
            int ngpus     = nodestr.at(4).toInt();
            int usedgpus  = nodestr.at(5).toInt();
            QString state = nodestr.at(7);
            QStringList properties = nodestr.at(6).split(",");

            dtkDistributedNode *node = new dtkDistributedNode;
            node->setName(name);

            if(state == "free")
                node->setState(dtkDistributedNode::Free);

            if(state == "busy")
                node->setState(dtkDistributedNode::Busy);

            if(state == "down")
                node->setState(dtkDistributedNode::Down);

            if(properties.contains("dell"))
                node->setBrand(dtkDistributedNode::Dell);

            if(properties.contains("hp"))
                node->setBrand(dtkDistributedNode::Hp);

            if(properties.contains("ibm"))
                node->setBrand(dtkDistributedNode::Ibm);

            if(properties.contains("myrinet"))
                node->setNetwork(dtkDistributedNode::Myrinet10G);
            else if(properties.contains("QDR"))
                node->setNetwork(dtkDistributedNode::Infiniband40G);
            else
                node->setNetwork(dtkDistributedNode::Ethernet1G);

            if(properties.contains("gpu")) for(int i = 0; i < ngpus; i++) {

                    dtkDistributedGpu *gpu = new dtkDistributedGpu(node);

                    if(properties.contains("nvidia-T10"))
                        gpu->setModel(dtkDistributedGpu::T10);
                    else if(properties.contains("nvidia-C2050"))
                        gpu->setModel(dtkDistributedGpu::C2050);
                    else if(properties.contains("nvidia-C2070"))
                        gpu->setModel(dtkDistributedGpu::C2070);

                    if(properties.contains("nvidia"))
                        gpu->setArchitecture(dtkDistributedGpu::Nvidia);

                    if(properties.contains("amd"))
                        gpu->setArchitecture(dtkDistributedGpu::AMD);

                    *node << gpu;
                }

            for(int i = 0; i < ncpus; i++) {

                    dtkDistributedCpu *cpu = new dtkDistributedCpu(node);
                    int cores = ncores / ncpus;
                    cpu->setCardinality(cores);

                    if(properties.contains("x86"))
                        cpu->setArchitecture(dtkDistributedCpu::x86);
                    else
                        cpu->setArchitecture(dtkDistributedCpu::x86_64);

                    if(properties.contains("opteron"))
                        cpu->setModel(dtkDistributedCpu::Opteron);

                    if(properties.contains("xeon"))
                        cpu->setModel(dtkDistributedCpu::Xeon);

                    for(int j = 0; j < cores; j++)
                        *cpu << new dtkDistributedCore(cpu);

                    *node << cpu;
                }

            d->nodes[d->sockets.key(socket)] << node;

            qDebug() << "Found node" << node->name() << "with" << node->cpus().count() << "cpus";

            emit updated();
        }

        status_contents.clear();
    }
}

void dtkDistributedController::error(QAbstractSocket::SocketError error)
{
    switch(error) {
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << DTK_PRETTY_FUNCTION << "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << DTK_PRETTY_FUNCTION << "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent.";
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
