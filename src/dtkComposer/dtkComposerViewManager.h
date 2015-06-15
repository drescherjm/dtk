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

#include "dtkComposerExport.h"

#include <QtWidgets/QFrame>

class dtkComposerViewManagerPrivate;
class dtkComposerViewWidget;

class DTKCOMPOSER_EXPORT dtkComposerViewManager : public QFrame
{
    Q_OBJECT

public:
     dtkComposerViewManager(QWidget *parent = 0);
    ~dtkComposerViewManager(void);

signals:
    void focused(dtkComposerViewWidget *view);

public slots:
    void clear(void);

public slots:
    void onViewFocused(dtkComposerViewWidget *widget);

private:
    dtkComposerViewManagerPrivate *d;
};

//
// dtkComposerViewManager.h ends here
