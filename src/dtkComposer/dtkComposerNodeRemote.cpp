/* dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeRemote.h"
#include "dtkComposerNodeRemote_p.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxyVariant.h"

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedSettings.h>
#include <dtkDistributed/dtkDistributedSlave.h>

#include <dtkLog/dtkLog.h>

#include <QApplication>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRemote::dtkComposerNodeRemote(void) : QObject(), dtkComposerNodeComposite(), d(new dtkComposerNodeRemotePrivate)
{
    static qlonglong count = 0;

    this->appendReceiver(&(d->jobid_receiver));
    this->appendReceiver(&(d->socket_emitter));

    this->appendEmitter(&(d->socket_emitter));

    d->communicator = NULL;
    d->socket     = NULL;
    d->controller = NULL;
    d->slave      = NULL;
    d->rank       = dtkDistributedMessage::CONTROLLER_RUN_RANK - count;
    d->title      = "Remote";
    count ++;
}

dtkComposerNodeRemote::~dtkComposerNodeRemote(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeRemote::setComposition(QDomDocument document)
{
    d->composition  = document;
    d->current_hash = QCryptographicHash::hash(d->composition.toByteArray(),QCryptographicHash::Md5);
}

void dtkComposerNodeRemote::setController(dtkDistributedController *controller)
{
    if (d->jobid.isEmpty()) {
        dtkWarn() <<  "No job id while setting controller !";
    }
    d->controller = controller;
}

void dtkComposerNodeRemote::setCommunicator(dtkDistributedCommunicator *c)
{
    d->communicator = c;
}

void dtkComposerNodeRemote::setSlave(dtkDistributedSlave *slave)
{
    d->slave = slave;
}

void dtkComposerNodeRemote::setSocket(QTcpSocket *s)
{
    d->socket = s;
}

void dtkComposerNodeRemote::setJob(QString jobid)
{
    d->jobid = jobid;
}

bool dtkComposerNodeRemote::isSlave(void)
{
    return d->slave;
}

void dtkComposerNodeRemote::onJobStarted(QString jobid)
{
    if (jobid == d->jobid) {
        QObject::disconnect( dtkDistributedController::instance(), SIGNAL(jobStarted(QString)), this, SLOT(onJobStarted(QString)));
    } else {
        dtkDebug() << "A job has started, but it's not ours, keep waiting " << d->jobid << jobid ;
    }
}

void dtkComposerNodeRemote::begin(void)
{
    QScopedPointer<dtkDistributedMessage> msg;

    if (!d->slave && !d->jobid_receiver.isEmpty()) {
        // we are running on the controller but controller and job was
        // not drag&dropped, get job from transmitter and main
        // controller instance
        d->jobid = d->jobid_receiver.data();
        d->controller = dtkDistributedController::instance();
        if (!d->controller->is_running(d->jobid)) {
            dtkDebug() << " Wait for job to start, jobid is " << d->jobid;
            QEventLoop loop;
            this->connect(d->controller, SIGNAL(jobStarted(QString)), this, SLOT(onJobStarted(QString)),Qt::DirectConnection);
            loop.connect(d->controller, SIGNAL(jobStarted(QString)), &loop, SLOT(quit()));
            loop.connect(qApp, SIGNAL(aboutToQuit()), &loop, SLOT(quit()));
            loop.exec();
            dtkTrace() << "waiting event loop ended, job has started" << d->jobid;
        } else
            dtkDebug() << " Job already running, go " << d->jobid;
    } else if (!d->slave && d->jobid.isEmpty()) { // on controller but no job !
        dtkError() << "No Job, can't run on remote node " ;
        return;
    }

    if (d->controller) {
        if (!d->socket) {
            d->socket = new QTcpSocket;
            d->socket_emitter.setData(d->socket);
            d->socket->connectToHost(d->controller->socket(d->jobid)->peerAddress().toString(),d->controller->socket(d->jobid)->peerPort());
            if (d->socket->waitForConnected()) {
                dtkDebug() << "Connected to server";
            } else {
                dtkError() << "Can't connect to server";
                return;
            }
        }

        if (d->last_jobid != d->jobid) {
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::SETRANK,d->jobid, d->rank));
            msg->send(d->socket);
            d->last_jobid=d->jobid;
            // the job has changed, so we must send the composition even if it has not changed
            d->last_sent_hash.clear();
        }
        if (d->current_hash != d->last_sent_hash){
            // send sub-composition to rank 0 on remote node
            QByteArray compo = d->composition.toByteArray();
            dtkDebug() << "running node remote begin statement on controller, send composition of size " << compo.size();
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,dtkDistributedMessage::SLAVE_RANK,compo.size(), "xml", compo ));
            d->last_sent_hash=d->current_hash;
        } else {
            dtkDebug() << "composition hash hasn't changed, send 'not-modified' to slave";
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,dtkDistributedMessage::SLAVE_RANK,d->current_hash.size(), "not-modified", d->current_hash ));
        }
        msg->send(d->socket);
        dtkDebug() << "composition sent";
        // then send transmitters data
        QList<dtkComposerTransmitter*> receivers = this->dtkComposerNodeComposite::receivers();
        int max  = receivers.count();

        dtkComposerTransmitterProxyVariant *t = NULL;
        for (int i = 2; i < max; ++i) {
            t = reinterpret_cast<dtkComposerTransmitterProxyVariant*>(receivers.at(i));
            dtkDebug() << "sending transmitter" << i;
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::DATA, d->jobid, 0,  t->variant()));
            // FIXME: is it the good socket ?
            msg->send(d->socket);
        }
        d->socket->waitForBytesWritten();
    } else if (d->communicator ){
        // running on the slave, receive data and set transmitters
        QList<dtkComposerTransmitter*> receivers = this->dtkComposerNodeComposite::receivers();
        int max  = receivers.count();
        int size = d->communicator->size();
        dtkComposerTransmitterProxyVariant *t = NULL;
        for (int i = 2; i < max; ++i) {
            t = reinterpret_cast<dtkComposerTransmitterProxyVariant*>(receivers.at(i));
            if (d->communicator->rank() == 0) {

                d->socket_emitter.setData(d->slave->socket());

                if (d->slave->socket()->bytesAvailable()) {
                    dtkDebug() << "data already available, parse" ;

                } else {
                    if (!(d->slave->socket()->waitForReadyRead(60000))) {
                        dtkError() << "No data received from server after 1mn, abort " ;
                        return;
                    } else
                        dtkDebug() << "BEGIN: Ok, data received, parse" ;
                }
                msg.reset(new dtkDistributedMessage);
                msg->parse(d->slave->socket());
                t->clearData();
                t->enableEmitter();
                t->setVariant(msg->variant());

                d->communicator->broadcast(msg->variant(), 0);

            } else {
                QVariant variant;
                dtkDebug() << "receive data from rank 0";
                d->communicator->broadcast(variant, 0);
                dtkDebug() << "data received, set";
                t->clearData();
                t->enableEmitter();
                t->setVariant(variant);
            }
        }
    } else {
        dtkError() << "No communicator and no controller on remote node: can't run begin node";
    }
}

void dtkComposerNodeRemote::end(void)
{
    QScopedPointer<dtkDistributedMessage> msg(new dtkDistributedMessage);

    if (!d->slave && d->jobid.isEmpty()) { // on controller but no job !
        dtkError() << "No Job, skip end remote node " ;
        return;
    }

    if (d->controller) {
        dtkDebug() << "running node remote end statement on controller";
        QList<dtkComposerTransmitter*> emitters = this->dtkComposerNodeComposite::emitters();
        int max  = this->emitters().count();
        dtkComposerTransmitterProxyVariant *t = NULL;
        for (int i = 1; i < max; ++i) {
            t = reinterpret_cast<dtkComposerTransmitterProxyVariant*>(emitters.at(i));

            if (d->socket->bytesAvailable()) {
                dtkDebug() << "data already available, parse" ;
            } else {
                if (!(d->socket->waitForReadyRead(60000))) {
                    dtkError() << "No data received from slave after 1mn, abort " ;
                    return;
                } else
                    dtkDebug() << "Ok, data received for transmitter, parse" ;
            }
            msg->parse(d->socket);
            t->clearData();
            t->enableEmitter();
            t->setVariant(msg->variant());
        }
    } else if (d->communicator) {
        // running on the slave, send data and set transmitters
        dtkDebug() << "running node remote end statement on slave" << d->communicator->rank() ;
        QList<dtkComposerTransmitter*> emitters = this->dtkComposerNodeComposite::emitters();
        int max  = this->emitters().count();
        int size = d->communicator->size();
        Q_UNUSED(size);
        dtkComposerTransmitterProxyVariant *t = NULL;
        for (int i = 1; i < max; ++i) {
            t = reinterpret_cast<dtkComposerTransmitterProxyVariant*>(emitters.at(i));
            // FIXME: use our own transmitter variant list (see control nodes)
            if (d->communicator->rank() == 0) {
                dtkDebug() << "end, send transmitter data (we are rank 0)";
                QVariant v = t->variant();
                if (!v.isNull()) {
                    dtkDistributedMessage *req;
                    req = new dtkDistributedMessage(dtkDistributedMessage::DATA, d->jobid, dtkDistributedMessage::CONTROLLER_RUN_RANK, v);
                    req->send(d->slave->socket());
                    delete req;
                } else {
                    dtkError() << "serialization failed in transmitter";
                }

            } else {
                //TODO rank >0
            }
        }
        if (d->communicator->rank() == 0) {
            d->slave->socket()->waitForBytesWritten();
        }
    } else {
        dtkError() << "No communicator and no controller on remote node: can't run end node";
    }

}


// /////////////////////////////////////////////////////////////////
// Submit
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemoteSubmitPrivate
{
public:
    dtkComposerTransmitterEmitter<QString> id;

    dtkComposerTransmitterReceiver<QString> cluster;
    dtkComposerTransmitterReceiver<qlonglong> nodes;
    dtkComposerTransmitterReceiver<qlonglong> cores;
    dtkComposerTransmitterReceiver<QString> walltime;
    dtkComposerTransmitterReceiver<QString> queuename;
    dtkComposerTransmitterReceiver<QString> application;
    dtkComposerTransmitterReceiver<QString> options;
    dtkComposerTransmitterReceiver<QString> policy;

public:
    QString slaveName;
};

dtkComposerNodeRemoteSubmit::dtkComposerNodeRemoteSubmit(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRemoteSubmitPrivate)
{
    this->appendReceiver(&(d->cluster));
    this->appendReceiver(&(d->nodes));
    this->appendReceiver(&(d->cores));
    this->appendReceiver(&(d->walltime));
    this->appendReceiver(&(d->queuename));
    this->appendReceiver(&(d->options));
    this->appendReceiver(&(d->policy));

    d->slaveName = "dtkComposerEvaluator --slave";
    this->appendEmitter(&(d->id));

}

dtkComposerNodeRemoteSubmit::~dtkComposerNodeRemoteSubmit(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeRemoteSubmit::setSlaveName(QString name)
{
    d->slaveName = name;
}

void dtkComposerNodeRemoteSubmit::run(void)
{
    QVariantMap resources;

    if (d->cluster.isEmpty()) {
        dtkError() << "Empty server in remote submit, can't submit job";
        return;
    }

    QVariantMap job;

    QUrl cluster = QUrl(d->cluster.data());

    if (cluster.port() < 0) {
        dtkDebug() << "setting port" ;
        cluster.setPort(dtkDistributedController::defaultPort());
        dtkDebug() << "new cluster url" << cluster.toString() ;
    }

    qlonglong nodes = d->nodes.data();
    qlonglong cores = d->cores.data();

    QString slaveOptions = " --server "+cluster.toString();

    if (d->cores.isEmpty())
        resources.insert("cores", 1);
    else
        resources.insert("cores", cores);

    if (d->nodes.isEmpty())
        resources.insert("nodes", 1);
    else
        resources.insert("nodes", nodes);

    if (nodes * cores > 1){
        slaveOptions += " -np " + QString::number(nodes * cores);
    }

    if (!d->policy.isEmpty()) {
        slaveOptions += " --policy " + d->policy.data();
    }

    job.insert("resources", resources);

    if (d->walltime.isEmpty())
        job.insert("walltime", "00:15:00");
    else
        job.insert("walltime", d->walltime.data());

    if (!d->queuename.isEmpty())
        job.insert("queue", d->queuename.data());

    job.insert("application", d->slaveName+" --logfile console --loglevel trace " + slaveOptions);

    QByteArray job_data = QJsonDocument(QJsonObject::fromVariantMap(job)).toJson();
    dtkTrace() << " submit job with parameters: "<< job_data;


    dtkDistributedController *controller = dtkDistributedController::instance();
    if (!controller->isConnected(cluster)) {
        dtkInfo() <<  "Not yet connected to " << cluster << ",try to connect";
        dtkDistributedSettings settings;
        bool use_tunnel = settings.use_ssh_tunnel(cluster);
        bool register_rank = true;
        controller->deploy(cluster, settings.server_type(cluster), use_tunnel , settings.path(cluster) );
        controller->connect(cluster, use_tunnel, register_rank);
    } else {
        dtkInfo() <<  "Controller is already connection to server " << cluster;
    }

    if (controller->submit(cluster, job_data)) {
        QEventLoop loop;
        this->connect(controller, SIGNAL(jobQueued(QString)), this, SLOT(onJobQueued(QString)),Qt::DirectConnection);
        loop.connect(controller, SIGNAL(jobQueued(QString)), &loop, SLOT(quit()));
        loop.connect(qApp, SIGNAL(aboutToQuit()), &loop, SLOT(quit()));

        loop.exec();
        dtkTrace() <<  "event loop ended, job is queued";

    } else
        dtkWarn() <<  "failed to submit ";
}

void dtkComposerNodeRemoteSubmit::onJobQueued(const QString& job_id)
{
    d->id.setData(job_id);
    QObject::disconnect( dtkDistributedController::instance(), SIGNAL(jobQueued(QString)), this, SLOT(onJobQueued(QString)));
}
