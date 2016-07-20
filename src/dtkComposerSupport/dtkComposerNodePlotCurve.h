/* dtkComposerNodePlotCurve.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:32:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. nov.  5 11:03:58 2013 (+0100)
 *           By: edelclau
 *     Update #: 34
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEPLOTCURVE_H
#define DTKCOMPOSERNODEPLOTCURVE_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QtCore>

class dtkComposerNodePlotCurvePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodePlotCurve : public QObject, public dtkComposerNodeLeaf
{
    Q_OBJECT

public:
    dtkComposerNodePlotCurve(void);
    ~dtkComposerNodePlotCurve(void);

public:
    inline QString type(void) {
        return "dtkPlotCurve";
    }

    inline QString titleHint(void) {
        return "Plot curve";
    }

public:
    inline QString inputLabelHint(int port) {
        switch (port) {
        case 0:
            return "vector x";

        case 1:
            return "vector y";

        default:
            return "port";
        }
    }

    inline QString outputLabelHint(int) {
        return "curve";
    }

public:
    void run(void);

private:
    dtkComposerNodePlotCurvePrivate *d;
};

#endif
