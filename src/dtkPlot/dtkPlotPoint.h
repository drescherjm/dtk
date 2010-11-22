/* dtkPlotPoint.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Nov 22 11:17:51 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 22 12:04:46 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
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

class dtkPlotPointPrivate;

class dtkPlotPoint : public QGraphicsItem
{
public:
     dtkPlotPoint(void);
     dtkPlotPoint(qreal x, qreal y);
    ~dtkPlotPoint(void);

    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    void setFillColor(const QColor& color);
    void setStrokeColor(const QColor& color);
    
private:
    dtkPlotPointPrivate *d;
};

#endif
