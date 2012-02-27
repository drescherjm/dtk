/* dtkComposerGraphEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 24 16:11:34 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 138
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
    d->id = 0;

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

    qreal xmin = qMin(s.x(), e.x());
    qreal xmax = qMax(s.x(), e.x());
    qreal ymin = qMin(s.y(), e.y());
    qreal ymax = qMax(s.y(), e.y());

    qreal x = xmin;
    qreal y = ymin;
    qreal w = xmax-xmin;
    qreal h = ymax-ymin;

    return QRectF(x, y, w, h);
}

void dtkComposerGraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPointF s = d->source->sceneBoundingRect().center();
    QPointF e = d->destination->sceneBoundingRect().center();

    if (d->id == 0)
        painter->setPen(Qt::black);
    else if (d->id == 1)
        painter->setPen(Qt::blue);
    else if (d->id > 1) { // for switch case
        int c = (180 + 10 * d->id) % 255;
        // different levels of blue depending on id value.
        painter->setPen(QColor (50, 50, c));
    }
    this->drawArrow(painter, s, e);
}

void dtkComposerGraphEdge::drawArrow(QPainter *p, QPointF from, QPointF to, qreal size, qreal end_margin)
{
    QPointF points[3];
    float a = atan2(from.y()-to.y(), from.x()-to.x());
    to.setX(to.x()+end_margin*cos(a));
    to.setY(to.y()+end_margin*sin(a));
    end_margin += size;
    a = atan2(from.y()-to.y(), from.x()-to.x());

    QPointF k(to.x()+size*cos(a), to.y()+size*sin(a));
    a += M_PI/2;
    size /= 2;
    QPointF i(k.x()+size*cos(a), k.y()+size*sin(a));
    QPointF j(k.x()-size*cos(a), k.y()-size*sin(a));

    p->save();
    p->setRenderHint(QPainter::Antialiasing, true);
    p->drawLine(from, k);
    points[0] = to;
    points[1] = i;
    points[2] = j;
    p->setPen(Qt::black);
    p->setBrush(Qt::black);
    p->drawConvexPolygon(points, 3);
    p->restore();
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
