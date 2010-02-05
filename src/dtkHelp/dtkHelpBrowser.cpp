/* dtkHelpBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 15:56:38 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  5 16:30:40 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 104
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
// dtkHelpBrowserCommand
// /////////////////////////////////////////////////////////////////

class dtkHelpBrowserCommand : public QUndoCommand
{
public:
    dtkHelpBrowserCommand(QUrl before, QUrl after, dtkHelpBrowser *browser);

    void undo(void);
    void redo(void);

private:
    dtkHelpBrowser *m_browser;

    QUrl m_before;
    QUrl m_after;
};

dtkHelpBrowserCommand::dtkHelpBrowserCommand(QUrl before, QUrl after, dtkHelpBrowser *browser)
{
    m_before = before;
    m_after = after;
    
    m_browser = browser;
}

void dtkHelpBrowserCommand::undo(void)
{
    if(m_before.isValid())
        m_browser->setContent(dtkHelpController::instance()->engine()->fileData(m_before));
}

void dtkHelpBrowserCommand::redo(void)
{
    if(m_after.isValid())
        m_browser->setContent(dtkHelpController::instance()->engine()->fileData(m_after));
}

// /////////////////////////////////////////////////////////////////
// dtkHelpBrowser
// /////////////////////////////////////////////////////////////////

class dtkHelpBrowserPrivate
{
public:
    QUndoStack *stack;

    QUrl currentUrl;
};

dtkHelpBrowser::dtkHelpBrowser(QWidget *parent) : QWebView(parent), d(new dtkHelpBrowserPrivate)
{
    d->stack = new QUndoStack(this);

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
    return d->stack->createUndoAction(this);
}

QAction *dtkHelpBrowser::forwardAction(void)
{
    return d->stack->createRedoAction(this);
}

void dtkHelpBrowser::setSource(const QUrl& url)
{
    QUrl filteredUrl;

    if(url.scheme() != "qthelp")
        filteredUrl = QUrl("qthelp://fr.inria.dtk/dtk/" + url.toString());
    else
        filteredUrl = url;

    d->stack->push(new dtkHelpBrowserCommand(d->currentUrl, filteredUrl, this));
    d->stack->redo();

    d->currentUrl = filteredUrl;

    emit sourceChanged(filteredUrl);
}
