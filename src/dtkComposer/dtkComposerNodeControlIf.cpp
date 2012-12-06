/* dtkComposerNodeControlIf.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: 2012 Thu Nov 15 15:03:35 (+0100)
 *           By: Thibaud Kloczko, Inria.
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlIf.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIfPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlIfPrivate
{
public:    
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite then_block;
    dtkComposerNodeComposite else_block;

public:
    dtkComposerTransmitterVariant cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIf implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlIf::dtkComposerNodeControlIf(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlIfPrivate)
{
    QList<int> variants;
    variants << QMetaType::Bool;
    d->cond.setDataTypes(variants);

    d->header.removeEmitter(0);
    d->header.setInputLabelHint("cond", 0); 
    d->header.setAsHeader(true);

    d->cond.appendPrevious(d->header.receivers().first());
    d->header.receivers().first()->appendNext(&(d->cond));

    d->footer.removeReceiver(0);
    d->footer.setOutputLabelHint("cond", 0);
    d->footer.setAsFooter(true);

    d->cond.appendNext(d->footer.emitters().first());
    d->footer.emitters().first()->appendPrevious(&(d->cond));

    d->then_block.setTitleHint("Then");

    d->else_block.setTitleHint("Else");
}

dtkComposerNodeControlIf::~dtkComposerNodeControlIf(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlIf::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlIf::block(int id)
{
    if(id == 0)
        return &(d->then_block);

    if(id == 1)
        return &(d->else_block);

    return NULL;
}

void dtkComposerNodeControlIf::setInputs(void)
{

}

void dtkComposerNodeControlIf::setConditions(void)
{
    
}

void dtkComposerNodeControlIf::setOutputs(void)
{

}

void dtkComposerNodeControlIf::setVariables(void)
{
    
}

int dtkComposerNodeControlIf::selectBranch(void)
{
    if (d->cond.isEmpty())
        return static_cast<int>(false);

    bool value = *d->cond.data<bool>();
    
    foreach(dtkComposerTransmitter *t, d->then_block.emitters())
        t->setActive(value);

    foreach(dtkComposerTransmitter *t, d->else_block.emitters())
        t->setActive(!value);
        
    return (!value);
}

void dtkComposerNodeControlIf::begin(void)
{
    
}

void dtkComposerNodeControlIf::end(void)
{
    
}

QString dtkComposerNodeControlIf::type(void)
{
    return "if";
}

QString dtkComposerNodeControlIf::titleHint(void)
{
    return "If";
}
