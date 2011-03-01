/* dtkComposerNodeConditional.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 18:30:34 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeConditional.h"

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeConditionalPrivate
{
public:
    dtkComposerNodeControlBloc *bloc_then;
    dtkComposerNodeControlBloc *bloc_else;
};

dtkComposerNodeConditional::dtkComposerNodeConditional(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeConditionalPrivate)
{
    d->bloc_then = this->addBlock();
    d->bloc_else = this->addBlock();

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
    qDebug() << DTK_PRETTY_FUNCTION;
}
