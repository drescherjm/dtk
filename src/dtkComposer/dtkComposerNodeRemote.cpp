/* @(#)dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 * Version: $Id$
 * Last-Updated: lun. juin 18 14:55:41 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 940
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeRemote.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>
#include <dtkDistributed/dtkDistributedSlave.h>

#include <dtkCore/dtkAbstractDataFactory.h>

#include <dtkJson>

#include <dtkMath/dtkMath.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemotePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate
{

public:
    dtkComposerTransmitterReceiver<QString> jobid_receiver;

public:
    QDomDocument composition;
    QByteArray current_hash;
    QByteArray last_sent_hash;

public:
    dtkDistributedController *controller;

public:
    dtkDistributedCommunicator *communicator;
    dtkDistributedCommunicatorTcp *server;

public:
    dtkDistributedSlave *slave;

public:
    QString jobid;
    QString last_jobid;

public:
    QString title;

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRemote::dtkComposerNodeRemote(void) : dtkComposerNodeComposite(), d(new dtkComposerNodeRemotePrivate)
{

    this->appendReceiver(&(d->jobid_receiver));
    this->setInputLabelHint("jobid", 0);

    d->controller = NULL;
    d->slave      = NULL;
    d->server     = NULL;
    d->title      = "Remote";
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
    if (d->jobid.isEmpty())
        dtkWarn() <<  "No job id while setting controller !";
    d->controller = controller;
}

void dtkComposerNodeRemote::setSlave(dtkDistributedSlave *slave)
{
    d->slave = slave;
}

void dtkComposerNodeRemote::setCommunicator(dtkDistributedCommunicator *c)
{
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
            loop.exec();
            dtkTrace() << "waiting event loop ended, job has started" << d->jobid;
        } else
            dtkDebug() << " Job already running, go " << d->jobid;
    }

    if (d->controller) {
        if (!d->server) {
            d->server = new dtkDistributedCommunicatorTcp;
            d->server->connectToHost(d->controller->socket(d->jobid)->peerAddress().toString(),d->controller->socket(d->jobid)->peerPort());
            if (d->server->socket()->waitForConnected()) {
                dtkDebug() << "Connected to server";
            } else {
                dtkError() << "Can't connect to server";
                return;
            }
        }
        dtkDistributedMessage *msg;
        if (d->last_jobid != d->jobid) {
            msg = new dtkDistributedMessage(dtkDistributedMessage::SETRANK,d->jobid,dtkDistributedMessage::CONTROLLER_RUN_RANK );
            d->server->socket()->sendRequest(msg);
            delete msg;
            d->last_jobid=d->jobid;
            // the job has changed, so we must send the composition even if it has not changed
            d->last_sent_hash.clear();
        }
        if (d->current_hash != d->last_sent_hash){
            // send sub-composition to rank 0 on remote node
            QByteArray compo = d->composition.toByteArray();
            dtkDebug() << "running node remote begin statement on controller, send composition of size " << compo.size();
            msg = new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,0,compo.size(), "xml", compo );
            d->last_sent_hash=d->current_hash;
        } else {
            dtkDebug() << "composition hash hasn't changed, send 'not-modified' to slave";
            msg = new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,0,d->current_hash.size(), "not-modified", d->current_hash );
        }
        d->server->socket()->sendRequest(msg);
        delete msg;
        dtkDebug() << "composition sent";
        // then send transmitters data
        int max  = dtkComposerNodeComposite::receivers().count();
        for (int i = 1; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(dtkComposerNodeComposite::receivers().at(i));
            // FIXME: use our own transmitter variant list (see control nodes)
            QByteArray array;
            QString  dataType;
            switch (t->type()) {
            case QVariant::Double: {
                double data = t->data().toDouble();
                dataType = "double";
                array = QByteArray(reinterpret_cast<const char*>(&data), sizeof(data));
                break;
            }
            case QVariant::LongLong: {
                qlonglong data = t->data().toLongLong();
                dataType = "qlonglong";
                array = QByteArray(reinterpret_cast<const char*>(&data), sizeof(data));
                break;
            }
            case QVariant::String: {
                dataType = "qstring";
                array = t->data().toByteArray();
                break;
            }
            case QVariant::UserType: {

                if(QString(t->data().typeName()) == "dtkAbstractData*") {

                    dtkAbstractData *data = t->data().value<dtkAbstractData *>();
                    dtkDebug() << "sending dtkAbstractData in transmitter" << i;
                    d->server->socket()->send(data, d->jobid, 0);

                } else {

                    dtkDebug() << QString("sending QVariant (%1) in transmitter").arg(t->data().typeName()) << i;
                    d->server->socket()->send(t->data(), d->jobid, 0);
                }

                continue;
            }
            default:
                continue;
            }
            dtkDebug() << "sending transmitter" << i << "of size" << array.size();
            msg = new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,0,array.size(), dataType, array );
            d->server->socket()->sendRequest(msg);
            delete msg;
        }
        d->server->socket()->waitForBytesWritten();
    } else {
        // running on the slave, receive data and set transmitters
        int max  = dtkComposerNodeComposite::receivers().count();
        int size = d->communicator->size();
        for (int i = 1; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(dtkComposerNodeComposite::receivers().at(i));
            if (d->communicator->rank() == 0) {

                if (d->slave->communicator()->socket()->bytesAvailable()) {
                    dtkDebug() << "data already available, parse" ;

                } else {
                    if (!(d->slave->communicator()->socket()->waitForReadyRead(60000))) {
                        dtkError() << "No data received from server after 1mn, abort " ;
                        return;
                    } else
                        dtkDebug() << "Ok, data received, parse" ;
                }
                dtkDistributedMessage *msg = d->slave->communicator()->socket()->parseRequest();

                t->setDataFromMsg(msg);

                dtkDebug() << "send data to slaves";
                for (int j=1; j< size; j++)
                    d->communicator->send(t->data(),j,0);

            } else {
                QVariant data;
                dtkDebug() << "receive data from rank 0";
                d->communicator->receive(data,0,0);
                dtkDebug() << "data received, set";
                t->setData(data);
            }
        }
    }
}

void dtkComposerNodeRemote::end(void)
{
    if (d->controller) {
        dtkDebug() << "running node remote end statement on controller";
        int max  = this->emitters().count();
        for (int i = 0; i < max; i++) {
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
            dtkDistributedMessage *msg = d->server->socket()->parseRequest();
            t->setDataFromMsg(msg);

        }
    } else {
        // running on the slave, send data and set transmitters
        dtkDebug() << "running node remote end statement on slave" << d->communicator->rank() ;
        int max  = this->emitters().count();
        int size = d->communicator->size();
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));
            // FIXME: use our own transmitter variant list (see control nodes)
            if (d->communicator->rank() == 0) {
                dtkDebug() << "end, send transmitter data (we are rank 0)";
                QByteArray array;
                QString  dataType;
                switch (t->type()) {
                case QVariant::Double: {
                    double data = t->data().toDouble();
                    dataType = "double";
                    array = QByteArray(reinterpret_cast<const char*>(&data), sizeof(data));
                    break;
                }
                case QVariant::LongLong: {
                    qlonglong data = t->data().toLongLong();
                    dataType = "qlonglong";
                    array = QByteArray(reinterpret_cast<const char*>(&data), sizeof(data));
                    break;
                }
                case QVariant::String: {
                    dataType = "qstring";
                    array = t->data().toByteArray();
                    break;
                }
                case QVariant::UserType: {

                    if(QString(t->data().typeName()) == "dtkAbstractData*") {

                        dtkAbstractData *data = t->data().value<dtkAbstractData *>();
                        QString type = data->identifier();
                        QByteArray *array = data->serialize();
                        if (!array->isNull()) {
                            dtkDistributedMessage *req = new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid, dtkDistributedMessage::CONTROLLER_RUN_RANK, array->size(), type);
                            d->slave->communicator()->socket()->sendRequest(req);
                            d->slave->communicator()->socket()->write(*array);
                            delete req;
                        } else {
                            dtkError() << "serialization failed in transmitter";
                        }

                    } else {

                        dtkDebug() << QString("sending QVariant (%1) in transmitter").arg(t->data().typeName()) << i;
                        d->slave->communicator()->socket()->send(t->data(), d->jobid, dtkDistributedMessage::CONTROLLER_RUN_RANK);
                    }

                    continue;
                }
                default:
                    continue;
                }
                dtkDistributedMessage *req = new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,dtkDistributedMessage::CONTROLLER_RUN_RANK, array.size(), dataType, array);
                d->slave->communicator()->socket()->sendRequest(req);
                delete req;
            } else {
                //TODO rank >0
            }
        }
        if (d->communicator->rank() == 0)
            d->slave->communicator()->socket()->waitForBytesWritten();
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
    dtkComposerTransmitterReceiver<QString> application;

    QMutex mutex;
};

dtkComposerNodeRemoteSubmit::dtkComposerNodeRemoteSubmit(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeRemoteSubmitPrivate)
{
    this->appendReceiver(&(d->cluster));
    this->appendReceiver(&(d->nodes));
    this->appendReceiver(&(d->cores));
    this->appendReceiver(&(d->walltime));

    this->appendEmitter(&(d->id));

    d->mutex.lock();
}

dtkComposerNodeRemoteSubmit::~dtkComposerNodeRemoteSubmit(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeRemoteSubmit::run(void)
{
    QVariantMap resources;

    if (d->cluster.isEmpty()) {
        dtkError() << "Empty server in remote submit, can't submit job";
        return;
    }

    QVariantMap job;

    if (d->cores.isEmpty())
        resources.insert("cores", 1);
    else
        resources.insert("cores", d->cores.data());

    if (d->nodes.isEmpty())
        resources.insert("nodes", 1);
    else
        resources.insert("nodes", d->nodes.data());

    job.insert("resources", resources);

    if (d->walltime.isEmpty())
        job.insert("walltime", "00:15:00");
    else
        job.insert("walltime", d->walltime.data());

    job.insert("properties", QVariantMap());
    job.insert("application", "dtkComposerEvaluatorSlave "+d->cluster.data());

   QByteArray job_data = dtkJson::serialize(job);

    dtkTrace() << " submit job with parameters: "<< job_data;

    dtkDistributedController *controller = dtkDistributedController::instance();
    if (controller->submit(QUrl(d->cluster.data()), job_data)) {
        QEventLoop loop;
        this->connect(controller, SIGNAL(jobQueued(QString)), this, SLOT(onJobQueued(QString)),Qt::DirectConnection);
        loop.connect(controller, SIGNAL(jobQueued(QString)), &loop, SLOT(quit()));
        loop.exec();
        dtkTrace() <<  "event loop ended, job is queued";

    } else
        dtkWarn() <<  "failed to submit ";
}

void dtkComposerNodeRemoteSubmit::onJobQueued(QString jobid)
{
    d->id.setData(jobid);
    QObject::disconnect( dtkDistributedController::instance(), SIGNAL(jobQueued(QString)), this, SLOT(onJobQueued(QString)));
}
