// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeafView.h"

#include <QtCore>

class dtkComposerNodeViewPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeView declaration
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeView : public QObject, public dtkComposerNodeLeafView
{
    Q_OBJECT

public:
    dtkComposerNodeView(void);
    ~dtkComposerNodeView(void);

public:
    void run(void);

public:
    bool isAbstractView(void) const {
        return true;
    }

    QString abstractViewType(void) const {
        return "dtkAbstractView";
    }

public:
    QString type(void);
    QString titleHint(void);

public:
    QString inputLabelHint(int);
    QString outputLabelHint(int);

private:
    dtkComposerNodeViewPrivate *d;
};

//
// dtkComposerNodeView.h ends here
