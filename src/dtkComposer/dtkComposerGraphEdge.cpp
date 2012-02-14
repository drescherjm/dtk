/* dtkComposerGraphEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 10 12:38:04 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"

class dtkComposerGraphEdgePrivate
{
public:
    dtkComposerGraphNode *source;
    dtkComposerGraphNode *destination;
};

dtkComposerGraphEdge::dtkComposerGraphEdge(void) : QGraphicsItem(), d(new dtkComposerGraphEdgePrivate)
{
    d->source = NULL;
    d->destination = NULL;

    this->setZValue(0);
}

dtkComposerGraphEdge::~dtkComposerGraphEdge(void)
{
    delete d;

    d = NULL;
}

dtkComposerGraphNode *dtkComposerGraphEdge::source(void)
{
    return d->source;
}

dtkComposerGraphNode *dtkComposerGraphEdge::destination(void)
{
    return d->destination;
}

void dtkComposerGraphEdge::setSource(dtkComposerGraphNode *source)
{
    d->source = source;
}
void dtkComposerGraphEdge::setDestination(dtkComposerGraphNode *destination)
{
    d->destination = destination;
}


QRectF dtkComposerGraphEdge::boundingRect(void) const
{
    if(!d->source || !d->destination)
        return QRectF();

    QPointF s = d->source->sceneBoundingRect().center();
    QPointF e = d->destination->sceneBoundingRect().center();

    return QRectF(s, e);
}

void dtkComposerGraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPointF s = d->source->sceneBoundingRect().center();
    QPointF e = d->destination->sceneBoundingRect().center();

    painter->drawLine(s, e);
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdgeList
// /////////////////////////////////////////////////////////////////

dtkComposerGraphEdgeList::dtkComposerGraphEdgeList(void) : QList<dtkComposerGraphEdge *>()
{

}

dtkComposerGraphEdgeList::dtkComposerGraphEdgeList(const QList<dtkComposerGraphEdge *>& other) : QList<dtkComposerGraphEdge *>(other)
{

}
