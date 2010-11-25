/* dtkPlotInterpolator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 12:50:46 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 16:35:12 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTINTERPOLATOR_H
#define DTKPLOTINTERPOLATOR_H

class dtkPlotCurve;
class dtkPlotData;
class dtkPlotInterpolatorPrivate;
class dtkPlotPoint;

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

bool dtkPlotInterpolatorLessThan(dtkPlotPoint *p1, dtkPlotPoint *p2);

// /////////////////////////////////////////////////////////////////
// dtkPlotInterpolator
// /////////////////////////////////////////////////////////////////

class dtkPlotInterpolator
{
public:
             dtkPlotInterpolator(void);
    virtual ~dtkPlotInterpolator(void);

    virtual dtkPlotCurve *interpolate(dtkPlotData *data) = 0;

private:
    dtkPlotInterpolatorPrivate *d;
};

#endif
