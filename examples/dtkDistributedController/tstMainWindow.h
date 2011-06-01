/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:12:05 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 14:52:52 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
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
    void onConnect(void);
    void onConnected(const QUrl& server);

    void onDisconnect(void);
    void onDisconnected(const QUrl& server);

private:
    tstMainWindowPrivate *d;
};

#endif // TSTMAINWINDOW_H
