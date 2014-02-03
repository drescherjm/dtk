/* tstPlotCurveEcg.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 16:32:45 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  7 16:39:55 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTPLOTCURVEECG_H
#define TSTPLOTCURVEECG_H

#include <dtkPlot/dtkPlotCurve.h>

class tstPlotCurveEcg : public dtkPlotCurve
{
public:
     tstPlotCurveEcg(const QString& title);
    ~tstPlotCurveEcg(void);

    void read(const QString& file);
};

#endif
