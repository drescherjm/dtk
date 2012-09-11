/* dtkComposerNodeControlWhile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 11 14:30:07 2012 (+0200)
 *           By: tkloczko
 *     Update #: 86
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerMetatype.h"
#include "dtkComposerNodeControlWhile.h"

#include "dtkComposerNodeComposite.h"
#include "dtkComposerNodeProxy.h"

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitterReceiver.h"
#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlWhilePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlWhilePrivate
{
public:
    dtkComposerNodeProxy header;
    dtkComposerNodeProxy footer;

    dtkComposerNodeComposite cond_block;
    dtkComposerNodeComposite body_block;

public:
    dtkComposerTransmitterReceiver<bool> cond;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlWhile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlWhile::dtkComposerNodeControlWhile(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlWhilePrivate)
{
    d->header.removeEmitter(0);
    d->header.removeReceiver(0);
    d->header.setAsHeader(true);

    d->footer.removeEmitter(0);
    d->footer.removeReceiver(0);
    d->footer.setAsFooter(true);

    d->cond_block.setTitleHint("Conditional");
    d->cond_block.appendEmitter(&(d->cond));
    d->cond_block.setOutputLabelHint("cond", 0);

    d->body_block.setTitleHint("Body");
}

dtkComposerNodeControlWhile::~dtkComposerNodeControlWhile(void)
{
    delete d;

    d = NULL;
}

int dtkComposerNodeControlWhile::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlWhile::header(void)
{
    return &(d->header);
}

dtkComposerNodeLeaf *dtkComposerNodeControlWhile::footer(void)
{
    return &(d->footer);
}

dtkComposerNodeComposite *dtkComposerNodeControlWhile::block(int id)
{
    if(id == 0)
        return &(d->cond_block);

    if(id == 1)
        return &(d->body_block);

    return NULL;
}

void dtkComposerNodeControlWhile::setInputs(void)
{
    foreach(dtkComposerTransmitterVariant *v, this->inputTwins()) {
        v->setTwinned(false);
        v->setDataFrom(v);
        v->setTwinned(true);
    }
}

void dtkComposerNodeControlWhile::setConditions(void)
{
}

void dtkComposerNodeControlWhile::setOutputs(void)
{
    foreach(dtkComposerTransmitterVariant *v, this->outputTwins()) {
        v->twin()->setDataFrom(v);
    }    
}

void dtkComposerNodeControlWhile::setVariables(void)
{
}

int dtkComposerNodeControlWhile::selectBranch(void)
{
    return static_cast<int>(!(*d->cond.data()));
}

void dtkComposerNodeControlWhile::begin(void)
{
}

void dtkComposerNodeControlWhile::end(void)
{
}

QString dtkComposerNodeControlWhile::type(void)
{
    return "while";
}

QString dtkComposerNodeControlWhile::titleHint(void)
{
    return "While";
}
