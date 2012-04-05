/* dtkDistributedControllerTargetView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 14:31:28 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerTargetView.h"

class dtkDistributedControllerTargetViewPrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedControllerTargetView::dtkDistributedControllerTargetView(QWidget *parent) : QListWidget(parent), d(new dtkDistributedControllerTargetViewPrivate)
{
    d->controller = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
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

    connect(d->controller, SIGNAL(connected(const QUrl&)), this, SLOT(onConnected(const QUrl&)));
}

void dtkDistributedControllerTargetView::onConnected(const QUrl& server)
{
    this->addItem(server.toString());
}
