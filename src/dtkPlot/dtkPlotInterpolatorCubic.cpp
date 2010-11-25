/* dtkPlotInterpolatorCubic.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 16:31:53 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 25 10:35:13 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 50
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"
#include "dtkPlotData.h"
#include "dtkPlotInterpolatorCubic.h"
#include "dtkPlotPoint.h"

dtkPlotCurve *dtkPlotInterpolatorCubic::interpolate(dtkPlotData *data)
{
    static qreal smooth_value = 0.6;

    dtkPlotData::dtkPlotDataPoints points = data->points();

    qSort(points.begin(), points.end(), dtkPlotInterpolatorLessThan);

    QPainterPath path;

    path.moveTo(points.first()->pos());

    int n = points.count();

    for(int i = 0; i < n-1; i++) {

        qreal x0 = (i>=1) ? points.at(i-1)->x() : points.at(i)->x();
        qreal y0 = (i>=1) ? points.at(i-1)->y() : points.at(i)->y();

        qreal x1 = points.at(i)->x();
        qreal y1 = points.at(i)->y();

        qreal x2 = points.at(i+1)->x();
        qreal y2 = points.at(i+1)->y();

        qreal x3 = (i+2<=n-1) ? points.at(i+2)->x() : points.at(i+1)->x();
        qreal y3 = (i+2<=n-1) ? points.at(i+2)->y() : points.at(i+1)->y();

        qreal xc1 = (x0+x1)/2.0;
        qreal yc1 = (y0+y1)/2.0;
        qreal xc2 = (x1+x2)/2.0;
        qreal yc2 = (y1+y2)/2.0;
        qreal xc3 = (x2+x3)/2.0;
        qreal yc3 = (y2+y3)/2.0;
        
        qreal len1 = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
        qreal len2 = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
        qreal len3 = sqrt((x3-x2)*(x3-x2) + (y3-y2)*(y3-y2));
        
        qreal k1 = len1/(len1+len2);
        qreal k2 = len2/(len2+len3);
        
        qreal xm1 = xc1+(xc2-xc1)*k1;
        qreal ym1 = yc1+(yc2-yc1)*k1;
        
        qreal xm2 = xc2+(xc3-xc2)*k2;
        qreal ym2 = yc2+(yc3-yc2)*k2;
        
        qreal ctrl1_x = xm1+(xc2-xm1)*smooth_value+x1-xm1;
        qreal ctrl1_y = ym1+(yc2-ym1)*smooth_value+y1-ym1;
        
        qreal ctrl2_x = xm2+(xc2-xm2)*smooth_value+x2-xm2;
        qreal ctrl2_y = ym2+(yc2-ym2)*smooth_value+y2-ym2;

        // -- The following draws control points

        // QGraphicsLineItem *line1 = new QGraphicsLineItem(data);
        // line1->setLine(x1, y1, ctrl1_x, ctrl1_y);
        // line1->setPen(QPen(Qt::black, Qt::DashLine));

        // QGraphicsEllipseItem *ctrl1 = new QGraphicsEllipseItem(data);
        // ctrl1->setRect(ctrl1_x-3, ctrl1_y-3, 6, 6);
        // ctrl1->setPen(QPen(Qt::black));
        // ctrl1->setBrush(Qt::red);

        // QGraphicsLineItem *line2 = new QGraphicsLineItem(data);
        // line2->setLine(ctrl2_x, ctrl2_y, x2, y2);
        // line2->setPen(QPen(Qt::black, Qt::DashLine));

        // QGraphicsEllipseItem *ctrl2 = new QGraphicsEllipseItem(data);
        // ctrl2->setRect(ctrl2_x-3, ctrl2_y-3, 6, 6);
        // ctrl2->setPen(QPen(Qt::black));
        // ctrl2->setBrush(Qt::red);

        path.cubicTo(ctrl1_x, ctrl1_y, ctrl2_x, ctrl2_y, x2, y2);
    }

    dtkPlotCurve *curve = new dtkPlotCurve;
    curve->setPath(path);

    return curve;
}
