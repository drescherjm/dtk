/* dtkComposerNodeControlFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  4 14:37:08 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 226
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlForEach.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEachPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlForEachPrivate
{
public:    
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterReceiverVariant header_rcv;

    dtkComposerTransmitterProxy              block_container;
    dtkComposerTransmitterEmitter<qlonglong> block_size;
    dtkComposerTransmitterEmitter<qlonglong> block_index;
    dtkComposerTransmitterEmitterVariant     block_item;

public:
    qlonglong counter;
    qlonglong size;

    bool first_iteration;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEach implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlForEach::dtkComposerNodeControlForEach(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlForEachPrivate)
{
    d->header.removeEmitter(0);
    d->header.removeReceiver(0);
    d->header.appendReceiver(&(d->header_rcv));
    d->header.setInputLabelHint("container", 0); 
    d->header.setAsHeader(true);

    d->footer.removeReceiver(0);
    d->footer.removeEmitter(0);
    d->footer.setAsFooter(true);

    d->body_block.setTitleHint("Body");
    d->body_block.setInputLabelHint("container", 0); 
    d->body_block.appendReceiver(&(d->block_container));
    d->body_block.setInputLabelHint("size", 1); 
    d->body_block.appendReceiver(&(d->block_size));
    d->body_block.setInputLabelHint("index", 2); 
    d->body_block.appendReceiver(&(d->block_index));
    d->body_block.setInputLabelHint("item", 3); 
    d->body_block.appendReceiver(&(d->block_item));

    d->block_container.appendPrevious(&d->header_rcv);
    d->header_rcv.appendNext(&d->block_container);

    d->counter = 0;
    d->size = -1;
}

dtkComposerNodeControlForEach::~dtkComposerNodeControlForEach(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlForEach::blockCount(void)
{
    return 1;
}

dtkComposerNodeLeaf *dtkComposerNodeControlForEach::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlForEach::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlForEach::block(int id)
{
    if(id == 0)
        return &(d->body_block);

    return NULL;
}

void dtkComposerNodeControlForEach::setInputs(void)
{
    foreach(dtkComposerTransmitterProxyLoop *t, this->inputTwins()) {
	t->disableLoopMode();
    }
    d->first_iteration = true;
}

void dtkComposerNodeControlForEach::setOutputs(void)
{
    if (d->first_iteration) {
	foreach(dtkComposerTransmitterProxyLoop *t, this->outputTwins()) {
	    t->twin()->enableLoopMode();
	}
	d->first_iteration = false;
    }
}

void dtkComposerNodeControlForEach::setVariables(void)
{
    //d->block_item.setData(d->container->at(d->counter));
    d->block_index.setData((d->counter)++);
}

int dtkComposerNodeControlForEach::selectBranch(void)
{
    return static_cast<int>(!((d->counter) < d->size));
}

void dtkComposerNodeControlForEach::begin(void)
{
    if (d->header_rcv.isEmpty())
        return;

    //d->container = d->header_rcv.constContainer();
    d->counter = 0;
    //d->size = d->container->count();
    d->block_size.setData(d->size);
}

void dtkComposerNodeControlForEach::end(void)
{

}

QString dtkComposerNodeControlForEach::type(void)
{
    return "foreach";
}

QString dtkComposerNodeControlForEach::titleHint(void)
{
    return "For Each";
}
