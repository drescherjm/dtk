/* dtkComposerNodeControlIf.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 29 10:09:06 2012 (+0100)
 *           By: tkloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlIf.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeComposite.h"

#include "dtkComposerTransmitterEmitter.h"
#include "dtkComposerTransmitterReceiver.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIfPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlIfPrivate
{
public:    
    dtkComposerNodeBoolean *header;
    dtkComposerNodeBoolean *footer;

    dtkComposerNodeComposite *then_block;
    dtkComposerNodeComposite *else_block;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlIf implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlIf::dtkComposerNodeControlIf(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlIfPrivate)
{
    d->header = new dtkComposerNodeBoolean;
    delete d->header->removeEmitter(0);

    d->footer = new dtkComposerNodeBoolean;
    delete d->footer->removeReceiver(0);

    d->then_block = new dtkComposerNodeComposite;
    d->then_block->setTitleHint("Then");

    d->else_block = new dtkComposerNodeComposite;
    d->else_block->setTitleHint("Else");
}

dtkComposerNodeControlIf::~dtkComposerNodeControlIf(void)
{
    delete d->header;
    delete d->footer;
    delete d->then_block;
    delete d->else_block;
    delete d;

    d = NULL;
}

int dtkComposerNodeControlIf::blockCount(void)
{
    return 2;
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::header(void)
{
    return d->header;
}

dtkComposerNodeLeaf *dtkComposerNodeControlIf::footer(void)
{
    return d->footer;
}

dtkComposerNodeComposite *dtkComposerNodeControlIf::block(int id)
{
    if(id == 0)
        return d->then_block;

    if(id == 1)
        return d->else_block;

    return NULL;
}

void dtkComposerNodeControlIf::setInputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlIf::setConditions(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlIf::setOutputs(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlIf::setVariables(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

int dtkComposerNodeControlIf::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeControlIf::begin(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

void dtkComposerNodeControlIf::end(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
}

QString dtkComposerNodeControlIf::type(void)
{
    return "if";
}

QString dtkComposerNodeControlIf::titleHint(void)
{
    return "If";
}
