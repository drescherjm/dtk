/* dtkPlotCurve.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:05:08 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  7 16:38:47 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTCURVE_H
#define DTKPLOTCURVE_H

#include <qwt_plot_curve.h>

class dtkPlotCurvePrivate;

class dtkPlotCurve : public QwtPlotCurve
{
public:
     dtkPlotCurve(const QString& title = QString());
    ~dtkPlotCurve(void);

private:
    dtkPlotCurvePrivate *d;
};

#endif
