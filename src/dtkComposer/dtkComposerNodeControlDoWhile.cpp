/* dtkComposerNodeControlDoWhile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 11:52:46 2012 (+0100)
 *           By: tkloczko
 *     Update #: 39
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

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhilePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlDoWhilePrivate
{
public:
    dtkComposerNodeProxy *header;
    dtkComposerNodeProxy *footer;

    dtkComposerNodeComposite *cond_block;
    dtkComposerNodeComposite *body_block;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlDoWhile::dtkComposerNodeControlDoWhile(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlDoWhilePrivate)
{
    d->header = new dtkComposerNodeProxy;
    delete d->header->removeReceiver(0);
    delete d->header->removeEmitter(0);
    d->header->setAsHeader(true);

    d->footer = new dtkComposerNodeProxy;
    delete d->footer->removeReceiver(0);
    delete d->footer->removeEmitter(0);
    d->footer->setAsFooter(true);

    d->cond_block = new dtkComposerNodeComposite;
    d->cond_block->setTitleHint("Conditional");

    d->body_block = new dtkComposerNodeComposite;
    d->body_block->setTitleHint("Body");
}

dtkComposerNodeControlDoWhile::~dtkComposerNodeControlDoWhile(void)
{
    delete d->header;
    delete d->footer;
    delete d->cond_block;
    delete d->body_block;
    delete d;

    d = NULL;
}

int dtkComposerNodeControlDoWhile::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlDoWhile::header(void)
{
    return d->header;
}

dtkComposerNodeLeaf *dtkComposerNodeControlDoWhile::footer(void)
{
    return d->footer;
}

dtkComposerNodeComposite *dtkComposerNodeControlDoWhile::block(int id)
{
    if(id == 0)
        return d->cond_block;

    if(id == 1)
        return d->body_block;

    return NULL;
}

void dtkComposerNodeControlDoWhile::setInputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlDoWhile::setConditions(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlDoWhile::setOutputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlDoWhile::setVariables(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

int dtkComposerNodeControlDoWhile::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeControlDoWhile::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlDoWhile::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

QString dtkComposerNodeControlDoWhile::type(void)
{
    return "do while";
}

QString dtkComposerNodeControlDoWhile::titleHint(void)
{
    return "Do While";
}
