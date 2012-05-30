/* dtkComposerNodePlotCurve.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:32:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 29 22:55:26 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPLOTCURVE_H
#define DTKCOMPOSERNODEPLOTCURVE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

#include <QtCore>

class dtkComposerNodePlotCurvePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePlotCurve : public QObject, public dtkComposerNodeLeaf
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
        switch(port) {
        case 0:
            return "x";
        case 1:
            return "y";
        default:
            return "port";
        }
    }

    inline QString outputLabelHint(int) {
        return "curve";
    }

public:
    void run(void);

signals:
    void runned(void);

protected slots:
    void onRun(void);

private:
    dtkComposerNodePlotCurvePrivate *d;
};

#endif
