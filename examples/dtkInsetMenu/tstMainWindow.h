/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jun  2 13:57:57 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Jun  6 18:09:52 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTMAINWINDOW_H
#define TSTMAINWINDOW_H

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// tstWorkspace
// /////////////////////////////////////////////////////////////////

class dtkInsetMenu;

class tstWorkspacePrivate;

class tstWorkspace : public QWidget
{
    Q_OBJECT

public:
     tstWorkspace(QWidget *parent = 0);
    ~tstWorkspace(void);

    dtkInsetMenu *inset(void);
                       
public slots:
    void toggle(void);

private:
    tstWorkspacePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate;

class tstMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

protected slots:
    void switchToWorkspace1(void);
    void switchToWorkspace2(void);
    void switchToWorkspace3(void);
    void toggle(void);

private:
    tstMainWindowPrivate *d;
};

#endif // TSTMAINWINDOW_H
