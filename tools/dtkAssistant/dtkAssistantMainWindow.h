/* dtkAssistantMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 18:04:43 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 13:38:04 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 21
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
    void onRegisterClicked(void);
    void onUnregisterClicked(void);
    void onUrlChanged(const QUrl& url);
    void onLinksActivated(const QMap<QString, QUrl>& urls, const QString& keyword);

private:
    dtkAssistantMainWindowPrivate *d;
};

#endif
