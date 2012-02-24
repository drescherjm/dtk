/* dtkComposerNodeFor.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:14:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 24 16:47:27 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 72
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeFor.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeComposite.h"

#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeForPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeForPrivate
{
public:    
    dtkComposerNodeBoolean *header;
    dtkComposerNodeBoolean *footer;

    dtkComposerNodeComposite *cond_block;
    dtkComposerNodeComposite *body_block;
    dtkComposerNodeComposite *incr_block;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeFor implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeFor::dtkComposerNodeFor(void) : dtkComposerNodeControl(), d(new dtkComposerNodeForPrivate)
{
    d->header = new dtkComposerNodeBoolean;
    delete d->header->removeEmitter(0);

    d->footer = new dtkComposerNodeBoolean;
    delete d->footer->removeReceiver(0);

    d->cond_block = new dtkComposerNodeComposite;
    d->cond_block->setTitleHint("Conditional");

    d->body_block = new dtkComposerNodeComposite;
    d->body_block->setTitleHint("Body");

    d->incr_block = new dtkComposerNodeComposite;
    d->incr_block->setTitleHint("Increment");
}

dtkComposerNodeFor::~dtkComposerNodeFor(void)
{
    delete d->header;
    delete d->footer;
    delete d->cond_block;
    delete d->body_block;
    delete d->incr_block;
    delete d;

    d = NULL;
}

int dtkComposerNodeFor::blockCount(void)
{
    return 3;
}

dtkComposerNodeLeaf *dtkComposerNodeFor::header(void)
{
    return d->header;
}

dtkComposerNodeLeaf *dtkComposerNodeFor::footer(void)
{
    return d->footer;
}

dtkComposerNodeComposite *dtkComposerNodeFor::block(int id)
{
    if(id == 0)
        return d->cond_block;

    if(id == 1)
        return d->body_block;

    if(id == 2)
        return d->incr_block;

    return NULL;
}

void dtkComposerNodeFor::setInputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::setConditions(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::setOutputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::setVariables(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

int dtkComposerNodeFor::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeFor::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeFor::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

QString dtkComposerNodeFor::type(void)
{
    return "for";
}

QString dtkComposerNodeFor::titleHint(void)
{
    return "For";
}
