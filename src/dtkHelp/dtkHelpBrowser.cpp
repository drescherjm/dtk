/* dtkHelpBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 15:56:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 13:29:51 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 140
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkHelpBrowser.h"
#include "dtkHelpController.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkHelpBrowser
// /////////////////////////////////////////////////////////////////

class dtkHelpBrowserPrivate
{
public:
};

dtkHelpBrowser::dtkHelpBrowser(QWidget *parent) : QWebView(parent), d(new dtkHelpBrowserPrivate)
{
    this->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(this, SIGNAL(linkClicked(const QUrl&)), this, SLOT(setSource(const QUrl&)));
}

dtkHelpBrowser::~dtkHelpBrowser(void)
{
    delete d;

    d = NULL;
}

QAction *dtkHelpBrowser::backwardAction(void)
{
    return this->pageAction(QWebPage::Back);
}

QAction *dtkHelpBrowser::forwardAction(void)
{
    return this->pageAction(QWebPage::Forward);
}

void dtkHelpBrowser::setSource(const QUrl& url)
{
    QUrl filteredUrl = dtkHelpController::instance()->filter(url);

    this->load(filteredUrl);

    emit sourceChanged(filteredUrl);
}
