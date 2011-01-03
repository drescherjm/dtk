/* dtkPlotInterpolatorLinear.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 12:58:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 16:34:40 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"
#include "dtkPlotData.h"
#include "dtkPlotInterpolatorLinear.h"
#include "dtkPlotPoint.h"

dtkPlotCurve *dtkPlotInterpolatorLinear::interpolate(dtkPlotData *data)
{
    dtkPlotData::dtkPlotDataPoints points = data->points();

    qSort(points.begin(), points.end(), dtkPlotInterpolatorLessThan);

    QPainterPath path;
    path.moveTo(points.first()->pos());
    for(int i = 1; i < points.count(); i++)
        path.lineTo(points.at(i)->pos());

    dtkPlotCurve *curve = new dtkPlotCurve;
    curve->setPath(path);

    return curve;
}
