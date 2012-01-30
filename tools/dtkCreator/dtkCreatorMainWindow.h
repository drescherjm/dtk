/* dtkCreatorMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:38:47 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 19:42:02 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCREATORMAINWINDOW_H
#define DTKCREATORMAINWINDOW_H

#include <QtGui/QMainWindow>

class dtkCreatorMainWindowPrivate;

class dtkCreatorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     dtkCreatorMainWindow(QWidget *parent = 0);
    ~dtkCreatorMainWindow(void);

    void readSettings(void);
    void writeSettings(void);

protected:
    void closeEvent(QCloseEvent *event);

private:
    dtkCreatorMainWindowPrivate *d;
};

#endif
