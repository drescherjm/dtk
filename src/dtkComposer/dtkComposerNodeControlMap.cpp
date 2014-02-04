/* dtkComposerNodeControlMap.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: lun. juin 18 16:08:06 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  5 08:50:24 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 127
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeControlMap.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterProxyLoop.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlMapPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlMapPrivate
{
public:
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterReceiverVariant header_rcv;
    dtkComposerTransmitterEmitterVariant footer_emit;

    dtkComposerTransmitterProxy              block_container;
    dtkComposerTransmitterEmitter<qlonglong> block_size;
    dtkComposerTransmitterEmitter<qlonglong> block_index;
    dtkComposerTransmitterEmitterVariant     block_item;
    dtkComposerTransmitterEmitterVariant     block_newitem;

public:
    qlonglong counter;
    qlonglong size;

    // dtkAbstractContainerWrapper *container;
    // dtkAbstractContainerWrapper *out_container;

public:
    bool first_iteration;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlMap implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlMap::dtkComposerNodeControlMap(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlMapPrivate)
{
    d->header.removeEmitter(0);
    d->header.removeReceiver(0);
    d->header.appendReceiver(&(d->header_rcv));
    d->header.setInputLabelHint("container", 0);
    d->header.setAsHeader(true);

    d->footer.removeReceiver(0);
    d->footer.removeEmitter(0);
    d->footer.appendEmitter(&(d->footer_emit));
    d->footer.setOutputLabelHint("container", 0);
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

    d->body_block.setOutputLabelHint("newitem", 0);
    d->body_block.appendEmitter(&(d->block_newitem));

    d->block_container.appendPrevious(&d->header_rcv);
    d->header_rcv.appendNext(&d->block_container);

    d->footer.emitters().first()->appendNext(&(d->footer_emit));

    d->counter = 0;
    d->size = -1;
}

dtkComposerNodeControlMap::~dtkComposerNodeControlMap(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlMap::blockCount(void)
{
    return 1;
}

dtkComposerNodeLeaf *dtkComposerNodeControlMap::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlMap::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlMap::block(int id)
{
    if(id == 0)
        return &(d->body_block);

    return NULL;
}

void dtkComposerNodeControlMap::setInputs(void)
{
    foreach(dtkComposerTransmitterProxyLoop *t, this->inputTwins()) {
        t->disableLoopMode();
    }
    d->first_iteration = true;
}


void dtkComposerNodeControlMap::setOutputs(void)
{
    if (d->first_iteration) {
	foreach(dtkComposerTransmitterProxyLoop *t, this->outputTwins()) {
	    t->twin()->enableLoopMode();
	}
	d->first_iteration = false;
    }
}

void dtkComposerNodeControlMap::setVariables(void)
{

    //d->out_container->append(d->block_newitem.variant());

    d->block_index.setData((d->counter)++);
    //d->block_item.setData(d->container->at(d->counter));
}

int dtkComposerNodeControlMap::selectBranch(void)
{
    return static_cast<int>(!((d->counter) < d->size));
}

void dtkComposerNodeControlMap::begin(void)
{
    if (d->header_rcv.isEmpty())
        return;

    // d->container = d->header_rcv.container();

    // if (d->out_container)
    //     delete d->out_container;
    // d->out_container = d->container->voidClone();    
    // d->footer_emit.setData(d->out_container);

    d->counter = 0;
    // d->size = d->container->count();
    d->block_size.setData(d->size);
}

void dtkComposerNodeControlMap::end(void)
{

}

QString dtkComposerNodeControlMap::type(void)
{
    return "map";
}

QString dtkComposerNodeControlMap::titleHint(void)
{
    return "Map";
}
