/* dtkComposerNodePlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:32:55 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. juil.  3 18:59:09 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 39
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPLOTVIEW_H
#define DTKCOMPOSERNODEPLOTVIEW_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeafView.h"

#include <QtCore>

class dtkComposerNodePlotViewPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePlotView : public QObject, public dtkComposerNodeLeafView
{
    Q_OBJECT

public:
     dtkComposerNodePlotView(void);
    ~dtkComposerNodePlotView(void);

public:
    inline QString type(void) {
        return "dtkPlotView";
    }

    inline QString titleHint(void) {
        return "Plot view";
    }

public:
    inline bool isAbstractView(void) const {return false;} ;

    inline QString abstractViewType(void) const {return "";};

public:
    inline QString inputLabelHint(int port) {
        switch(port) {
        case 0:
            return "curve";
        case 1:
            return "x-axis label";
        case 2:
            return "y-axis label";
        default:
            return dtkComposerNodeLeaf::inputLabelHint(port);
        }
    }

public:
    void run(void);

signals:
    void runned(void);

protected slots:
    void onRun(void);

private:
    dtkComposerNodePlotViewPrivate *d;
};

#endif
