/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:19:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 14:28:59 2012 (+0100)
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

#include <QMainWindow>

class dtkInterpreter;

class tstMainWindowPrivate;

class tstMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

    dtkInterpreter *interpreter(void);

protected:
    void closeEvent(QCloseEvent *event);

private:
    tstMainWindowPrivate *d;
};

#endif // TSTMAINWINDOW_H
