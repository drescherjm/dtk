/* dtkPlotCurve.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 24 13:54:26 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 24 14:09:27 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLOTCURVE_H
#define DTKPLOTCURVE_H

#include <QtGui>

class dtkPlotCurvePrivate;

class dtkPlotCurve : public QGraphicsPathItem
{
public:
     dtkPlotCurve(void);
    ~dtkPlotCurve(void);

private:
    dtkPlotCurvePrivate *d;
};

#endif
