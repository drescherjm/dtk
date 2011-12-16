/* dtkDistributedController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. déc.  6 18:23:02 2011 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 1400
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
#include "dtkDistributedJob.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"
#include "dtkDistributedSocket.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>
#include <dtkJson/dtkJson.h>
#include <dtkJson/dtkJson.h>
#include <QtNetwork>
#include <QtXml>

class dtkDistributedControllerPrivate
{
public:
    QHash<QString, dtkDistributedSocket *> sockets;
    QHash<QString, QList<dtkDistributedNode *> > nodes;
    QHash<QString, QString > jobids;
    QHash<QString, QList<dtkDistributedJob*> > jobs;// list of all queued and running jobs on each server
    QHash<QString, QList<QProcess *> > servers;

    void read_status(QByteArray const &buffer, dtkDistributedSocket *socket);
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

        dtkDistributedSocket *socket = d->sockets.value(server.toString());

        return (socket->state() == QAbstractSocket::ConnectedState);
    }

    return false;
}

bool dtkDistributedController::isDisconnected(const QUrl& server)
{
    if(d->sockets.keys().contains(server.toString())) {

        dtkDistributedSocket *socket = d->sockets.value(server.toString());

        return (socket->state() == QAbstractSocket::UnconnectedState);
    }

    return true;
}

void dtkDistributedController::submit(const QUrl& server,  QByteArray& resources)
{
    qDebug() << "Want to submit jobs with resources:" << resources;
    dtkDistributedMessage *msg  = new dtkDistributedMessage(dtkDistributedMessage::NEWJOB,"",-2,resources.size(),"json",resources);
    d->sockets[server.toString()]->sendRequest(msg);
}

// deploy a server instance on remote host (to be executed before connect)
void dtkDistributedController::deploy(const QUrl& server)
{
    if(!d->servers.keys().contains(server.toString())) {
        QProcess *serverProc = new QProcess (this);
        QStringList args;
        args << "-t"; // that way, ssh will forward the SIGINT signal,
                      // and the server will stop when the ssh process
                      // is killed
        args << "-t"; // do it twice to force tty allocation
        args << server.host();

        serverProc->setProcessChannelMode(QProcess::MergedChannels);
        QSettings settings("inria", "dtk");
        settings.beginGroup("distributed");
        QString defaultPath;
        if (!settings.contains(server.host()+"_server_path")) {
            defaultPath =  "./dtkDistributedServer";
            dtkDebug() << "Filling in empty path in settings with default path:" << defaultPath;
        }
        QString path = settings.value(server.host()+"_server_path", defaultPath).toString();

        QString forward = server.host()+"_server_forward";
        if (settings.contains(forward) && settings.value(forward).toString() == "true") {
            dtkDebug() << "ssh port forwarding is set for server " << server.host();
            args << "-L" << QString::number(server.port())+":localhost:"+QString::number(server.port());
        }

        args << path;
        args << "-p";
        args << QString::number(server.port());
        args << "--"+settings.value(server.host()+"_server_type", "torque").toString();

        settings.endGroup();
        serverProc->start("ssh", args);
        if (!serverProc->waitForStarted(5000))
            dtkDebug() << "server not yet started  " << args;
        if (!serverProc->waitForReadyRead(3000))
            dtkDebug() << "no output from server yet" << args;

        QObject::connect(serverProc, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onProcessFinished(int,QProcess::ExitStatus)));

        QObject::connect (qApp, SIGNAL(aboutToQuit()), this, SLOT(cleanup()));

        d->servers[server.toString()] << serverProc;
    } else {
        dtkDebug() << "dtkDistributedServer already started on " << server.host();
    }
}

void dtkDistributedController::send(dtkDistributedMessage *msg)
{
    QString server = d->jobids[msg->jobid()];
    dtkDistributedSocket *socket = d->sockets[server];

    socket->sendRequest(msg);
}

void dtkDistributedController::send(dtkAbstractData *data, QString jobid, qint16 rank)
{
    QString server = d->jobids[jobid];
    dtkDistributedSocket *socket = d->sockets[server];
    QByteArray *array = data->serialize();
    if (!array) {
        dtkDebug() << "serialization failed for jobid" << jobid;
        return;
    }

    QString type = data->identifier();

    socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,jobid,rank, array->size(), type));
    socket->write(*array);

}

void dtkDistributedController::connect(const QUrl& server)
{
    if(!d->sockets.keys().contains(server.toString())) {

        dtkDistributedSocket *socket = new dtkDistributedSocket(this);

        QSettings settings("inria", "dtk");
        settings.beginGroup("distributed");
        QString forward = server.host()+"_server_forward";

        if (settings.contains(forward) && settings.value(forward).toString() == "true")
            socket->connectToHost("localhost", server.port());
        else
            socket->connectToHost(server.host(), server.port());

        settings.endGroup();


        if(socket->waitForConnected()) {

            QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
            QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

            d->sockets.insert(server.toString(), socket);

            emit connected(server);

            socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::STATUS));

        } else {

            qDebug() << "Unable to connect to" << server.toString();
        }
    }
}

void dtkDistributedController::disconnect(const QUrl& server)
{
    if(d->sockets.keys().contains(server.toString())) {

        dtkDistributedSocket *socket = d->sockets.value(server.toString());
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

void dtkDistributedControllerPrivate::read_status(QByteArray const &buffer, dtkDistributedSocket *socket)
{
    QVariantMap json = dtkJson::parse(buffer).toMap();
    // TODO: check version
    // First, read nodes status

    // store mapping between cores and jobs in this list
    QHash<QString,dtkDistributedCore *> coreref;

    foreach(QVariant qv, json["nodes"].toList()) {

        QVariantMap jnode=qv.toMap();

        QVariantList cores    = jnode["cores"].toList();
        int usedcores = jnode["cores_busy"].toInt();
        int ncpus     = jnode["cpus"].toInt();
        int ngpus     = jnode["gpus"].toInt();
        int usedgpus  = jnode["gpus_busy"].toInt();
        QVariantMap properties = jnode["properties"].toMap();
        QString state =  jnode["state"].toString();

        Q_UNUSED(usedcores);
        Q_UNUSED(usedgpus);

            qint64 ncores = cores.count();
            dtkDistributedNode *node = new dtkDistributedNode;
            node->setName( jnode["name"].toString());

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

            if (properties["myrinet"] == "10G") {
                node->setNetwork(dtkDistributedNode::Myrinet10G);
            } else if(properties["infiniband"] == "QDR") {
                node->setNetwork(dtkDistributedNode::Infiniband40G);
            } else if(properties["infiniband"] == "DDR") {
                node->setNetwork(dtkDistributedNode::Infiniband20G);
            } else if(properties["infiniband"] == "SDR") {
                node->setNetwork(dtkDistributedNode::Infiniband10G);
            } else if(properties["ethernet"] == "10G") {
                node->setNetwork(dtkDistributedNode::Ethernet10G);
            } else {
                node->setNetwork(dtkDistributedNode::Ethernet1G);
            }
            if(ngpus > 0) for(int i = 0; i < ngpus; i++) {
                    dtkDistributedGpu *gpu = new dtkDistributedGpu(node);

                    if(properties["gpu_model"] == "T10")
                        gpu->setModel(dtkDistributedGpu::T10);
                    else if(properties["gpu_model"] == "C2050")
                        gpu->setModel(dtkDistributedGpu::C2050);
                    else if(properties["gpu_model"] == "C2070")
                        gpu->setModel(dtkDistributedGpu::C2070);

                    if(properties["gpu_arch"] == "nvidia-1.0")
                        gpu->setArchitecture(dtkDistributedGpu::Nvidia_10);
                    else if(properties["gpu_arch"] == "nvidia-1.3")
                        gpu->setArchitecture(dtkDistributedGpu::Nvidia_13);
                    else if(properties["gpu_arch"] == "nvidia-2.0")
                        gpu->setArchitecture(dtkDistributedGpu::Nvidia_20);
                    else if(properties["gpu_arch"].toString().contains("amd"))
                        gpu->setArchitecture(dtkDistributedGpu::AMD);

                    *node << gpu;
                }

            for(int i = 0; i < ncpus; i++) {
                    dtkDistributedCpu *cpu = new dtkDistributedCpu(node);
                    int ppn = ncores / ncpus;
                    cpu->setCardinality(ppn);

                    if(properties["cpu_arch"] == "x86")
                        cpu->setArchitecture(dtkDistributedCpu::x86);
                    else
                        cpu->setArchitecture(dtkDistributedCpu::x86_64);

                    if(properties["cpu_model"].toString().contains("opteron")) {
                        cpu->setModel(dtkDistributedCpu::Opteron);
                    } else if(properties["cpu_model"].toString().contains("xeon")) {
                        cpu->setModel(dtkDistributedCpu::Xeon);
                    }
                    foreach (QVariant jcore, cores) {
                        QVariantMap qmap = jcore.toMap();
                        dtkDistributedCore * core = new dtkDistributedCore(cpu, qmap["id"].toInt());
                        *cpu << core;
                        if  (qmap.contains("job")) {
                            coreref[qmap["job"].toString()] = core;
                        }
                    }
                    *node << cpu;
                }

            nodes[sockets.key(socket)] << node;
            qDebug() << "Found node" << node->name() << "with" << node->cpus().count() << "cpus";
    }
    // Then, read jobs status
    dtkDistributedJob *job = new dtkDistributedJob;

    foreach(QVariant qv, json["jobs"].toList()) {
        QVariantMap jjob=qv.toMap();
        QString jobid = jjob["id"].toString();
        job->setId(jobid);
        job->setState(jjob["state"].toString());
        job->setUsername(jjob["username"].toString());
        job->setName(jjob["name"].toString());
        job->setWalltime(jjob["walltime"].toString());
        job->setQueue(jjob["queue"].toString());
        job->setQtime(jjob["qtime"].toInt());
        job->setStime(jjob["stime"].toInt());
        job->setResources(jjob["resources"].toString());
        if (coreref.contains(jobid))
            coreref[jobid]->setJob(job);
        jobs[sockets.key(socket)] << job;
        qDebug() << "Found job " << job->Id() <<"from "<< job->Username() << " in queue " << job->Queue();
    }
}

void dtkDistributedController::read(void)
{
    dtkDistributedSocket *socket = (dtkDistributedSocket *)sender();

    QString server = d->sockets.key(socket);
    dtkDistributedMessage *msg = socket->parseRequest();
    QByteArray result;

    dtkDistributedMessage::Method method = msg->method();
    switch (method) {
        case dtkDistributedMessage::OKSTATUS:
            result = msg->content();
            d->read_status(result,socket);
            emit updated();
            break;
        case dtkDistributedMessage::OKJOB:
            qDebug() << DTK_PRETTY_FUNCTION << "New job queued: " << msg->jobid();
            d->jobids[msg->jobid()] = server;
            emit updated();
            break;
        case dtkDistributedMessage::SETRANK:
            qDebug() << DTK_PRETTY_FUNCTION << "set rank received";
            if (msg->rank() == 0) {
                qDebug() << DTK_PRETTY_FUNCTION << "job started";
                emit jobStarted(msg->jobid());
                emit updated();
            }
            break;
        case dtkDistributedMessage::ENDJOB:
            qDebug() << "job finished: " << msg->jobid();
            d->jobids.remove(msg->jobid());
            emit updated();
            break;
        case dtkDistributedMessage::DATA:
            result = msg->content();
            qDebug() << "Result: " << result;
            emit dataPosted(result);
            emit updated();
            break;
        default:
            qDebug() << "unknown response from server ";
        };
    if (socket->bytesAvailable() > 0)
        this->read();
}

void dtkDistributedController::cleanup()
{
    foreach (const QString& key, d->servers.keys()) {
        foreach (QProcess* server, d->servers[key]) {
            qDebug() << "terminating servers started on" << key;
            server->terminate();
        }
    }
}

void dtkDistributedController::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus )
{
    qDebug() << DTK_PRETTY_FUNCTION << "remote server deployment failure" << exitStatus ;
}

void dtkDistributedController::error(QAbstractSocket::SocketError error)
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
