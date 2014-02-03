/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Sep  5 13:31:23 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 13:40:39 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTMAINWINDOW_H
#define TSTMAINWINDOW_H

#include <QtCore>
#include <QtGui>

class tstMainWindowPrivate;

class tstMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

protected slots:
    void onItemClicked(QListWidgetItem *item);

private:
    tstMainWindowPrivate *d;
};

#endif
