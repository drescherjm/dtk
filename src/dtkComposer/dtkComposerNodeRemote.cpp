/* @(#)dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 * Version: $Id$
 * Last-Updated: ven. avril 20 16:23:05 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 493
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeRemote.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkAbstractDataFactory.h>

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>
#include <dtkDistributed/dtkDistributedSlave.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemotePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate
{
public:
    QDomDocument composition;

public:
    dtkDistributedController *controller;

public:
    dtkDistributedCommunicator *communicator;
    dtkDistributedCommunicatorTcp *server;

public:
    dtkDistributedSlave *slave;

public:
    QString jobid;

public:
    QString title;

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRemote::dtkComposerNodeRemote(void) : dtkComposerNodeComposite(), d(new dtkComposerNodeRemotePrivate)
{
    d->controller = NULL;
    d->slave      = NULL;
    d->server     = NULL;
    d->title = "Remote";
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
    d->composition = document;
}

void dtkComposerNodeRemote::setController(dtkDistributedController *controller)
{
    if (d->jobid.isEmpty())
        dtkWarn() <<  "No job id while setting controller !";
    d->controller = controller;
    if (!d->server) {
        d->server = new dtkDistributedCommunicatorTcp;
        d->server->connectToHost(controller->socket(d->jobid)->peerAddress().toString(),controller->socket(d->jobid)->peerPort());
    }
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

void dtkComposerNodeRemote::begin(void)
{
    if (d->controller) {
        // send sub-composition to rank 0 on remote node
        QByteArray compo = d->composition.toByteArray();
        dtkDebug() << "running node remote begin statement on controller, send composition of size " << compo.size();
        d->server->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::SETRANK,d->jobid,dtkDistributedMessage::CONTROLLER_RUN_RANK ));
        d->server->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,0,compo.size(), "xml", compo ));
        dtkDebug() << "composition sent";
        // then send transmitters data
        int max  = this->receivers().count();
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->receivers().at(i));
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
            case QVariant::UserType:
            case QVariant::UserType+1: {
                // assume it's a dtkAbstractData
                dtkAbstractData *data = t->data().value<dtkAbstractData *>();
                dtkDebug() << "sending dtkAbstractData in transmitter" << i;
                d->server->socket()->send(data, d->jobid, 0);
                continue;
            }
            default:
                continue;
            }
            dtkDebug() << "sending transmitter" << i << "of size" << array.size();
            d->server->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,0, array.size(), dataType, array));
        }
    } else {
        // running on the slave, receive data and set transmitters
        int max  = this->receivers().count();
        int size = d->communicator->size();
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->receivers().at(i));
            if (d->communicator->rank() == 0) {

                if (d->slave->communicator()->socket()->bytesAvailable()) {
                    dtkDebug() << "data already available, parse" ;

                } else {
                    if (!(d->slave->communicator()->socket()->waitForData(60000))) {
                        dtkError() << "No data received from server after 1mn, abort " ;
                        return;
                    } else
                        dtkDebug() << "Ok, data received, parse" ;
                }
                dtkDistributedMessage *msg = d->slave->communicator()->socket()->parseRequest();
                if (msg->type() == "double") {
                    double *data = reinterpret_cast<double*>(msg->content().data());
                    dtkDebug() << "received double, set data in transmitter";
                    t->setData(*data);
                } else if (msg->type() == "qlonglong") {
                    qlonglong *data = reinterpret_cast<qlonglong*>(msg->content().data());
                    dtkDebug() << "received longlong, set data in transmitter";
                    t->setData(*data);
                } else if (msg->type() == "qstring") {
                    QString data = QString(msg->content());
                    dtkDebug() << "received string, set data in transmitter";
                    t->setData(data);
                } else { // assume a dtkAbstractData
                    dtkDebug() << "received dtkAbstractData, deserialize";
                    if (msg->size() > 0) {
                        QByteArray array = msg->content();
                        dtkAbstractData *data;
                        data = dtkAbstractDataFactory::instance()->create(msg->type());
                        if (!data->deserialize(array)) {
                            dtkError() << "Deserialization failed";
                        } else {
                            dtkDebug() << "set dtkAbstractData in transmitter" << msg->size();
                            t->setData(qVariantFromValue(data));
                        }
                    } else
                        dtkWarn() << "warning: no content in dtkAbstractData transmitter";
                }
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
//        d->controller->socket(d->jobid)->blockSignals(true);
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
            if (msg->type() == "double") {
                double *data = reinterpret_cast<double*>(msg->content().data());
                t->setTwinned(false);
                t->setData(*data);
                t->setTwinned(true);
            } else if (msg->type() == "qlonglong") {
                qlonglong *data = reinterpret_cast<qlonglong*>(msg->content().data());
                t->setTwinned(false);
                t->setData(*data);
                t->setTwinned(true);
            } else if (msg->type() == "qstring") {
                t->setTwinned(false);
                t->setData(QString(msg->content()));
                t->setTwinned(true);
            } else { // assume a dtkAbstractData
                dtkDebug() << "data received" << msg->type();
                if (msg->size() > 0) {
                    QByteArray array = msg->content();
                    dtkAbstractData *data;
                    data = dtkAbstractDataFactory::instance()->create(msg->type());
                    if (!data->deserialize(array)) {
                        dtkError() << "Deserialization failed";
                    } else {
                        t->setTwinned(false);
                        t->setData(qVariantFromValue(data));
                        t->setTwinned(true);
                    }
                } else
                    dtkWarn() << "warning: no content in dtkAbstractData transmitter";
            }
        }
//        d->server->socket()->blockSignals(false);
    } else {
        // running on the slave, send data and set transmitters
        dtkDebug() << "running node remote end statement on slave" << d->communicator->rank() ;
        int max  = this->emitters().count();
        int size = d->communicator->size();
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));
            // FIXME: use our own transmitter variant list (see control nodes)
            if (d->communicator->rank() ==0) {
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
                case QVariant::UserType:
                case QVariant::UserType+1: {
                    // assume it's a dtkAbstractData
                    dtkAbstractData *data = t->data().value<dtkAbstractData *>();
                    QString type = data->identifier();
                    QByteArray *array = data->serialize();
                    if (!array->isNull()) {
                        d->slave->communicator()->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid, dtkDistributedMessage::CONTROLLER_RUN_RANK, array->size(), type));
                        d->slave->communicator()->socket()->write(*array);
                    } else {
                        dtkError() << "serialization failed in transmitter";
                    }
                    continue;
                }
                default:
                    continue;
                }
                d->slave->communicator()->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,dtkDistributedMessage::CONTROLLER_RUN_RANK, array.size(), dataType, array));
            } else {
                //TODO rank >0
            }
        }
        if (d->communicator->rank() ==0)
            d->slave->communicator()->socket()->waitForBytesWritten();
    }
}
