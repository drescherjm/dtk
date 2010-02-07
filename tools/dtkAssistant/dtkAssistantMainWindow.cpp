/* dtkAssistantMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 21:42:16 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  7 13:38:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 150
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

    dtkAddressBar *address;
    dtkNavigationBar *navigation;
    dtkSearchBar *search;

    QAction *backwardAction;
    QAction *forwardAction;

    QAction   *registerAction;
    QAction *unregisterAction;

    QDockWidget *contentDock;
    QDockWidget *indexDock;
};

dtkAssistantMainWindow::dtkAssistantMainWindow(QWidget *parent) : QMainWindow(parent), d(new dtkAssistantMainWindowPrivate)
{
    d->browser = new dtkHelpBrowser(this);

    connect(d->browser, SIGNAL(sourceChanged(const QUrl&)), this, SLOT(onUrlChanged(const QUrl&)));

    connect(dtkHelpController::instance()->engine()->contentWidget(), SIGNAL(linkActivated(const QUrl&)), d->browser, SLOT(setSource(const QUrl&)));
    connect(dtkHelpController::instance()->engine()->indexWidget(), SIGNAL(linkActivated(const QUrl&, const QString&)), d->browser, SLOT(setSource(const QUrl&)));
    connect(dtkHelpController::instance()->engine()->indexWidget(), SIGNAL(linksActivated(const QMap<QString, QUrl>&, const QString&)), this, SLOT(onLinksActivated(const QMap<QString, QUrl>&, const QString&)));

    d->backwardAction = d->browser->backwardAction();
    d->forwardAction = d->browser->forwardAction();

    d->registerAction = new QAction("Register", this);
    d->registerAction->setShortcut(Qt::ControlModifier + Qt::Key_I);
    connect(d->registerAction, SIGNAL(triggered()), this, SLOT(onRegisterClicked()));

    d->unregisterAction = new QAction("Unregister", this);
    connect(d->unregisterAction, SIGNAL(triggered()), this, SLOT(onUnregisterClicked()));

    d->navigation = new dtkNavigationBar(this);

    connect(d->navigation->backwardButton(), SIGNAL(clicked()), d->backwardAction, SLOT(trigger()));
    connect(d->navigation->forwardButton(), SIGNAL(clicked()), d->forwardAction, SLOT(trigger()));

    d->address = new dtkAddressBar(this);
    d->address->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(d->address, SIGNAL(addressEntered(const QUrl&)), d->browser, SLOT(setSource(const QUrl&)));

    d->search = new dtkSearchBar(this);
    d->search->setFixedWidth(200);

    connect(d->search, SIGNAL(textChanged(QString)), dtkHelpController::instance()->engine()->indexWidget(), SLOT(filterIndices(QString)));
    connect(d->search, SIGNAL(returnPressed()), dtkHelpController::instance()->engine()->indexWidget(), SLOT(activateCurrentItem()));

    QToolBar *toolbar = this->addToolBar("navigation");
    toolbar->addWidget(d->navigation);
    toolbar->addAction(d->registerAction);
    toolbar->addAction(d->unregisterAction);
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

    this->resize(800, 480);
}

dtkAssistantMainWindow::~dtkAssistantMainWindow(void)
{
    delete d;

    d = NULL;
}

void dtkAssistantMainWindow::onRegisterClicked(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Help Collection File", qApp->applicationDirPath(), "Help collection file (*.qch)");
    
    if(!fileName.isNull())
        dtkHelpController::instance()->registerDocumentation(fileName);
}

void dtkAssistantMainWindow::onUnregisterClicked(void)
{
    bool ok;

    QStringList items = dtkHelpController::instance()->registeredNamespaces();
    items.removeFirst();

    QString namespaceName = QInputDialog::getItem(
        this,
        "dtkAssistant",
        "Choose the documentation namespace to unregister",
        items,
        0,
        false,
        &ok);
    
    if (ok)
        dtkHelpController::instance()->unregisterDocumentation(namespaceName);
}

void dtkAssistantMainWindow::onUrlChanged(const QUrl& url)
{
    d->address->setText(url.toString());
}

void dtkAssistantMainWindow::onLinksActivated(const QMap<QString, QUrl>& urls, const QString& keyword)
{
    bool ok;
    
    QString key = QInputDialog::getItem(
        this,
        "dtkAssistant",
        QString("Choose a topic for %1").arg(keyword),
        urls.keys(),
        0,
        false,
        &ok);
    
    if (ok)
        d->browser->setSource(urls.value(key));
}
