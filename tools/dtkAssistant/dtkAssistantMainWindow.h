/* dtkAssistantMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 18:04:43 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  4 19:01:53 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKASSISTANTMAINWINDOW_H
#define DTKASSISTANTMAINWINDOW_H

#include <QtGui>

class dtkAssistantMainWindowPrivate;

class dtkAssistantMainWindow : public QMainWindow
{
    Q_OBJECT

public:
     dtkAssistantMainWindow(QWidget *parent = 0);
    ~dtkAssistantMainWindow(void);

public slots:
    void onUrlChanged(const QUrl& url);

private:
    dtkAssistantMainWindowPrivate *d;
};

#endif
