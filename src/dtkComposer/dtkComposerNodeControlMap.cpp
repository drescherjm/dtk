/* dtkComposerNodeControlMap.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: lun. juin 18 16:08:06 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 11 14:44:53 2012 (+0200)
 *           By: tkloczko
 *     Update #: 96
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerMetatype.h"
#include "dtkComposerNodeControlMap.h"
#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>

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
    dtkComposerTransmitterVariant header_rcv;
    dtkComposerTransmitterVariant footer_emit;

    dtkComposerTransmitterProxy                 block_container;
    dtkComposerTransmitterEmitter<qlonglong> block_size;
    dtkComposerTransmitterEmitter<qlonglong> block_index;
    dtkComposerTransmitterVariant               block_item;
    dtkComposerTransmitterVariant               block_newitem;

public:
    qlonglong counter;
    qlonglong size;

    dtkAbstractContainerWrapper *container;
    dtkAbstractContainerWrapper *out_container;
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
    d->block_index.setData(&d->counter);

    d->size = -1;
    d->block_size.setData(&d->size);

    d->container = NULL;
    d->out_container = NULL;
}

dtkComposerNodeControlMap::~dtkComposerNodeControlMap(void)
{
    if (d->out_container)
        delete d->out_container;

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
    d->container = d->header_rcv.container();

    if (d->out_container)
        delete d->out_container;
    d->out_container = d->container->voidClone();    
    d->footer_emit.setData(d->out_container);

    d->counter = 0;
    d->size = d->container->count();

    foreach(dtkComposerTransmitterVariant *v, this->inputTwins()) {
        v->setTwinned(false);
        v->setDataFrom(v);
        v->setTwinned(true);
    }
}


void dtkComposerNodeControlMap::setOutputs(void)
{
    foreach(dtkComposerTransmitterVariant *v, this->outputTwins()) {
        v->twin()->setDataFrom(v);
    }

    d->out_container->append(d->block_newitem.variant());

    ++(d->counter);
}

void dtkComposerNodeControlMap::setVariables(void)
{
    d->block_item.setData(d->container->at(d->counter));
}

int dtkComposerNodeControlMap::selectBranch(void)
{
    return static_cast<int>(!((d->counter) < d->size));
}

void dtkComposerNodeControlMap::begin(void)
{

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
