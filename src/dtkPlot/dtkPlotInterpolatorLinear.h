/* dtkPlotInterpolatorLinear.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 12:57:01 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 14:16:09 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTINTERPOLATORLINEAR_H
#define DTKPLOTINTERPOLATORLINEAR_H

#include "dtkPlotInterpolator.h"

class dtkPlotInterpolatorLinearPrivate;

class dtkPlotInterpolatorLinear : public dtkPlotInterpolator
{
public:
    dtkPlotCurve *interpolate(dtkPlotData *data);
};

#endif
