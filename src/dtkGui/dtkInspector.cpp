/* dtkInspector.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 23:28:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sun Mar 14 15:04:37 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 88
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

    this->setWindowFlags(Qt::Tool | Qt::WindowCloseButtonHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(0.8);
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

void dtkInspector::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("inspector");
    QPoint pos = settings.value("pos", QPoint(800, 150)).toPoint();
    QSize size = settings.value("size", QSize(100, 250)).toSize();
    bool visible = settings.value("visible", false).toBool();
    move(pos);
    resize(size);
    setVisible(visible);
    settings.endGroup();
}

void dtkInspector::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("inspector");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("visible", isVisible());
    settings.endGroup();
}

QAction *dtkInspector::addPage(const QString& title, QWidget *page)
{
    QAction *action = new QAction(title, this);
    action->setIcon(QIcon(":icons/widget.tiff"));
    action->setToolTip(QString("Switch to %1 inspector page.").arg(title));

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->toolBar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));

    if (d->stack->count() == 1)
        action->trigger();

    return action;
}

QAction *dtkInspector::addPage(const QString& title, QWidget *page, const QIcon& icon)
{
    QAction *action = new QAction(title, this);
    action->setIcon(icon);
    action->setToolTip(QString("Switch to %1 inspector page.").arg(title));
    action->setEnabled(d->stack->count());

    d->pages.insert(action, page);
    d->stack->addWidget(page);
    d->toolBar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(onActionTriggered()));

    if (d->stack->count() == 1)
        action->trigger();

    return action;
}

void dtkInspector::onActionTriggered(void)
{
    QAction *sender = qobject_cast<QAction *>(this->sender());

    foreach(QAction *action, d->pages.keys())
        action == sender ? action->setEnabled(false) : action->setEnabled(true);

    d->stack->setCurrentWidget(d->pages.value(sender));

    this->setWindowTitle("Inspector - " + sender->text());
}
