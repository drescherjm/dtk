/* dtkComposerNodeControlDoWhile.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sat Feb 25 00:02:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 27 10:51:36 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlDoWhile.h"
#include "dtkComposerNodeLeaf.h"
#include "dtkComposerNodeBoolean.h"
#include "dtkComposerNodeComposite.h"

#include "dtkComposerEmitter.h"
#include "dtkComposerReceiver.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhilePrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlDoWhilePrivate
{
public:    
    dtkComposerNodeBoolean *header;
    dtkComposerNodeBoolean *footer;

    dtkComposerNodeComposite *cond_block;
    dtkComposerNodeComposite *body_block;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlDoWhile implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlDoWhile::dtkComposerNodeControlDoWhile(void) : dtkComposerNodeControl(), d(new dtkComposerNodeControlDoWhilePrivate)
{
    d->header = new dtkComposerNodeBoolean;
    delete d->header->removeReceiver(0);
    delete d->header->removeEmitter(0);

    d->footer = new dtkComposerNodeBoolean;
    delete d->footer->removeEmitter(0);

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
