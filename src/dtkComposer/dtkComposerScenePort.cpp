/* dtkComposerScenePort.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 13:59:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 16:31:23 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneNode.h"
#include "dtkComposerScenePort.h"

class dtkComposerScenePortPrivate
{
public:
    unsigned int id;

public:
    dtkComposerSceneNode *node;

public:
    QGraphicsEllipseItem *ellipse;
};

dtkComposerScenePort::dtkComposerScenePort(unsigned int id, dtkComposerSceneNode *parent) : QGraphicsItem(parent), d(new dtkComposerScenePortPrivate)
{
    d->id = id;
    d->node = parent;

    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(Qt::darkGray, 1));
    d->ellipse->setBrush(Qt::lightGray);
    d->ellipse->setRect(0, 0, 10, 10);
    
    this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setZValue(1);
}

dtkComposerScenePort::~dtkComposerScenePort(void)
{
    delete d;

    d = NULL;
}

unsigned int dtkComposerScenePort::id(void) const
{
    return d->id;
}

dtkComposerSceneNode *dtkComposerScenePort::node(void)
{
    return d->node;
}

QRectF dtkComposerScenePort::boundingRect(void) const
{
    return QRectF(0, 0, 10, 10);
}

void dtkComposerScenePort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
