/* @(#)dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 * Version: $Id$
 * Last-Updated: ven. avril 13 16:11:01 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 208
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
//            dtkComposerTransmitter *t = this->receivers().at(i);
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
            case QVariant::Invalid: { // assume it's a dtkAbstractData
                dtkAbstractData * data;
                // TODO: get the data from t->data() as a dtkAbstractData
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
            }
        }

    }
}

void dtkComposerNodeRemote::end(void)
{
    if (d->controller) {
        int max  = this->emitters().count();
        for (int i = 0; i < max; i++) {
            // todo
        }
    } else {
        // running on the slave, send data and set transmitters
        int max  = this->emitters().count();
        for (int i = 0; i < max; i++) {
            // todo
        }

    }

}
