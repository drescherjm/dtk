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

#include "dtkComposerMetatype.h"

#include "dtkComposerNodeRemote.h"
#include "dtkComposerNodeRemote_p.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>
#include <dtkDistributed/dtkDistributedSlave.h>

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkJson>

#include <dtkMath/dtkMath.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRemote::dtkComposerNodeRemote(void) : QObject(), dtkComposerNodeComposite(), d(new dtkComposerNodeRemotePrivate)
{

    this->appendReceiver(&(d->jobid_receiver));
    this->setInputLabelHint("jobid", 0);

    this->appendReceiver(&(d->communicator_emitter));
    this->setInputLabelHint("communicator", 1);

    this->appendEmitter(&(d->communicator_emitter));
    this->setOutputLabelHint("communicator", 0);

    dtkInfo() << "constructor remode, set communicator to null" ;

    d->communicator = NULL;
    d->controller   = NULL;
    d->slave        = NULL;
    d->server       = NULL;
    d->title        = "Remote";
}

dtkComposerNodeRemote::~dtkComposerNodeRemote(void)
{
    delete d->server;
    delete d;

    d = NULL;
}

QString dtkComposerNodeRemote::type(void)
{
    return "remote";
}

QString dtkComposerNodeRemote::titleHint(void)
{
    return d->title;
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

void dtkComposerNodeRemote::setSlave(dtkDistributedSlave *slave)
{
    d->slave = slave;
}

void dtkComposerNodeRemote::setCommunicator(dtkDistributedCommunicator *c)
{
    dtkTrace() <<  "set communicator";
    d->communicator = c;
}

void dtkComposerNodeRemote::setJob(QString jobid)
{
    d->jobid = jobid;
}

bool dtkComposerNodeRemote::isSlave(void)
{
    if (d->slave)
        return true;
    return false;
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
        d->jobid = *d->jobid_receiver.data();
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
        if (!d->server) {
            d->server = new dtkDistributedCommunicatorTcp;
            d->communicator_emitter.setData(d->server);
            d->server->connectToHost(d->controller->socket(d->jobid)->peerAddress().toString(),d->controller->socket(d->jobid)->peerPort());
            if (d->server->socket()->waitForConnected()) {
                dtkDebug() << "Connected to server";
            } else {
                dtkError() << "Can't connect to server";
                return;
            }
        }

        if (d->last_jobid != d->jobid) {
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::SETRANK,d->jobid,dtkDistributedMessage::CONTROLLER_RUN_RANK ));
            d->server->socket()->sendRequest(msg.data());
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
        d->server->socket()->sendRequest(msg.data());
        dtkDebug() << "composition sent";
        // then send transmitters data
        int max  = dtkComposerNodeComposite::receivers().count();
        for (int i = 2; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(dtkComposerNodeComposite::receivers().at(i));
            // FIXME: use our own transmitter variant list (see control nodes)
            QByteArray array = t->dataToByteArray();
            dtkDebug() << "sending transmitter" << i << "of size" << array.size();
            msg.reset(new dtkDistributedMessage(dtkDistributedMessage::DATA, d->jobid, 0, array.size(), "qvariant", array));
            d->server->socket()->sendRequest(msg.data());
        }
        d->server->socket()->fflush();
    } else if (d->communicator) {
        // running on the slave, receive data and set transmitters
        int max  = dtkComposerNodeComposite::receivers().count();
        int size = d->communicator->size();
        for (int i = 2; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(dtkComposerNodeComposite::receivers().at(i));
            if (d->communicator->rank() == 0) {

                d->communicator_emitter.setData(d->slave->communicator());

                if (d->slave->communicator()->socket()->bytesAvailable()) {
                    dtkDebug() << "data already available, parse" ;

                } else {
                    if (!(d->slave->communicator()->socket()->waitForReadyRead(60000))) {
                        dtkError() << "No data received from server after 1mn, abort " ;
                        return;
                    } else
                        dtkDebug() << "Ok, data received, parse" ;
                }
                msg.reset( d->slave->communicator()->socket()->parseRequest());
                t->setTwinned(false);
                t->setDataFrom(msg->content());
                t->setTwinned(true);

                dtkDebug() << "send data to slaves";
                for (int j=1; j< size; j++)
                    d->communicator->send(msg->content(),j,0);

            } else {
                QByteArray array;
                dtkDebug() << "receive data from rank 0";
                d->communicator->receive(array, 0, 0);
                dtkDebug() << "data received, set";
                t->setTwinned(false);
                t->setDataFrom(array);
                t->setTwinned(true);
            }
        }
    } else {
        dtkError() << "No communicator and no controller on remote node: can't run begin node";
    }
}

void dtkComposerNodeRemote::end(void)
{
    QScopedPointer<dtkDistributedMessage> msg;

    if (!d->slave && d->jobid.isEmpty()) { // on controller but no job !
        dtkError() << "No Job, skip end remote node " ;
        return;
    }

    if (d->controller) {
        dtkDebug() << "running node remote end statement on controller";
        int max  = this->emitters().count();
        for (int i = 1; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));

            if (d->server->socket()->bytesAvailable()) {
                dtkDebug() << "data already available, parse" ;
            } else {
                if (!(d->server->socket()->waitForReadyRead(60000))) {
                    dtkError() << "No data received from slave after 1mn, abort " ;
                    return;
                } else
                    dtkDebug() << "Ok, data received, parse" ;
            }
            msg.reset(d->server->socket()->parseRequest());
            t->setTwinned(false);
            t->setDataFrom(msg->content());
            t->setTwinned(true);
        }
    } else if (d->communicator) {
        // running on the slave, send data and set transmitters
        dtkDebug() << "running node remote end statement on slave" << d->communicator->rank() ;

        int max  = this->emitters().count();
        int size = d->communicator->size();
        Q_UNUSED(size);

        for (int i = 1; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));
            // FIXME: use our own transmitter variant list (see control nodes)
            if (d->communicator->rank() == 0) {
                dtkDebug() << "end, send transmitter data (we are rank 0)";
                QByteArray array = t->dataToByteArray();
                if (!array.isEmpty()) {
                    msg.reset(new dtkDistributedMessage(dtkDistributedMessage::DATA, d->jobid, dtkDistributedMessage::CONTROLLER_RUN_RANK, array.size(), "qvariant", array));
                    d->slave->communicator()->socket()->sendRequest(msg.data());
                } else {
                    dtkError() << "serialization failed in transmitter";
                }

            } else {
                //TODO rank >0
            }
        }
        if (d->communicator->rank() == 0) {
            d->slave->communicator()->socket()->fflush();
            d->slave->communicator()->socket()->moveToThread(QApplication::instance()->thread());
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

public:
    QString slaveName;

public:
    QString job_id;
};

dtkComposerNodeRemoteSubmit::dtkComposerNodeRemoteSubmit(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRemoteSubmitPrivate)
{
    this->appendReceiver(&(d->cluster));
    this->appendReceiver(&(d->nodes));
    this->appendReceiver(&(d->cores));
    this->appendReceiver(&(d->walltime));
    this->appendReceiver(&(d->queuename));

    d->slaveName = "dtkComposerEvaluatorSlave";
    d->job_id = QString();
    d->id.setData(&d->job_id);
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

    QUrl cluster = QUrl(*(d->cluster.data()));

    if (cluster.port() < 0) {
        dtkDebug() << "setting port" ;
        cluster.setPort(dtkDistributedController::defaultPort());
        dtkDebug() << "new cluster url" << cluster.toString() ;
    }


    if (d->cores.isEmpty())
        resources.insert("cores", 1);
    else
        resources.insert("cores", *d->cores.data());

    if (d->nodes.isEmpty())
        resources.insert("nodes", 1);
    else
        resources.insert("nodes", *d->nodes.data());

    job.insert("resources", resources);

    if (d->walltime.isEmpty())
        job.insert("walltime", "00:15:00");
    else
        job.insert("walltime", *d->walltime.data());

    if (!d->queuename.isEmpty())
        job.insert("queue", *d->queuename.data());

    job.insert("properties", QVariantMap());
    job.insert("application", d->slaveName+" "+cluster.toString());

    QByteArray job_data = dtkJson::serialize(job);

    dtkTrace() << " submit job with parameters: "<< job_data;


    dtkDistributedController *controller = dtkDistributedController::instance();
    if (!controller->isConnected(cluster)) {
        dtkInfo() <<  "Not yet connected to " << cluster << ",try to connect";
        controller->deploy(cluster);
        controller->connect(cluster);
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
    d->job_id = job_id;
    QObject::disconnect( dtkDistributedController::instance(), SIGNAL(jobQueued(QString)), this, SLOT(onJobQueued(QString)));
}
