/* dtkDistributedController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:15:13 2011 (+0200)
 * Version: $Id$
 * Last-Updated: ven. avril 13 13:48:01 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 1535
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

#include <dtkJson/dtkJson.h>
#include <dtkJson/dtkJson.h>

#include <dtkLog/dtkLog.h>

#include <QtNetwork>
#include <QtXml>

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerPrivate
{
public:
    void clear();

public:
    void read_status(QByteArray const &buffer, dtkDistributedSocket *socket);

public:
    QHash<QString, dtkDistributedSocket *> sockets;

    QHash<QString, QList<dtkDistributedNode *> > nodes;
    QHash<QString, QList<dtkDistributedJob *> > jobs;

    QHash<QString, QString > jobids;

    QHash<QString, QList<QProcess *> > servers;

public:
    bool refreshing;
};

void dtkDistributedControllerPrivate::clear(void)
{
    foreach(QList<dtkDistributedNode *> n, this->nodes.values())
        qDeleteAll(n);

    foreach(QList<dtkDistributedJob *> j, this->jobs.values())
        qDeleteAll(j);

    this->nodes.clear();
    this->jobs.clear();
}

void dtkDistributedControllerPrivate::read_status(QByteArray const &buffer, dtkDistributedSocket *socket)
{
    if (this->refreshing) {
        this->clear();
        this->refreshing = false;
    }

    QVariantMap json = dtkJson::parse(buffer).toMap();
    // TODO: check version
    // First, read nodes status

    // store mapping between cores and jobs in this list
    QHash<QString, QList<dtkDistributedCore *> > coreref;

    foreach(QVariant qv, json["nodes"].toList()) {

        QVariantMap jnode = qv.toMap();

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
        
        for(int i = 0; i < ngpus; i++) {
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

        // feed cpus

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

            for(int j = i*ppn; j < (i+1)*ppn; j++) {

                QVariantMap qmap = cores.at(j).toMap();

                dtkDistributedCore *core = new dtkDistributedCore(cpu, qmap["id"].toInt());
                *cpu << core;

                if (qmap.contains("job"))
                    coreref[qmap["job"].toString()] << core;
            }

            *node << cpu;
        }

        nodes[sockets.key(socket)] << node;
        dtkDebug() << "Found node" << node->name() << "with" << node->cpus().count() << "cpus";
    }

    foreach(QVariant qv, json["jobs"].toList()) {

        dtkDistributedJob *job = new dtkDistributedJob;

        QVariantMap jjob=qv.toMap();
        QString jobid = jjob["id"].toString();
        job->setId(jobid);
        job->setState(jjob["state"].toString());
        job->setUsername(jjob["username"].toString());
        job->setName(jjob["name"].toString());
        job->setWalltime(jjob["walltime"].toString());
        job->setQueue(jjob["queue"].toString());
        job->setQtime(jjob["queue_time"].toLongLong()*1000);
        job->setStime(jjob["start_time"].toLongLong()*1000);
        job->setResources(jjob["resources"].toString());
        if (coreref.contains(jobid))
            foreach(dtkDistributedCore *job_core,  coreref[jobid])
                job_core->setJob(job);
        jobs[sockets.key(socket)] << job;
        dtkDebug() << "Found job " << job->Id() <<"from "<< job->Username() << " in queue " << job->Queue();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedController implementation
// /////////////////////////////////////////////////////////////////

dtkDistributedController::dtkDistributedController(void) : d(new dtkDistributedControllerPrivate)
{
    d->refreshing = false;
}

dtkDistributedController::~dtkDistributedController(void)
{
    d->clear();

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
    dtkDebug() << "Want to submit jobs with resources:" << resources;
    dtkDistributedMessage *msg  = new dtkDistributedMessage(dtkDistributedMessage::NEWJOB,"",-2,resources.size(),"json",resources);
    d->sockets[server.toString()]->sendRequest(msg);
}

void dtkDistributedController::killjob(const QUrl& server, QString jobid)
{
    dtkDebug() << "Want to kill job" << jobid;
    dtkDistributedMessage *msg  = new dtkDistributedMessage(dtkDistributedMessage::DELJOB,jobid,-2);
    d->sockets[server.toString()]->sendRequest(msg);
}

void dtkDistributedController::refresh(const QUrl& server)
{
    dtkDebug() << DTK_PRETTY_FUNCTION << server;

    if(!d->sockets.keys().contains(server.toString()))
        return;
    
    d->refreshing = true;

    dtkDistributedSocket *socket = d->sockets.value(server.toString());
    socket->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::STATUS));

    emit updated(server);
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

        QString key;
#if defined(Q_WS_MAC)
        key = server.host().replace(".", "_");
#else
        key = server.host();
#endif

        if (!settings.contains(key+"_server_path")) {
            defaultPath =  "./dtkDistributedServer";
            dtkDebug() << "Filling in empty path in settings with default path:" << defaultPath;
        }
        QString path = settings.value(key+"_server_path", defaultPath).toString();

        QString forward = key+"_server_forward";
        if (settings.contains(forward) && settings.value(forward).toString() == "true") {
            dtkTrace() << "ssh port forwarding is set for server " << server.host();
            args << "-L" << QString::number(server.port())+":localhost:"+QString::number(server.port());
        }

        args << path;
        args << "-p";
        args << QString::number(server.port());
        args << "--"+settings.value(key+"_server_type", "torque").toString();

        settings.endGroup();
        serverProc->start("ssh", args);


        // need to wait a bit when ssh port forwarding is used
        if (settings.contains(forward) && settings.value(forward).toString() == "true")
            sleep(1);

        dtkDebug() << DTK_PRETTY_FUNCTION << "ssh" << args;

        if (!serverProc->waitForStarted(5000))
            dtkDebug() << "server not yet started  " << args;
        if (!serverProc->waitForReadyRead(5000))
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
        dtkFatal() << "serialization failed for jobid" << jobid;
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

        QString key;
#if defined(Q_WS_MAC)
        key = server.host().replace(".", "_");
#else
        key = server.host();
#endif

        QSettings settings("inria", "dtk");
        settings.beginGroup("distributed");
        QString forward = key+"_server_forward";

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

            dtkError() << "Unable to connect to" << server.toString();
        }
    }
}

void dtkDistributedController::disconnect(const QUrl& server)
{
    if(!d->sockets.keys().contains(server.toString()))
        return;
    
    dtkDistributedSocket *socket = d->sockets.value(server.toString());
    socket->disconnectFromHost();
    
    d->sockets.remove(server.toString());
    
    emit disconnected(server);
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

QList<dtkDistributedJob *> dtkDistributedController::jobs(void)
{
    QList<dtkDistributedJob *> j;

    foreach(QList<dtkDistributedJob *> jobset, d->jobs)
        j << jobset;

    return j;
}

QList<dtkDistributedJob *> dtkDistributedController::jobs(const QString& cluster)
{
    return d->jobs.value(cluster);
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
        emit status(QUrl(server));
        emit updated();
        break;
    case dtkDistributedMessage::OKJOB:
        dtkDebug() << DTK_PRETTY_FUNCTION << "New job queued: " << msg->jobid();
        d->jobids[msg->jobid()] = server;
        emit updated();
        break;
    case dtkDistributedMessage::SETRANK:
        dtkDebug() << DTK_PRETTY_FUNCTION << "set rank received";
        if (msg->rank() == 0) {
            qDebug() << DTK_PRETTY_FUNCTION << "job started";
            emit jobStarted(msg->jobid());
            emit updated();
        }
        break;
    case dtkDistributedMessage::ENDJOB:
        dtkDebug() << "job finished: " << msg->jobid();
        d->jobids.remove(msg->jobid());
        emit updated();
        break;
    case dtkDistributedMessage::DATA:
        result = msg->content();
        dtkDebug() << "Result: " << result;
        emit dataPosted(result);
        emit updated();
        break;
    default:
        dtkDebug() << "unknown response from server ";
    };
    if (socket->bytesAvailable() > 0)
        this->read();
}

void dtkDistributedController::cleanup()
{
    foreach (const QString& key, d->servers.keys()) {
        foreach (QProcess* server, d->servers[key]) {
            dtkDebug() << "terminating servers started on" << key;
            server->terminate();
        }
    }
}

void dtkDistributedController::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus )
{
    DTK_UNUSED(exitCode);
    qDebug() << DTK_PRETTY_FUNCTION << "remote server deployment failure" << exitStatus ;
}

void dtkDistributedController::error(QAbstractSocket::SocketError error)
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
