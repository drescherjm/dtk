/* dtkComposerNodeConditional.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  3 18:15:35 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeConditional.h"
#include "dtkComposerNodeControlBlock.h"

class dtkComposerNodeConditionalPrivate
{
public:
    dtkComposerNodeControlBlock *block_then;
    dtkComposerNodeControlBlock *block_else;
};

dtkComposerNodeConditional::dtkComposerNodeConditional(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeConditionalPrivate)
{
    d->block_then = this->addBlock("then");
    d->block_else = this->addBlock("else");

    this->setTitle("Conditional");
    this->setType("dtkComposerConditional");
}

dtkComposerNodeConditional::~dtkComposerNodeConditional(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeConditional::update(void)
{
    if(this->condition())
        foreach(dtkComposerNode *node, d->block_then->startNodes())
            node->update();
    else
        foreach(dtkComposerNode *node, d->block_else->startNodes())
            node->update();
}
