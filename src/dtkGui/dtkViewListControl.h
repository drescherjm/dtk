/* dtkViewListControl.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Oct 31 12:49:39 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. oct. 10 16:14:56 2013 (+0200)
 *           By: Etienne
 *     Update #: 18
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

protected slots:
    void onLayoutHorizontally(void);
    void onLayoutVertically(void);
    void onLayoutGrid(void);
    void onLayoutCloseAll(void);

private:
    dtkViewListControlPrivate *d;
};

#endif
