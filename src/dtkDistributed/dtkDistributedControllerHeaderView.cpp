/* dtkDistributedControllerHeaderView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 10:28:02 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 59
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
    d->server->setStyleSheet("font-size: 13px; font-weight: bold;");

    d->stats = new QLabel(this);
    d->stats->setStyleSheet("font-size: 10px;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->server);
    layout->addWidget(d->stats);

    this->setStyleSheet(
        "dtkDistributedControllerHeaderView { background: qlineargradient(x1: 0, y1: 1, stop: 0 #bcc3d7, stop: 1 #a2abc7); border-top: 1px solid #6a6a6a; border-bottom: 1px solid #b6b6b6; }"
        "QLabel { color: white; }");
}

dtkDistributedControllerHeaderView::~dtkDistributedControllerHeaderView(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerHeaderView::setController(dtkDistributedController *controller)
{
    d->controller = controller;

    connect(d->controller, SIGNAL(status(const QUrl&)), this, SLOT(onStatus(const QUrl&)));
}

void dtkDistributedControllerHeaderView::onStatus(const QUrl& server)
{
    d->server->setText(server.host());
    
    d->stats->setText(QString("Nodes: %1\nJobs: %2")
                      .arg(d->controller->nodes(server.toString()).count())
                      .arg(d->controller->jobs(server.toString()).count()));
}
