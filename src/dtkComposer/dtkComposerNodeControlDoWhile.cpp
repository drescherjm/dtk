/* dtkComposerNodeControlDoWhile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  4 14:53:22 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 72
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxyLoop.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhilePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlDoWhilePrivate
{
public:
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite cond_block;
    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterReceiver<bool> cond;

public:
    bool first_iteration;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlDoWhile::dtkComposerNodeControlDoWhile(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlDoWhilePrivate)
{
    d->header.removeReceiver(0);
    d->header.removeEmitter(0);
    d->header.setAsHeader(true);

    d->footer.removeReceiver(0);
    d->footer.removeEmitter(0);
    d->footer.setAsFooter(true);

    d->cond_block.setTitleHint("Conditional");
    d->cond_block.appendEmitter(&(d->cond));
    d->cond_block.setOutputLabelHint("cond", 0);

    d->body_block.setTitleHint("Body");
}

dtkComposerNodeControlDoWhile::~dtkComposerNodeControlDoWhile(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlDoWhile::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlDoWhile::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlDoWhile::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlDoWhile::block(int id)
{
    if(id == 0)
        return &(d->body_block);

    if(id == 1)
        return &(d->cond_block);

    return NULL;
}

void dtkComposerNodeControlDoWhile::setInputs(void)
{
    foreach(dtkComposerTransmitterProxyLoop *t, this->inputTwins()) {
        t->disableLoopMode();
    }
    d->first_iteration = true;
}

void dtkComposerNodeControlDoWhile::setOutputs(void)
{
    if (d->first_iteration) {
	foreach(dtkComposerTransmitterProxyLoop *t, this->outputTwins()) {
	    t->twin()->enableLoopMode();
	}
	d->first_iteration = false;
    }
}

void dtkComposerNodeControlDoWhile::setVariables(void)
{

}

int dtkComposerNodeControlDoWhile::selectBranch(void)
{
    if (!d->cond.isEmpty())
	return static_cast<int>(!(d->cond.data()));
        
    return static_cast<int>(true);
}

void dtkComposerNodeControlDoWhile::begin(void)
{

}

void dtkComposerNodeControlDoWhile::end(void)
{

}

QString dtkComposerNodeControlDoWhile::type(void)
{
    return "do while";
}

QString dtkComposerNodeControlDoWhile::titleHint(void)
{
    return "Do While";
}
