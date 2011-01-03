/* dtkPlotInterpolatorCubic.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 16:31:05 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 16:31:46 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTINTERPOLATORCUBIC_H
#define DTKPLOTINTERPOLATORCUBIC_H

#include "dtkPlotInterpolator.h"

class dtkPlotInterpolatorCubicPrivate;

class dtkPlotInterpolatorCubic : public dtkPlotInterpolator
{
public:
    dtkPlotCurve *interpolate(dtkPlotData *data);
};

#endif
