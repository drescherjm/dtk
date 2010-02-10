/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb  9 11:14:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb  9 16:08:50 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 11
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
#include <QtNetwork>

class tstMainWindowPrivate;

class tstMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     tstMainWindow(QWidget *parent = 0);
    ~tstMainWindow(void);

protected slots:
    void onRead(void);
    void onConnect(void);
    void onConnected(void);
    void onDisconnect(void);
    void onDisconnected(void);
    void onError(QAbstractSocket::SocketError);

private:
    tstMainWindowPrivate *d;
};

#endif // TSTMAINWINDOW_H
