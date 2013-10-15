/* dtkViewListControl.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Oct 31 12:49:39 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKVIEWLISTCONTROL_H
#define DTKVIEWLISTCONTROL_H

#include "dtkGuiExport.h"

#include <QtGui>

class dtkViewLayout;
class dtkViewList;
class dtkViewListControlPrivate;

class DTKGUI_EXPORT dtkViewListControl : public QFrame
{
    Q_OBJECT

public:
     dtkViewListControl(QWidget *parent = 0);
    ~dtkViewListControl(void);

public:
    void setLayout(dtkViewLayout *layout);
    void setList(dtkViewList *list);

public slots:
    void onActorStarted(QString view_name);

protected slots:
    void onLayoutHorizontally(void);
    void onLayoutVertically(void);
    void onLayoutGrid(void);
    void onLayoutCloseAll(void);

private:
    dtkViewListControlPrivate *d;
};

#endif
