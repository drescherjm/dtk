/* dtkDistributedControllerHeaderView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 16:13:45 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerHeaderView.h"

class dtkDistributedControllerHeaderViewPrivate
{
public:
    QLabel *server;
    QLabel *stats;

public:
    dtkDistributedController *controller;
};

dtkDistributedControllerHeaderView::dtkDistributedControllerHeaderView(QWidget *parent) : QFrame(parent), d(new dtkDistributedControllerHeaderViewPrivate)
{
    d->controller = NULL;

    d->server = new QLabel(this);
    d->server->setStyleSheet("font-size: 13px;");

    d->stats = new QLabel(this);
    d->stats->setStyleSheet("font-size: 10px;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->server);
    layout->addWidget(d->stats);
}

dtkDistributedControllerHeaderView::~dtkDistributedControllerHeaderView(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerHeaderView::setController(dtkDistributedController *controller)
{
    d->controller = controller;

    connect(d->controller, SIGNAL(connected(const QUrl&)), this, SLOT(onConnected(const QUrl&)));
}

void dtkDistributedControllerHeaderView::onConnected(const QUrl& server)
{
    d->server->setText(server.host());

    d->stats->setText(QString("Nodes: %1\nJobs: -1").arg(d->controller->nodes().count()));
}
