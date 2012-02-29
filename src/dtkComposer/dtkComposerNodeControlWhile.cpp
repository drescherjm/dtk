/* dtkComposerNodeControlWhile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 10:13:08 2012 (+0100)
 *           By: tkloczko
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlWhile.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeComposite.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlWhilePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlWhilePrivate
{
public:
    dtkComposerNodeBoolean *header;
    dtkComposerNodeBoolean *footer;

    dtkComposerNodeComposite *cond_block;
    dtkComposerNodeComposite *body_block;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlWhile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlWhile::dtkComposerNodeControlWhile(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlWhilePrivate)
{
    d->header = new dtkComposerNodeBoolean;
    delete d->header->removeEmitter(0);

    d->footer = new dtkComposerNodeBoolean;
    delete d->footer->removeReceiver(0);

    d->cond_block = new dtkComposerNodeComposite;
    d->cond_block->setTitleHint("Conditional");

    d->body_block = new dtkComposerNodeComposite;
    d->body_block->setTitleHint("Body");
}

dtkComposerNodeControlWhile::~dtkComposerNodeControlWhile(void)
{
    delete d->header;
    delete d->footer;
    delete d->cond_block;
    delete d->body_block;
    delete d;

    d = NULL;
}

int dtkComposerNodeControlWhile::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlWhile::header(void)
{
    return d->header;
}

dtkComposerNodeLeaf *dtkComposerNodeControlWhile::footer(void)
{
    return d->footer;
}

dtkComposerNodeComposite *dtkComposerNodeControlWhile::block(int id)
{
    if(id == 0)
        return d->cond_block;

    if(id == 1)
        return d->body_block;

    return NULL;
}

void dtkComposerNodeControlWhile::setInputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlWhile::setConditions(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlWhile::setOutputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlWhile::setVariables(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

int dtkComposerNodeControlWhile::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeControlWhile::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlWhile::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

QString dtkComposerNodeControlWhile::type(void)
{
    return "while";
}

QString dtkComposerNodeControlWhile::titleHint(void)
{
    return "While";
}
