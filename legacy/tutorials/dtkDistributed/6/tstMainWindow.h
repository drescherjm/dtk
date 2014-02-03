/* tstMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep 20 11:30:29 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. déc.  6 13:21:48 2011 (+0100)
 *           By: Nicolas Niclausse
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

    void onSubmit(void);

    void onDisconnect(void);
    void onDisconnected(const QUrl& server);

private slots:
    void onDataPosted(const QByteArray& data);
    void onJobStarted(QString jobid);

private:
    tstMainWindowPrivate *d;
};

#endif // TSTMAINWINDOW_H
