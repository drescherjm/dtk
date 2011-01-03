/* dtkPlotPoint.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 11:20:01 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 14:44:28 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotPoint.h"

class dtkPlotPointPrivate
{
public:
    qreal x;
    qreal y;

public:
    QColor fillColor;
    QColor strokeColor;
};

dtkPlotPoint::dtkPlotPoint(void) : QGraphicsItem(), d(new dtkPlotPointPrivate)
{
    d->x = 0;
    d->y = 0;
    
    this->setPos(d->x*100, -d->y*100);
}

dtkPlotPoint::dtkPlotPoint(qreal x, qreal y) : QGraphicsItem(), d(new dtkPlotPointPrivate)
{
    d->x = x;
    d->y = y;

    this->setPos(d->x*100, -d->y*100);
    this->setZValue(50);
}

dtkPlotPoint::~dtkPlotPoint(void)
{
    delete d;

    d = NULL;
}

QRectF dtkPlotPoint::boundingRect(void) const
{
    return QRectF(-5, -5, 10, 10);
}

void dtkPlotPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(d->strokeColor);
    painter->setBrush(d->fillColor);
    painter->drawRoundedRect(-5, -5, 10, 10, 5, 5);
}

void dtkPlotPoint::setFillColor(const QColor& color)
{
    d->fillColor = color;
}

void dtkPlotPoint::setStrokeColor(const QColor& color)
{
    d->strokeColor = color;
}
