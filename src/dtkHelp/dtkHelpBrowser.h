/* dtkHelpBrowser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 15:54:13 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  5 16:25:10 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKHELPBROWSER_H
#define DTKHELPBROWSER_H

#include <QtCore>
#include <QtGui>
#include <QtHelp>
#include <QtWebKit>

class dtkHelpBrowserPrivate;

class dtkHelpBrowser : public QWebView
{
    Q_OBJECT

public:
     dtkHelpBrowser(QWidget *parent = 0);
    ~dtkHelpBrowser(void);

    QAction *backwardAction(void);
    QAction *forwardAction(void);

signals:
    void sourceChanged(const QUrl& url);

public slots:
    void setSource(const QUrl& url);

private:
    dtkHelpBrowserPrivate *d;
};

#endif
