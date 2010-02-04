/* dtkHelpBrowser.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 15:54:13 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  3 17:24:45 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
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

class dtkHelpBrowserPrivate;

class dtkHelpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
     dtkHelpBrowser(QWidget *parent = 0);
    ~dtkHelpBrowser(void);

    QVariant loadResource(int type, const QUrl &url);

private:
    dtkHelpBrowserPrivate *d;
};

#endif
