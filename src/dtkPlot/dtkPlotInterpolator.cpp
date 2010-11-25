/* dtkPlotInterpolator.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 12:52:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 16:35:35 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotInterpolator.h"
#include "dtkPlotPoint.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

bool dtkPlotInterpolatorLessThan(dtkPlotPoint *p1, dtkPlotPoint *p2)
{
    return p1->x() <= p2->x();
}

// /////////////////////////////////////////////////////////////////
// dtkPlotInterpolator
// /////////////////////////////////////////////////////////////////

class dtkPlotInterpolatorPrivate
{
public:

};

dtkPlotInterpolator::dtkPlotInterpolator(void) : d(new dtkPlotInterpolatorPrivate)
{

}

dtkPlotInterpolator::~dtkPlotInterpolator(void)
{
    delete d;

    d = NULL;
}
