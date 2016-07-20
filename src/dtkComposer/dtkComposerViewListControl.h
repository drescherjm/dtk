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

#include <QtWidgets>

class dtkComposerViewLayout;
class dtkComposerViewList;
class dtkComposerViewListControlPrivate;

class DTKCOMPOSER_EXPORT dtkComposerViewListControl : public QFrame
{
    Q_OBJECT

public:
    dtkComposerViewListControl(QWidget *parent = 0);
    ~dtkComposerViewListControl(void);

public:
    void setLayout(dtkComposerViewLayout *layout);
    void setList(dtkComposerViewList *list);

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
    dtkComposerViewListControlPrivate *d;
};

//
// dtkComposerViewListControl.h ends here
