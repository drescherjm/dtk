/* dtkComposerGraphEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 20 15:07:43 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 100
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

public:
    int id;
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

int dtkComposerGraphEdge::id(void)
{
    return d->id;
}

dtkComposerGraphNode *dtkComposerGraphEdge::source(void)
{
    return d->source;
}

dtkComposerGraphNode *dtkComposerGraphEdge::destination(void)
{
    return d->destination;
}

void dtkComposerGraphEdge::setId(int id)
{
    d->id = id;
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

    if (d->id == 1)
        painter->setPen(Qt::blue);
    else if (d->id > 1) { // for switch case
        int c = (180 + 10 * d->id) % 255;
        // different levels of blue depending on id value.
        painter->setPen(QColor (50, 50, c));
    }
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
