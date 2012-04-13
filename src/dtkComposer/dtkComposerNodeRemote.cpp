/* @(#)dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 * Version: $Id$
 * Last-Updated: ven. avril 13 19:00:16 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 311
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
    d->slave = NULL;
    d->title = "Remote";
}

dtkComposerNodeRemote::~dtkComposerNodeRemote(void)
{
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
    d->controller = controller;
}

void dtkComposerNodeRemote::setSlave(dtkDistributedSlave *slave)
{
    d->slave = slave;
}

void dtkComposerNodeRemote::setJob(QString jobid)
{
    d->jobid = jobid;
    d->title = d->title + "(" + jobid + ")";
    dtkDebug() << "our job is now " << jobid;

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
        d->controller->send(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,0,compo.size(), "xml", compo ));
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
                d->controller->send(data, d->jobid, 0);
                continue;
            }
            default:
                continue;
            }
            d->controller->send(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,0, array.size(), dataType, array));
        }
    } else {
        // running on the slave, receive data and set transmitters
        int max  = this->receivers().count();
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->receivers().at(i));
            if (!(d->slave->communicator()->socket()->waitForData(60000))) {
                dtkError() << "No data received from server after 1mn, abort " ;
                return;
            } else
                dtkDebug() << "Ok, data received, parse" ;

            dtkDistributedMessage *msg = d->slave->communicator()->socket()->parseRequest();
            if (msg->type() == "double") {
                double *data = reinterpret_cast<double*>(msg->content().data());
                t->setData(*data);
            } else if (msg->type() == "qlonglong") {
                qlonglong *data = reinterpret_cast<qlonglong*>(msg->content().data());
                t->setData(*data);
            } else if (msg->type() == "qstring") {
                t->setData(QString(msg->content()));
            } else { // assume a dtkAbstractData
                //TODO
            }
        }
    }
}

void dtkComposerNodeRemote::end(void)
{
    if (d->controller) {
        int max  = this->emitters().count();
        d->controller->socket(d->jobid)->blockSignals(true);
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));

            if (!(d->controller->socket(d->jobid)->waitForReadyRead(60000))) {
                dtkError() << "No data received from slave after 1mn, abort " ;
                return;
            } else
                dtkDebug() << "Ok, data received, parse" ;

            dtkDistributedMessage *msg = d->controller->socket(d->jobid)->parseRequest();
            if (msg->type() == "double") {
                double *data = reinterpret_cast<double*>(msg->content().data());
                dtkDebug() << "double received" << *data ;
                t->setData(*data);
            } else if (msg->type() == "qlonglong") {
                qlonglong *data = reinterpret_cast<qlonglong*>(msg->content().data());
                dtkDebug() << "longlong received" << *data ;
                t->setData(*data);
            } else if (msg->type() == "qstring") {
                t->setData(QString(msg->content()));
                dtkDebug() << "string" << QString(msg->content()) ;
            } else { // assume a dtkAbstractData
                //TODO
            }
            d->controller->socket(d->jobid)->blockSignals(false);
        }
    } else {
        // running on the slave, send data and set transmitters
        int max  = this->emitters().count();
        for (int i = 0; i < max; i++) {
            dtkComposerTransmitterVariant *t = dynamic_cast<dtkComposerTransmitterVariant *>(this->emitters().at(i));
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
//                d->slave->communicator()->socket()->send(data, d->jobid, 0); FIXME
                continue;
            }
            default:
                continue;
            }
            d->slave->communicator()->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA,d->jobid,-1, array.size(), dataType, array));

        }

    }

}
