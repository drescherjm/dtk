/* dtkInspector.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 23:28:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Aug  7 00:24:34 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 37
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspector.h"

#include <QtCore>
#include <QtGui>

class dtkInspectorPrivate
{
public:
    QHash<QAction *, QWidget *> pages;
    QToolBar *toolBar;
    QStackedWidget *stack;
};

dtkInspector::dtkInspector(QWidget *parent) : QMainWindow(parent), d(new dtkInspectorPrivate)
{
    d->stack = new QStackedWidget(this);

    d->toolBar = this->addToolBar("Pages");
    d->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    d->toolBar->setIconSize(QSize(16, 16));
    d->toolBar->setFloatable(false);
    d->toolBar->setMovable(false);

    QAction *action1 = new QAction("Test1", this);
    action1->setIcon(QIcon(":icons/widget.tiff"));
    action1->setToolTip(QString("Switch to %1 preferences page"));

    QAction *action2 = new QAction("Test2", this);
    action2->setIcon(QIcon(":icons/widget.tiff"));
    action2->setToolTip(QString("Switch to %1 preferences page"));

    connect(action1, SIGNAL(hovered()), this, SLOT(onActionHovered()));
    connect(action2, SIGNAL(hovered()), this, SLOT(onActionHovered()));

    d->toolBar->addAction(action1);
    d->toolBar->addAction(action2);

    this->setWindowFlags(Qt::Tool | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint);
    this->setWindowTitle("Inspector");
    this->setCentralWidget(d->stack);
}

dtkInspector::~dtkInspector(void)
{
    delete d->stack;
    delete d->toolBar;
    delete d;

    d = NULL;
}

void dtkInspector::addPage(const QString& title, QWidget *page)
{
    QAction *action = new QAction(title, this);
    action->setIcon(QIcon(":icons/widget.tiff"));
    action->setToolTip(QString("Switch to %1 inspector page.").arg(title));

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->toolBar->addAction(action);

    connect(action, SIGNAL(hovered()), this, SLOT(onActionHovered()));
    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));
}

void dtkInspector::addPage(const QString& title, QWidget *page, const QIcon& icon)
{
    QAction *action = new QAction(title, this);
    action->setIcon(icon);
    action->setToolTip(QString("Switch to %1 inspector page.").arg(title));

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->toolBar->addAction(action);

    connect(action, SIGNAL(hovered()), this, SLOT(onActionHovered()));
    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));
}

void dtkInspector::onActionHovered(void)
{
    QAction *sender = qobject_cast<QAction *>(this->sender());

    this->setWindowTitle(sender->text());
}

void dtkInspector::onActionTriggered(void)
{
    QAction *sender = qobject_cast<QAction *>(this->sender());

    foreach(QAction *action, d->pages.keys())
        action == sender ? action->setEnabled(false) : action->setEnabled(true);

    d->stack->setCurrentWidget(d->pages.value(sender));
}
