/* dtkDistributedControllerSubmitView.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:53:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 16:16:36 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 109
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerSubmitView.h"

class dtkDistributedControllerSubmitViewPrivate
{
public:
    dtkDistributedController *controller;

public:
    QString cluster;
    QString application;

public:
    QSpinBox *node_spin;
    QSpinBox *ppn_spin;
    QDateTimeEdit *time_edit;
    QPushButton *submit_button;
};

dtkDistributedControllerSubmitView::dtkDistributedControllerSubmitView(QWidget *parent) : QFrame(parent), d(new dtkDistributedControllerSubmitViewPrivate)
{
    d->controller = NULL;

    d->application = "dtkComposerEvaluatorSlave";

    d->node_spin = new QSpinBox(this);
    d->node_spin->setMinimum(1);
    d->node_spin->setMaximum(500);
    d->node_spin->setSingleStep(1);
    d->node_spin->setValue(1);
    d->node_spin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    d->ppn_spin = new QSpinBox(this);
    d->ppn_spin->setMinimum(1);
    d->ppn_spin->setMaximum(500);
    d->ppn_spin->setSingleStep(1);
    d->ppn_spin->setValue(1);
    d->ppn_spin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    d->time_edit = new QDateTimeEdit(this);
    d->time_edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    d->time_edit->setDisplayFormat("hh:mm:ss");
    d->time_edit->setTime(QTime(0, 15, 0));

    d->submit_button = new QPushButton("Submit", this);

    QFormLayout *f_layout = new QFormLayout;
    f_layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    f_layout->addRow("Nodes", d->node_spin);
    f_layout->addRow("Process per node", d->ppn_spin);
    f_layout->addRow("Duration", d->time_edit);
    f_layout->addRow(d->submit_button);

    QLabel *header = new QLabel("Submission", this);
    header->setObjectName("dtkDistributedControllerSubmitViewHeader");

    QHBoxLayout *t_layout = new QHBoxLayout;
    t_layout->addWidget(header);

    QWidget *bottom = new QWidget(this);
    bottom->setLayout(f_layout);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(header);
    layout->addWidget(bottom);

    connect(d->submit_button, SIGNAL(clicked()), this, SLOT(onSubmit()));

    this->setEnabled(false);
}

dtkDistributedControllerSubmitView::~dtkDistributedControllerSubmitView(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerSubmitView::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}

void dtkDistributedControllerSubmitView::setCluster(const QString& cluster)
{
    d->cluster = cluster;

    this->setEnabled(true);
}

void dtkDistributedControllerSubmitView::setApplication(const QString& application)
{
    d->application = application;
}

void dtkDistributedControllerSubmitView::onSubmit(void)
{
    if (!d->controller)
        return;

    if (d->cluster.isEmpty())
        return;

    QVariantMap resources;
    resources.insert("cores", d->ppn_spin->text());
    resources.insert("nodes", d->node_spin->text());

    QVariantMap job;
    job.insert("resources", resources);
    job.insert("properties", QVariantMap());
    job.insert("walltime", d->time_edit->time().toString("hh:mm:ss"));
    job.insert("application", d->application + " " + d->cluster);

    QByteArray data = QJsonDocument(QJsonObject::fromVariantMap(job)).toJson();

    d->controller->submit(QUrl(d->cluster), data);
}
