/* dtkPlotCurve.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 13:56:44 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 14:43:28 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPlotCurve.h"

class dtkPlotCurvePrivate
{
public:
    
};

dtkPlotCurve::dtkPlotCurve(void) : QGraphicsPathItem(), d(new dtkPlotCurvePrivate)
{

}

dtkPlotCurve::~dtkPlotCurve(void)
{
    delete d;

    d = NULL;
}
