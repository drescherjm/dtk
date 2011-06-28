/* dtkDistributedController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 28 15:26:18 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 238
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
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

public:
    QProcess *ssh;
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

void dtkDistributedController::read(void)
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    QString response = socket->readAll();

    if(response == "!! status !!") {

        QString contents;

        QString p = socket->readAll();

        while(p != "!! endstatus !!") {
            contents += p;
            p = socket->readAll();
        }

        QDomDocument document; QString error;
        
        if(!document.setContent(contents, false, &error))
            dtkDebug() << "Error retrieving xml output out of socket" << error;
        
        QDomNodeList nodes = document.elementsByTagName("Node");
        
        for(int i = 0; i < nodes.count(); i++) {
            
            int np = nodes.item(i).firstChildElement("np").text().simplified().toInt();
            QString name  = nodes.item(i).firstChildElement("name").text().simplified();
            QString state = nodes.item(i).firstChildElement("state").text().simplified();
            QString status = nodes.item(i).firstChildElement("status").text().simplified();
            QStringList properties = nodes.item(i).firstChildElement("properties").text().simplified().split(",");
            
            dtkDistributedNode *node = new dtkDistributedNode;
            node->setName(name);
            
            if(state == "free")
                node->setState(dtkDistributedNode::Free);
            
            if(state == "job-exclusive")
                node->setState(dtkDistributedNode::JobExclusive);
            
            if(state == "down")
                node->setState(dtkDistributedNode::Down);
            
            if(state == "offline")
                node->setState(dtkDistributedNode::Offline);
            
            if(properties.contains("dell"))
                node->setBrand(dtkDistributedNode::Dell);
            
            if(properties.contains("hp"))
                node->setBrand(dtkDistributedNode::Hp);
            
            if(properties.contains("ibm"))
                node->setBrand(dtkDistributedNode::Ibm);
            
            if(properties.contains("myrinet"))
                node->setNetwork(dtkDistributedNode::Myrinet10G);
            else
                node->setNetwork(dtkDistributedNode::Ethernet1G);
            
            if(properties.contains("gpu")) for(int i = 0; i < np; i++) {
                    
                    dtkDistributedGpu *gpu = new dtkDistributedGpu(node);
                    
                    if(status.contains("x86_64"))
                        gpu->setArchitecture(dtkDistributedGpu::x86_64);
                    else
                        gpu->setArchitecture(dtkDistributedGpu::x86);
                    
                    if(properties.contains("opteron"))
                        gpu->setModel(dtkDistributedGpu::Opteron);
                    
                    if(properties.contains("xeon"))
                        gpu->setModel(dtkDistributedGpu::Xeon);
                    
                    int nc = 0;
                    
                    if(properties.contains("singlecore")) {
                        nc = 1; gpu->setCardinality(dtkDistributedGpu::Single);
                    } else if(properties.contains("dualcore")) {
                        nc = 2; gpu->setCardinality(dtkDistributedGpu::Dual);
                    } else if(properties.contains("quadcore")) {
                        nc = 4; gpu->setCardinality(dtkDistributedGpu::Quad);
                    } else if(properties.contains("octocore")) {
                        nc = 8; gpu->setCardinality(dtkDistributedGpu::Octo);
                    }
                    
                    for(int i = 0; i < nc; i++)
                        *gpu << new dtkDistributedCore(gpu);

                    *node << gpu;
                }
            
            else for(int i = 0; i < np; i++) {
                    
                    dtkDistributedCpu *cpu = new dtkDistributedCpu(node);

                    if(status.contains("x86_64"))
                        cpu->setArchitecture(dtkDistributedCpu::x86_64);
                    else
                        cpu->setArchitecture(dtkDistributedCpu::x86);
                    
                    if(properties.contains("opteron"))
                        cpu->setModel(dtkDistributedCpu::Opteron);
                    
                    if(properties.contains("xeon"))
                        cpu->setModel(dtkDistributedCpu::Xeon);
                    
                    int nc = 0;
                    
                    if(properties.contains("singlecore")) {
                        nc = 1; cpu->setCardinality(dtkDistributedCpu::Single);
                    } else if(properties.contains("dualcore")) {
                        nc = 2; cpu->setCardinality(dtkDistributedCpu::Dual);
                    } else if(properties.contains("quadcore")) {
                        nc = 4; cpu->setCardinality(dtkDistributedCpu::Quad);
                    } else if(properties.contains("octocore")) {
                        nc = 8; cpu->setCardinality(dtkDistributedCpu::Octo);
                    }
                    
                    for(int i = 0; i < nc; i++)
                        *cpu << new dtkDistributedCore(cpu);
                    
            *node << cpu;
                }
            
            // d->nodes.prepend(node);
            
            qDebug() << DTK_PRETTY_FUNCTION << "Adding a node";
        }
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
