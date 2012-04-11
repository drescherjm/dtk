/* @(#)dtkComposerNodeRemote.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 15:19:20
 * Version: $Id$
 * Last-Updated: mer. avril 11 17:46:54 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 92
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeRemote.h"
#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedSlave.h>



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

};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeRemote implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeRemote::dtkComposerNodeRemote(void) : dtkComposerNodeComposite(), d(new dtkComposerNodeRemotePrivate)
{
    d->controller = NULL;
    d->slave = NULL;
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
    return "Remote";
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
            // todo
        }
    } else {
        // running on the slave, receive data and set transmitters
        int max  = this->receivers().count();
        for (int i = 0; i < max; i++) {
            // todo
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
