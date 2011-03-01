/* dtkComposerNodeConditional.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 13:03:58 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 28 13:53:16 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
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
};

dtkComposerNodeConditional::dtkComposerNodeConditional(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeConditionalPrivate)
{
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
