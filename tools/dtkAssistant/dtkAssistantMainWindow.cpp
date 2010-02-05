/* dtkAssistantMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 21:42:16 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  5 09:17:04 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 49
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAssistantMainWindow.h"

#include <dtkGui/dtkAddressBar.h>
#include <dtkGui/dtkNavigationBar.h>
#include <dtkGui/dtkSearchBar.h>

#include <dtkHelp/dtkHelpController.h>
#include <dtkHelp/dtkHelpBrowser.h>

class dtkAssistantMainWindowPrivate
{
public:
    dtkHelpBrowser *browser;

    QAction *backwardAction;
    QAction *forwardAction;

    dtkAddressBar *address;
    dtkNavigationBar *navigation;
    dtkSearchBar *search;

    QDockWidget *contentDock;
    QDockWidget *indexDock;
};

dtkAssistantMainWindow::dtkAssistantMainWindow(QWidget *parent) : QMainWindow(parent), d(new dtkAssistantMainWindowPrivate)
{
    d->browser = new dtkHelpBrowser(this);

    connect(dtkHelpController::instance()->engine()->contentWidget(), SIGNAL(linkActivated(const QUrl&)), d->browser, SLOT(setSource(const QUrl&)));
    connect(dtkHelpController::instance()->engine()->indexWidget(), SIGNAL(linkActivated(const QUrl&, const QString&)), d->browser, SLOT(setSource(const QUrl&)));

    connect(dtkHelpController::instance()->engine()->contentWidget(), SIGNAL(linkActivated(const QUrl&)), this, SLOT(onUrlChanged(const QUrl&)));
    connect(dtkHelpController::instance()->engine()->indexWidget(), SIGNAL(linkActivated(const QUrl&, const QString&)), this, SLOT(onUrlChanged(const QUrl&)));

    d->backwardAction = new QAction("Backward", this);
    d->backwardAction->setShortcut(Qt::AltModifier + Qt::Key_Left);

    d->forwardAction = new QAction("Forward", this);
    d->forwardAction->setShortcut(Qt::AltModifier + Qt::Key_Right);

    connect(d->backwardAction, SIGNAL(triggered()), d->browser, SLOT(backward()));
    connect(d->forwardAction, SIGNAL(triggered()), d->browser, SLOT(forward()));

    connect(d->browser, SIGNAL(backwardAvailable(bool)), d->backwardAction, SLOT(setEnabled(bool)));
    connect(d->browser, SIGNAL(forwardAvailable(bool)), d->forwardAction, SLOT(setEnabled(bool)));

    d->navigation = new dtkNavigationBar(this);

    connect(d->browser, SIGNAL(backwardAvailable(bool)), d->navigation->backwardButton(), SLOT(setEnabled(bool)));
    connect(d->browser, SIGNAL(forwardAvailable(bool)), d->navigation->forwardButton(), SLOT(setEnabled(bool)));

    connect(d->navigation->backwardButton(), SIGNAL(clicked()), d->backwardAction, SLOT(trigger()));
    connect(d->navigation->forwardButton(), SIGNAL(clicked()), d->forwardAction, SLOT(trigger()));

    d->address = new dtkAddressBar(this);
    d->address->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    d->search = new dtkSearchBar(this);
    d->search->setFixedWidth(200);

    connect(d->search, SIGNAL(textChanged(QString)), dtkHelpController::instance()->engine()->indexWidget(), SLOT(filterIndices(QString)));
    connect(d->search, SIGNAL(returnPressed()), dtkHelpController::instance()->engine()->indexWidget(), SLOT(activateCurrentItem()));

    QToolBar *toolbar = this->addToolBar("navigation");
    toolbar->addWidget(d->navigation);
    toolbar->addWidget(d->address);
    toolbar->addWidget(d->search);

    d->contentDock = new QDockWidget("Content", this);
    d->contentDock->setWidget(dtkHelpController::instance()->engine()->contentWidget());

    d->indexDock = new QDockWidget("Index", this);
    d->indexDock->setWidget(dtkHelpController::instance()->engine()->indexWidget());

    this->addDockWidget(Qt::LeftDockWidgetArea, d->contentDock);
    this->addDockWidget(Qt::LeftDockWidgetArea, d->indexDock);

    this->setCentralWidget(d->browser);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkAssistant");
}

dtkAssistantMainWindow::~dtkAssistantMainWindow(void)
{
    delete d;

    d = NULL;
}

void dtkAssistantMainWindow::onUrlChanged(const QUrl& url)
{
    d->address->setText(url.toString());
}
