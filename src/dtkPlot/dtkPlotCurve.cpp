/* dtkPlotCurve.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:09:17 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  7 16:26:00 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
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

dtkPlotCurve::dtkPlotCurve(const QString& title) : QwtPlotCurve(title), d(new dtkPlotCurvePrivate)
{

}

dtkPlotCurve::~dtkPlotCurve(void)
{
    delete d;

    d = NULL;
}
