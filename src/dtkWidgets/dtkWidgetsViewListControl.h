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

#include <QtWidgets>

class dtkWidgetsViewLayout;
class dtkWidgetsViewList;
class dtkWidgetsViewListControlPrivate;

class DTKWIDGETS_EXPORT dtkWidgetsViewListControl : public QFrame
{
    Q_OBJECT

public:
     dtkWidgetsViewListControl(QWidget *parent = 0);
    ~dtkWidgetsViewListControl(void);

public:
    void setLayout(dtkWidgetsViewLayout *layout);
    void setList(dtkWidgetsViewList *list);

public:
    bool isEmpty(void) const;

public:
    void closeAllLayout(void);
    void layoutHorizontally(void);
    void layoutVertically(void);
    void layoutGrid(void);

public slots:
    void onActorStarted(QString view_name);

protected slots:
    void onLayoutHorizontally(void);
    void onLayoutVertically(void);
    void onLayoutGrid(void);
    void onLayoutCloseAll(void);

private:
    dtkWidgetsViewListControlPrivate *d;
};

//
// dtkWidgetsViewListControl.h ends here
