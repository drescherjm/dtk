/* dtkComposerSceneNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:53:59 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 12:51:49 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 74
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControl.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerScenePort.h"

class dtkComposerSceneNodeControlPrivate
{
public:
    dtkComposerSceneNodeLeaf *header;
    dtkComposerSceneNodeLeaf *footer;

public:
    QList<dtkComposerSceneNodeComposite *> blocks;
};

dtkComposerSceneNodeControl::dtkComposerSceneNodeControl(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeControlPrivate)
{
    d->header = NULL;
    d->footer = NULL;

// -- Development code

    dtkComposerSceneNodeLeaf *header = new dtkComposerSceneNodeLeaf;
    header->addInputPort(new dtkComposerScenePort(0, dtkComposerScenePort::Input, d->header));
    header->setParent(this);

    dtkComposerSceneNodeComposite *cond_block = new dtkComposerSceneNodeComposite;
    cond_block->setParent(this);
    
    dtkComposerSceneNodeComposite *body_block = new dtkComposerSceneNodeComposite;
    body_block->setParent(this);

    dtkComposerSceneNodeComposite *incr_block = new dtkComposerSceneNodeComposite;
    incr_block->setParent(this);

    dtkComposerSceneNodeLeaf *footer = new dtkComposerSceneNodeLeaf;
    footer->addOutputPort(new dtkComposerScenePort(0, dtkComposerScenePort::Output, d->header));
    footer->setParent(this);

// --

    this->setHeader(header);
    this->setFooter(footer);

    this->addBlock(cond_block);
    this->addBlock(body_block);
    this->addBlock(incr_block);

// -- Development code
}

dtkComposerSceneNodeControl::~dtkComposerSceneNodeControl(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeControl::wrap(dtkComposerNode *wrapee)
{
    dtkComposerNodeControl *control = dynamic_cast<dtkComposerNodeControl *>(wrapee);

    if(!control)
        return;

    dtkComposerSceneNode::wrap(wrapee);    
    
    qDebug() << __func__;
}

void dtkComposerSceneNodeControl::setHeader(dtkComposerSceneNodeLeaf *header)
{
    d->header = header;
}

void dtkComposerSceneNodeControl::setFooter(dtkComposerSceneNodeLeaf *footer)
{
    d->footer = footer;
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
    qDebug() << __func__;
}

QRectF dtkComposerSceneNodeControl::boundingRect(void) const
{
    qDebug() << __func__;
}

void dtkComposerSceneNodeControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
