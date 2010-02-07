/* dtkAssistantMainWindow.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 18:04:43 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 15:38:45 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
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

    void readSettings(void);
    void writeSettings(void);

protected slots:
    void onRegisterClicked(void);
    void onUnregisterClicked(void);
    void onUrlChanged(const QUrl& url);
    void onLinksActivated(const QMap<QString, QUrl>& urls, const QString& keyword);
    void onAddressFocusTriggered(void);
    void onSearchFocusTriggered(void);

protected:
    void closeEvent(QCloseEvent *event);

private:
    dtkAssistantMainWindowPrivate *d;
};

#endif
