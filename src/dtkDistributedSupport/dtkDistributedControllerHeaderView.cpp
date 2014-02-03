/* dtkDistributedControllerHeaderView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 16:11:57 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 258
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerHeaderView.h"
#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedNode.h"

#include <dtkGuiSupport/dtkPieChart.h>

class dtkDistributedControllerHeaderViewPrivate
{
public:
    QLabel *server;
    QLabel *stats;
    dtkPieChart *pie_jobs;
    dtkPieChart *pie_cores;

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

    d->pie_jobs  = new dtkPieChart(this);
    d->pie_cores = new dtkPieChart(this);
    d->pie_jobs->setStyleSheet("font-size: 9px;");
    d->pie_cores->setStyleSheet("font-size: 9px;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(d->server);
    QHBoxLayout *layout_pies = new QHBoxLayout;
    layout_pies->addWidget(d->stats);
    layout_pies->addWidget(d->pie_jobs);
    layout_pies->addWidget(d->pie_cores);
    layout->addLayout(layout_pies);
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
    d->pie_jobs->clear();
    d->pie_cores->clear();

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
    int cores_free =0;
    int cores_busy =0;
    int cores_down =0;
    foreach (dtkDistributedNode *node, d->controller->nodes(d->cluster)) {
        foreach (dtkDistributedCpu *cpu, node->cpus()) {
            foreach (dtkDistributedCore *core, cpu->cores()) {
                if (node->state() == dtkDistributedNode::Down ||node->state() == dtkDistributedNode::Absent)
                    cores_down += 1;
                else if(core->job())
                    cores_busy += 1;
                else
                    cores_free += 1;
            }
        }
        total++;
        if (node->state() == dtkDistributedNode::Free)
            nfree++;
        else if (node->state() == dtkDistributedNode::Busy)
            nbusy++;
        else if (node->state() == dtkDistributedNode::StandBy)
            nstandby++;
        else if (node->state() == dtkDistributedNode::Down)
            ndown++;
        else if (node->state() == dtkDistributedNode::Absent)
            nabsent++;
    }
    int ncores = cores_free+cores_busy+cores_down;
    d->stats->setText(QString("Nodes: \t%1\nCores: \t%2\nJobs: \t%3")
                      .arg(total)
                      .arg(ncores)
                      .arg(d->controller->jobs(d->cluster).count()));

    if (total > 0) {
        d->pie_jobs->clear();
        d->pie_cores->clear();
        d->pie_jobs->addPiece(QString::number(nfree),   100*nfree/total,   Qt::darkGreen);
        d->pie_jobs->addPiece(QString::number(ndown),   100*ndown/total,   Qt::red);
        d->pie_jobs->addPiece(QString::number(nstandby),100*nstandby/total,Qt::blue);
        d->pie_jobs->addPiece(QString::number(nbusy),   100*nbusy/total,   QColor("#FF7722"));
        d->pie_jobs->addPiece(QString::number(nabsent), 100*nabsent/total, Qt::black);
        d->pie_cores->addPiece(QString::number(cores_free), 100*cores_free/ncores, Qt::darkGreen);
        d->pie_cores->addPiece(QString::number(cores_busy), 100*cores_busy/ncores, QColor("#FF7722"));
        d->pie_cores->addPiece(QString::number(cores_down), 100*cores_down/ncores, Qt::red);

        d->pie_jobs->setToolTip("free nodes: " + QString::number(nfree));
        d->pie_cores->setToolTip("free cores: " + QString::number(cores_free));
    }
    QFrame::update();
}
