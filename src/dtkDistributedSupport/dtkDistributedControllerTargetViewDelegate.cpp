/* dtkDistributedControllerTargetViewDelegate.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 10:10:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. oct. 30 16:46:59 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 84
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerTargetViewDelegate.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerTargetViewDelegate
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerTargetViewDelegatePrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedControllerTargetViewDelegate::dtkDistributedControllerTargetViewDelegate(QWidget *parent) : QStyledItemDelegate(parent), d(new dtkDistributedControllerTargetViewDelegatePrivate)
{
    d->controller = NULL;
}

dtkDistributedControllerTargetViewDelegate::~dtkDistributedControllerTargetViewDelegate(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerTargetViewDelegate::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}

void dtkDistributedControllerTargetViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize dtkDistributedControllerTargetViewDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

QWidget *dtkDistributedControllerTargetViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    dtkDistributedControllerTargetViewEditor *editor = new dtkDistributedControllerTargetViewEditor(parent);
    editor->setController(d->controller);

    return editor;
}

void dtkDistributedControllerTargetViewDelegate::setEditorData(QWidget *widget, const QModelIndex& index) const
{
    dtkDistributedControllerTargetViewEditor *editor = qobject_cast<dtkDistributedControllerTargetViewEditor *>(widget);

    if (!editor)
        return;

    editor->setCluster(index.data().toString());
}

void dtkDistributedControllerTargetViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex& index) const
{
    Q_UNUSED(editor);
    Q_UNUSED(model);
    Q_UNUSED(index);
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerTargetViewEditor
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerTargetViewEditorPrivate
{
public:
    QPushButton *refresh;
    QPushButton *disconnect;
    QPushButton *stop;

public:
    QUrl cluster;

public:
    dtkDistributedController *controller;
};

dtkDistributedControllerTargetViewEditor::dtkDistributedControllerTargetViewEditor(QWidget *parent) : QWidget(parent), d(new dtkDistributedControllerTargetViewEditorPrivate)
{
    d->refresh    = new QPushButton("Refresh", this);
    d->disconnect = new QPushButton("Disconnect", this);
    d->stop       = new QPushButton("Stop", this);

    d->controller = NULL;

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addStretch(1);
    layout->addWidget(d->refresh);
    layout->addWidget(d->disconnect);
    layout->addWidget(d->stop);

    connect(d->refresh, SIGNAL(clicked()), this, SLOT(onRefresh()));
    connect(d->disconnect, SIGNAL(clicked()), this, SLOT(onDisconnect()));
    connect(d->stop, SIGNAL(clicked()), this, SLOT(onStop()));
}

dtkDistributedControllerTargetViewEditor::~dtkDistributedControllerTargetViewEditor(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerTargetViewEditor::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}

void dtkDistributedControllerTargetViewEditor::setCluster(QUrl cluster)
{
    d->cluster = cluster;
}

void dtkDistributedControllerTargetViewEditor::onRefresh(void)
{
    if (!d->controller)
        return;

    d->controller->refresh(d->cluster);
}

void dtkDistributedControllerTargetViewEditor::onDisconnect(void)
{
    if (!d->controller)
        return;

    d->controller->disconnect(d->cluster);
}

void dtkDistributedControllerTargetViewEditor::onStop(void)
{
    if (!d->controller)
        return;

    d->controller->stop(d->cluster);
}
