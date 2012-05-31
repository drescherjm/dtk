/* @(#)dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 * Version: $Id$
 * Last-Updated: mer. mai 30 15:42:27 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 700
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeRemote.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>
#include <dtkDistributed/dtkDistributedSlave.h>

#include <dtkCore/dtkAbstractDataFactory.h>

#include <dtkMath/dtkMath.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemotePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeRemotePrivate
{
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
    QString last_rank;

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

void dtkComposerNodeRemote::begin(void)
{
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
        if (d->last_rank != d->jobid) {
            msg = new dtkDistributedMessage(dtkDistributedMessage::SETRANK,d->jobid,dtkDistributedMessage::CONTROLLER_RUN_RANK );
            d->server->socket()->sendRequest(msg);
            delete msg;
            d->last_rank=d->jobid;
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
        int max  = this->receivers().count();
        int size = d->communicator->size();
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->receivers().at(i));
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
