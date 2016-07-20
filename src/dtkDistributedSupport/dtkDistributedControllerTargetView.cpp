/* dtkDistributedControllerTargetView.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  6 11:08:59 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 54
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerTargetView.h"
#include "dtkDistributedControllerTargetViewDelegate.h"

class dtkDistributedControllerTargetViewPrivate
{
public:
    dtkDistributedController *controller;

public:
    dtkDistributedControllerTargetViewDelegate *delegate;
};

dtkDistributedControllerTargetView::dtkDistributedControllerTargetView(QWidget *parent) : QListWidget(parent), d(new dtkDistributedControllerTargetViewPrivate)
{
    d->controller = NULL;
    d->delegate = new dtkDistributedControllerTargetViewDelegate(this);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    this->setItemDelegate(d->delegate);

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));
}

dtkDistributedControllerTargetView::~dtkDistributedControllerTargetView(void)
{
    delete d;

    d = NULL;
}

QSize dtkDistributedControllerTargetView::sizeHint(void) const
{
    return QSize(100, 100);
}

void dtkDistributedControllerTargetView::setController(dtkDistributedController *controller)
{
    d->controller = controller;
    d->delegate->setController(d->controller);

    connect(d->controller, SIGNAL(connected(const QUrl&)), this, SLOT(onConnected(const QUrl&)));
    connect(d->controller, SIGNAL(disconnected(const QUrl&)), this, SLOT(onDisconnected(const QUrl&)));
}

void dtkDistributedControllerTargetView::onConnected(const QUrl& server)
{
    QListWidgetItem *item = new QListWidgetItem(server.toString(), this);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);

    this->addItem(item);
    this->openPersistentEditor(item);
}

void dtkDistributedControllerTargetView::onDisconnected(const QUrl& server)
{
    QList<QListWidgetItem *> items = this->findItems(server.toString(), Qt::MatchExactly);

    foreach (QListWidgetItem *item, items) {
        this->closePersistentEditor(item);
        delete this->takeItem(this->row(item));
    }
}

void dtkDistributedControllerTargetView::onItemClicked(QListWidgetItem *item)
{
    emit selected(item->text());
}
