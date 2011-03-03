/* dtkPlotData.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 11:27:04 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 14:15:15 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTDATA_H
#define DTKPLOTDATA_H

#include <QtGui>

#include "dtkPlotExport.h"

class dtkPlotCurve;
class dtkPlotPoint;
class dtkPlotDataPrivate;

class DTKPLOT_EXPORT dtkPlotData : public QGraphicsItem
{
public:
    typedef QList<dtkPlotPoint *> dtkPlotDataPoints;

public:
     dtkPlotData(void);
    ~dtkPlotData(void);

    dtkPlotData& operator<<(dtkPlotPoint *point);

    dtkPlotDataPoints points(void);

    void   setFillColor(const QColor& color);
    void setStrokeColor(const QColor& color);

public:
    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkPlotDataPrivate *d;
};

#endif
