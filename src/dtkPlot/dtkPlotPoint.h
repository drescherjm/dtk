/* dtkPlotPoint.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 11:17:51 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 11:30:08 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTPOINT_H
#define DTKPLOTPOINT_H

#include <QtGui>

#include "dtkPlotExport.h"

class dtkPlotPointPrivate;

class DTKPLOT_EXPORT dtkPlotPoint : public QGraphicsItem
{
public:
     dtkPlotPoint(void);
     dtkPlotPoint(qreal x, qreal y);
    ~dtkPlotPoint(void);

    void setFillColor(const QColor& color);
    void setStrokeColor(const QColor& color);

public:
    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    
private:
    dtkPlotPointPrivate *d;
};

#endif
