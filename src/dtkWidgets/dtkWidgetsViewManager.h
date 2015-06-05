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

#include "dtkWidgetsExport.h"

#include <QtWidgets/QFrame>

class dtkWidgetsViewManagerPrivate;

class DTKWIDGETS_EXPORT dtkWidgetsViewManager : public QFrame
{
    Q_OBJECT

public:
     dtkWidgetsViewManager(QWidget *parent = 0);
    ~dtkWidgetsViewManager(void);

public:
    void addWidget(QWidget *widget);
    void setCurrentWidget(QWidget *widget);

signals:
    void focused(QWidget *view);

public slots:
    void clear(void);
    void hideCurrentWidget(void);

private:
    dtkWidgetsViewManagerPrivate *d;
};

//
// dtkWidgetsViewManager.h ends here
