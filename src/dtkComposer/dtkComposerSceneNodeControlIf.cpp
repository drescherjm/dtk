/* dtkComposerSceneNodeControlIf.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 16:21:46 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  8 16:27:18 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControlIf.h"

class dtkComposerSceneNodeControlIfPrivate
{
public:
    dtkComposerSceneNodeComposite *then_block;
    dtkComposerSceneNodeComposite *else_block;
};

dtkComposerSceneNodeControlIf::dtkComposerSceneNodeControlIf(void) : dtkComposerSceneNodeControl(), d(new dtkComposerSceneNodeControlIfPrivate)
{
    d->then_block = new dtkComposerSceneNodeComposite;
    d->else_block = new dtkComposerSceneNodeComposite;

    this->addBlock(d->then_block);
    this->addBlock(d->else_block);
}

dtkComposerSceneNodeControlIf::~dtkComposerSceneNodeControlIf(void)
{
    delete d->then_block;
    delete d->else_block;
    delete d;

    d = NULL;
}

QString dtkComposerSceneNodeControlIf::type(void)
{
    return "if";
}
