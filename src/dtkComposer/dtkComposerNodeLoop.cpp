/* dtkComposerNodeLoop.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Mar  7 09:26:54 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  8 15:39:18 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeLoop.h"

#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeLoopPrivate
{
public:
    dtkComposerNodeControlBlock *block_loop;
    dtkComposerNodeControlBlock *block_post;
};

dtkComposerNodeLoop::dtkComposerNodeLoop(dtkComposerNode *parent) : dtkComposerNodeControl(parent), d(new dtkComposerNodeLoopPrivate)
{
    d->block_loop = this->addBlock("loop");
    d->block_loop->setInteractive(true);

    d->block_post = this->addBlock("post");
    d->block_post->setInteractive(true);

    this->setColor(QColor("#004b07"));
    this->setTitle("Loop");
    this->setType("dtkComposerLoop");
}

dtkComposerNodeLoop::~dtkComposerNodeLoop(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLoop::update(void)
{
    // qDebug() << DTK_PRETTY_FUNCTION;
}

void dtkComposerNodeLoop::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    DTK_UNUSED(edge);
    DTK_UNUSED(property);

    // qDebug() << DTK_PRETTY_FUNCTION;
}

void dtkComposerNodeLoop::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    DTK_UNUSED(edge);
    DTK_UNUSED(property);

    // qDebug() << DTK_PRETTY_FUNCTION;
}
