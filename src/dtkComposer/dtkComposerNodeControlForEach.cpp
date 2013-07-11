/* dtkComposerNodeControlFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. juil. 11 12:18:14 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 197
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
#include "dtkComposerTransmitterProxy.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkContainer/dtkAbstractContainerWrapper.h>

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
    dtkComposerTransmitterVariant header_rcv;

    dtkComposerTransmitterProxy              block_container;
    dtkComposerTransmitterEmitter<qlonglong> block_size;
    dtkComposerTransmitterEmitter<qlonglong> block_index;
    dtkComposerTransmitterVariant            block_item;

public:
    qlonglong counter;
    qlonglong size;

    const dtkAbstractContainerWrapper *container;
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
    d->block_index.setData(&d->counter);

    d->size = -1;
    d->block_size.setData(&d->size);

    d->container = NULL;
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
    if (d->header_rcv.isEmpty())
        return;

    d->container = d->header_rcv.constContainer();

    if (!d->container)
        return;

    d->counter = 0;
    d->size = d->container->count();

    foreach(dtkComposerTransmitterVariant *v, this->inputTwins()) {
        v->setTwinned(false);
        v->setDataFrom(v);
        v->setTwinned(true);
    }
}

void dtkComposerNodeControlForEach::setOutputs(void)
{
    foreach(dtkComposerTransmitterVariant *v, this->outputTwins()) {
        v->twin()->setDataFrom(v);
    }

    ++(d->counter);
}

void dtkComposerNodeControlForEach::setVariables(void)
{
    d->block_item.setData(d->container->at(d->counter));
}

int dtkComposerNodeControlForEach::selectBranch(void)
{
    return static_cast<int>(!((d->counter) < d->size));
}

void dtkComposerNodeControlForEach::begin(void)
{

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
