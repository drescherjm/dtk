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

class DTKCOMPOSER_EXPORT dtkComposerViewManager : public QFrame
{
    Q_OBJECT

public:
     dtkComposerViewManager(QWidget *parent = 0);
    ~dtkComposerViewManager(void);

public:
    void addWidget(QWidget *widget);
    void setCurrentWidget(QWidget *widget);

signals:
    void focused(QWidget *view);

public slots:
    void clear(void);
    void hideCurrentWidget(void);

private:
    dtkComposerViewManagerPrivate *d;
};

//
// dtkComposerViewManager.h ends here
