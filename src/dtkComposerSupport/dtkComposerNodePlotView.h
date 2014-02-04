/* dtkComposerNodePlotView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 29 14:32:55 2012 (+0200)
 * Version: $Id$
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODEPLOTVIEW_H
#define DTKCOMPOSERNODEPLOTVIEW_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeafView.h"

#include <QtCore>

class dtkPlotView;

class dtkComposerNodePlotViewPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodePlotView : public QObject, public dtkComposerNodeLeafView
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
    dtkAbstractView *view(void);

public:
    inline QString inputLabelHint(int port) {
        switch(port) {
        case 0:
            return "curve";
        case 1:
            return "curves list";
        case 2:
            return "title";
        case 3:
            return "x-axis label";
        case 4:
            return "y-axis label";
        default:
            return dtkComposerNodeLeaf::inputLabelHint(port);
        }
    }

public:
    virtual void run(void);

private:
    dtkComposerNodePlotViewPrivate *d;
};

#endif
