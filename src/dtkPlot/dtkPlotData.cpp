/* dtkPlotData.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 11:31:18 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 12:45:08 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 70
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotData.h"
#include "dtkPlotInterpolator.h"
#include "dtkPlotPoint.h"

// /////////////////////////////////////////////////////////////////
// dtkPlotDataPrivate
// /////////////////////////////////////////////////////////////////

class dtkPlotDataPrivate
{
public:
    void computeRect(void);

public:
    QRectF rect;

    QColor fillColor;
    QColor strokeColor;

    QList<dtkPlotPoint *> points;
};

void dtkPlotDataPrivate::computeRect(void)
{
    qreal xmin, ymin;
    qreal xmax, ymax;

    xmin = xmax = points.first()->x();
    ymin = ymax = points.first()->y();

    foreach(dtkPlotPoint *point, points) {
        xmin = (point->x() < xmin) ? point->x() : xmin;
        ymin = (point->y() < ymin) ? point->y() : ymin;
        xmax = (point->x() > xmax) ? point->x() : xmax;
        ymax = (point->y() > ymax) ? point->y() : ymax;
    }

    rect = QRect(xmin, ymin, xmax-xmin, ymax-ymin);
}

// /////////////////////////////////////////////////////////////////
// dtkPlotData
// /////////////////////////////////////////////////////////////////

dtkPlotData::dtkPlotData(void) : QGraphicsItem(), d(new dtkPlotDataPrivate)
{
    d->fillColor = Qt::red;
    d->strokeColor = Qt::black;
}

dtkPlotData::~dtkPlotData(void)
{
    delete d;
    
    d = NULL;
}

dtkPlotData& dtkPlotData::operator<<(dtkPlotPoint *point)
{
    d->points << point;
    d->computeRect();

    // point->setFillColor(d->fillColor);
    // point->setStrokeColor(d->strokeColor);

    point->setParentItem(this);

    return *(this);
}

dtkPlotData::dtkPlotDataPoints dtkPlotData::points(void)
{
    return d->points;
}

void dtkPlotData::setFillColor(const QColor& color)
{
    d->fillColor = color;

    foreach(dtkPlotPoint *point, d->points)
        point->setFillColor(color);
}

void dtkPlotData::setStrokeColor(const QColor& color)
{
    d->strokeColor = color;

    foreach(dtkPlotPoint *point, d->points)
        point->setStrokeColor(color);
}

QRectF dtkPlotData::boundingRect(void) const
{
    return d->rect;
}

void dtkPlotData::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
