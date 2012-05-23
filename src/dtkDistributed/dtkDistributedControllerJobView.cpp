/* dtkDistributedControllerJobView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 11 17:02:06 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 13:43:28 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 91
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerJobView.h"
#include "dtkDistributedJob.h"
#include "dtkDistributedMimeData.h"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

QString toString(dtkDistributedJob::State state)
{
    switch(state) {
    case dtkDistributedJob::Running: return "Running"; break;
    case dtkDistributedJob::Queued: return "Queued"; break;
    case dtkDistributedJob::Suspended: return "Suspended"; break;
    case dtkDistributedJob::Blocked: return "Blocked"; break;
    case dtkDistributedJob::Ending: return "Ending"; break;
    case dtkDistributedJob::Scheduled: return "Scheduled"; break;
    case dtkDistributedJob::EndedOK: return "EndedOk"; break;
    case dtkDistributedJob::EndedError: return "EndedError"; break;
    default:
        return QString();
    };
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerJobViewPrivate
{
public:
    dtkDistributedController *controller;

public:
    QString cluster;
};

dtkDistributedControllerJobView::dtkDistributedControllerJobView(QWidget *parent) : QTreeWidget(parent), d(new dtkDistributedControllerJobViewPrivate)
{
    d->controller = NULL;

    this->setHeaderLabels(QStringList() << "Job" << "State" << "User" << "Queue" << "Queued" << "Started" << "Duration" << "Name" << "Script" << "Resources");

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setDragEnabled(true);
}

dtkDistributedControllerJobView::~dtkDistributedControllerJobView(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerJobView::setController(dtkDistributedController *controller)
{
    d->controller = controller;

    connect(d->controller, SIGNAL(updated(const QUrl&)), this, SLOT(onStatus(const QUrl&)));
    connect(d->controller, SIGNAL(status(const QUrl&)), this, SLOT(onStatus(const QUrl&)));
    connect(d->controller, SIGNAL(disconnected(const QUrl&)), this, SLOT(onDisconnected(const QUrl&)));
}

void dtkDistributedControllerJobView::setCluster(const QString& cluster)
{
    d->cluster = cluster;

    this->update();
}

void dtkDistributedControllerJobView::onStatus(const QUrl& cluster)
{
    d->cluster = cluster.toString();

    this->update();
}

void dtkDistributedControllerJobView::onDisconnected(const QUrl& cluster)
{
    d->cluster = QString();

    this->update();
}

void dtkDistributedControllerJobView::update(void)
{
    this->clear();

    foreach(dtkDistributedJob *job, d->controller->jobs(d->cluster))
        this->addTopLevelItem(new QTreeWidgetItem(this, QStringList() << job->Id() << toString(job->state()) << job->Username() << job->Queue() << job->Qtime().toString() << job->Stime().toString() << job->Walltime() << job->Name() << job->Script() << job->Resources()));

    QTreeWidget::update();
}

QMimeData *dtkDistributedControllerJobView::mimeData(const QList<QTreeWidgetItem *> items) const
{
    dtkDistributedMimeData *data = new dtkDistributedMimeData;
    data->setText(items.first()->text(0));
    data->setController(d->controller);
    
    return data;
}

QStringList dtkDistributedControllerJobView::mimeTypes(void) const
{
    return QStringList() << "text/plain";
}
