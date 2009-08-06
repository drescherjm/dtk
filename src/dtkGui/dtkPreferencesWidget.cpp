/* dtkPreferencesWidget.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 10:01:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 10:57:55 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 77
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPreferencesWidget.h"

class dtkPreferencesWidgetPrivate
{
public:
    QHash<QAction *, QWidget *> pages;
    QStackedWidget *stack;
    QToolBar *toolBar;
};

dtkPreferencesWidget::dtkPreferencesWidget(QWidget *parent) : QMainWindow(parent), d(new dtkPreferencesWidgetPrivate)
{
    d->stack = new QStackedWidget(this);

    d->toolBar = this->addToolBar("Pages");
    d->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    d->toolBar->setIconSize(QSize(32, 32));
    d->toolBar->setFloatable(false);
    d->toolBar->setMovable(false);

    this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    this->setWindowTitle("Preferences");
    this->setCentralWidget(d->stack);
}

dtkPreferencesWidget::~dtkPreferencesWidget(void)
{
    delete d->stack;
    delete d->toolBar;
    delete d;

    d = NULL;
}

void dtkPreferencesWidget::addPage(const QString& title, dtkPreferencesPage *page)
{
    QAction *action = new QAction(title, this);
    action->setIcon(QIcon(":icons/widget.tiff"));
    action->setToolTip(QString("Switch to %1 preferences page").arg(title));

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->toolBar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));

    connect(page, SIGNAL(accepted()), this, SLOT(close()));
    connect(page, SIGNAL(rejected()), this, SLOT(close()));
}

void dtkPreferencesWidget::addPage(const QString& title, dtkPreferencesPage *page, const QIcon& icon)
{
    QAction *action = new QAction(title, this);
    action->setIcon(icon);
    action->setToolTip(QString("Switch to %1 preferences page").arg(title));

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->toolBar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));

    connect(page, SIGNAL(accepted()), this, SLOT(close()));
    connect(page, SIGNAL(rejected()), this, SLOT(close()));
}

void dtkPreferencesWidget::showEvent(QShowEvent *event)
{
    if(!d->stack->currentWidget()->isVisible())
        d->stack->currentWidget()->setVisible(true);

    if(d->pages.count())
        d->pages.keys().first()->trigger();

    QMainWindow::showEvent(event);
}

void dtkPreferencesWidget::onActionTriggered(void)
{
    QAction *sender = qobject_cast<QAction *>(this->sender());

    foreach(QAction *action, d->pages.keys())
        action == sender ? action->setEnabled(false) : action->setEnabled(true);

    d->stack->setCurrentWidget(d->pages.value(sender));
}
