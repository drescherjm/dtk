/* dtkComposerSceneNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:53:59 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  8 16:17:15 2012 (+0100)
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
#include "dtkComposerSceneNodeControl.h"

class dtkComposerSceneNodeControlPrivate
{
public:
    QList<dtkComposerSceneNodeComposite *> blocks;
};

dtkComposerSceneNodeControl::dtkComposerSceneNodeControl(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeControlPrivate)
{
    
}

dtkComposerSceneNodeControl::~dtkComposerSceneNodeControl(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeControl::addBlock(dtkComposerSceneNodeComposite *block)
{
    d->blocks << block;
}

void dtkComposerSceneNodeControl::removeBlock(dtkComposerSceneNodeComposite *block)
{
    d->blocks.removeAll(block);
}

void dtkComposerSceneNodeControl::layout(void)
{

}

QRectF dtkComposerSceneNodeControl::boundingRect(void) const
{

}

void dtkComposerSceneNodeControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
