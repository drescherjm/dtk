/* dtkComposerNodePlotCurveAppendPoint.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:32:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 21 14:04:36 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPLOTCURVEAPPENDPOINT_H
#define DTKCOMPOSERNODEPLOTCURVEAPPENDPOINT_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

#include <dtkPlot/dtkPlotCurve.h>

#include <QtCore>

class dtkComposerNodePlotCurveAppendPointPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePlotCurveAppendPoint : public QObject, public dtkComposerNodeLeaf
{
    Q_OBJECT

public:
     dtkComposerNodePlotCurveAppendPoint(void);
    ~dtkComposerNodePlotCurveAppendPoint(void);

public:
    inline QString type(void) {
        return "dtkPlotCurveAppendPoint";
    }

    inline QString titleHint(void) {
        return "Plot curve append point";
    }

public:
    inline QString inputLabelHint(int port) {
        switch(port) {
        case 0:
            return "curve";
        case 1:
            return "x";
        case 2:
            return "y";
        default:
            return "port";
        }
    }

    inline QString outputLabelHint(int) {
        return "curve";
    }

public:
    dtkPlotCurve *curve(void);

public:
    void run(void);

private:
    dtkComposerNodePlotCurveAppendPointPrivate *d;
};

#endif
