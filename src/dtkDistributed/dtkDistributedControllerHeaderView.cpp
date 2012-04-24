/* dtkDistributedControllerHeaderView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. avril 24 17:15:05 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 178
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerHeaderView.h"
#include "dtkDistributedNode.h"

#include <dtkGui/dtkPieChart.h>

class dtkDistributedControllerHeaderViewPrivate
{
public:
    QLabel *server;
    QLabel *stats;
    dtkPieChart *pie;

public:
    QString cluster;

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

    d->pie = new dtkPieChart(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->server);
    layout->addWidget(d->stats);
    layout->addWidget(d->pie);
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
    connect(d->controller, SIGNAL(disconnected(const QUrl&)), this, SLOT(onDisconnected(const QUrl&)));
}

void dtkDistributedControllerHeaderView::setCluster(const QString& cluster)
{
    d->cluster = cluster;

    this->update();
}

void dtkDistributedControllerHeaderView::onStatus(const QUrl& cluster)
{
    d->cluster = cluster.toString();

    this->update();
}

void dtkDistributedControllerHeaderView::onDisconnected(const QUrl& cluster)
{
    d->server->clear();
    d->stats->clear();
    d->pie->clear();

    d->cluster = QString();
}

void dtkDistributedControllerHeaderView::update(void)
{
    d->server->setText(QUrl(d->cluster).host());
    int nfree   =0;
    int nbusy   =0;
    int ndown   =0;
    int nstandby=0;
    int nabsent =0;
    int total   =0;
    foreach (dtkDistributedNode * node, d->controller->nodes(d->cluster)) {
        total++;
        if (node->state() == dtkDistributedNode::Free)
            nfree++;
        else if (node->state() == dtkDistributedNode::Busy)
            nbusy++;
        else if (node->state() == dtkDistributedNode::Down)
            ndown++;
        else if (node->state() == dtkDistributedNode::StandBy)
            nstandby++;
        else if (node->state() == dtkDistributedNode::Absent)
            nabsent++;
    }
    d->stats->setText(QString("Nodes: %1\nJobs: %2")
                      .arg(total)
                      .arg(d->controller->jobs(d->cluster).count()));

    if (total > 0) {
        d->pie->clear();
        d->pie->addPiece("free: "   +QString::number(nfree),   100*nfree/total,   Qt::darkGreen);
        d->pie->addPiece("dead: "   +QString::number(ndown),   100*ndown/total,   Qt::red);
        d->pie->addPiece("standby: "+QString::number(nstandby),100*nstandby/total,Qt::blue);
        d->pie->addPiece("busy: "   +QString::number(nbusy),   100*nbusy/total,   QColor("#FF7722"));
        d->pie->addPiece("absent: " +QString::number(nabsent), 100*nabsent/total, Qt::black);
    }
    QFrame::update();
}
