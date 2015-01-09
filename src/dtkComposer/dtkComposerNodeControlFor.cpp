/* dtkComposerNodeControlFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. nov. 13 10:22:47 2014 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 270
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlFor.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlForPrivate
{
public:    
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite cond_block;
    dtkComposerNodeComposite body_block;
    dtkComposerNodeComposite incr_block;

public:
    dtkComposerTransmitterReceiver<bool> cond;
    dtkComposerTransmitterProxy          cond_prx;

    dtkComposerTransmitterProxyLoop block_rcv;

    dtkComposerTransmitterProxy   incr_rcv;
    dtkComposerTransmitterProxyLoop incr_emt;

public:
    bool first_iteration;
    bool var_first_it;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlFor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlFor::dtkComposerNodeControlFor(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlForPrivate)
{
    d->header.removeEmitter(0);
    d->header.setInputLabelHint("i_begin", 0); 
    d->header.setAsHeader(true);

    d->footer.removeReceiver(0);
    d->footer.setOutputLabelHint("i_end", 0);
    d->footer.setAsFooter(true);

    d->cond_block.setTitleHint("Conditional");
    d->cond_block.appendEmitter(&(d->cond));
    d->cond_block.setOutputLabelHint("cond", 0);

    d->body_block.setTitleHint("Body");

    d->incr_block.setTitleHint("Increment");

    d->cond_block.appendReceiver(&(d->cond_prx));
    d->cond_block.setInputLabelHint("i", 0);
    
    d->body_block.appendReceiver(&(d->block_rcv));
    d->body_block.setInputLabelHint("i", 0);

    d->incr_block.appendReceiver(&(d->incr_rcv));
    d->incr_block.setInputLabelHint("i", 0);

    d->incr_block.appendEmitter(&(d->incr_emt));
    d->incr_block.setOutputLabelHint("i_next", 0);

    d->body_block.receivers().first()->appendPrevious(d->header.receivers().first());
    d->header.receivers().first()->appendNext(d->body_block.receivers().first());

    d->cond_block.receivers().first()->appendPrevious(d->body_block.receivers().first());
    d->body_block.receivers().first()->appendNext(d->cond_block.receivers().first());

    d->incr_block.receivers().first()->appendPrevious(d->body_block.receivers().first());
    d->body_block.receivers().first()->appendNext(d->incr_block.receivers().first());

    d->incr_block.emitters().first()->appendNext(d->footer.emitters().first());
    d->footer.emitters().first()->appendPrevious(d->incr_block.emitters().first());

    d->incr_emt.setTwin(&(d->block_rcv));
    d->block_rcv.setTwin(&(d->incr_emt));
}

dtkComposerNodeControlFor::~dtkComposerNodeControlFor(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlFor::blockCount(void)
{
    return 3;
}

dtkComposerNodeLeaf *dtkComposerNodeControlFor::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlFor::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlFor::block(int id)
{
    if(id == 0)
        return &(d->cond_block);

    if(id == 1)
        return &(d->body_block);

    if(id == 2)
        return &(d->incr_block);

    return NULL;
}

void dtkComposerNodeControlFor::setInputs(void)
{
    for(dtkComposerTransmitterProxyLoop *t : this->inputTwins()) {
	t->disableLoopMode();
    }
    d->first_iteration = true;
}

void dtkComposerNodeControlFor::setOutputs(void)
{
    if (d->first_iteration) {
	for(dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
	    t->twin()->enableLoopMode();
	}
	d->first_iteration = false;
    }
    for(dtkComposerTransmitterProxyLoop *t : this->outputTwins()) {
        t->twin()->setVariant(t->variant());
    }
}

void dtkComposerNodeControlFor::setVariables(void)
{
    if (d->var_first_it) {
	d->incr_emt.twin()->enableLoopMode();
	d->var_first_it = false;
    }
    d->incr_emt.twin()->setVariant(d->incr_emt.variant());
}

int dtkComposerNodeControlFor::selectBranch(void)
{
    if (!d->cond.isEmpty())
	return static_cast<int>(!(d->cond.data()));

    return static_cast<int>(true);
}

void dtkComposerNodeControlFor::begin(void)
{
    d->var_first_it = true;
    d->block_rcv.disableLoopMode();
}

void dtkComposerNodeControlFor::end(void)
{
}
