/* dtkComposerNodeControlFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed May  9 17:00:57 2012 (+0200)
 *           By: tkloczko
 *     Update #: 140
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
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractContainer.h>
#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEachPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlForEachPrivate
{
public:    
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterVariant header_rcv;

    dtkComposerTransmitterVariant block_var;

public:
    qlonglong counter;
    qlonglong end;

    dtkAbstractContainer container;
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
    d->body_block.setInputLabelHint("item", 0); 
    d->body_block.appendReceiver(&(d->block_var));

    d->counter = 0;
    d->end = -1;
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
    d->container = d->header_rcv.container();
    d->counter = 0;
    d->end = d->container.count();

    foreach(dtkComposerTransmitterVariant *v, this->inputTwins()) {
        v->setTwinned(false);
        v->setData(v->data());
        v->setTwinned(true);        
    }
}

void dtkComposerNodeControlForEach::setOutputs(void)
{
    foreach(dtkComposerTransmitterVariant *v, this->outputTwins()) {
        v->twin()->setData(v->data());
    }

    d->counter++;
}

void dtkComposerNodeControlForEach::setVariables(void)
{
    d->block_var.setData(d->container.at(d->counter));
}

int dtkComposerNodeControlForEach::selectBranch(void)
{
    return (int)(!((d->counter) < d->end));
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
