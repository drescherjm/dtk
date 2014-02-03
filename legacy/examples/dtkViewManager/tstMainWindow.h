/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:42:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:43:09 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef TSTMAINWINDOW_H
#define TSTMAINWINDOW_H

#include <QtGui/QMainWindow>

class tstMainWindowPrivate;

class tstMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

private:
     tstMainWindowPrivate *d;
};

#endif
