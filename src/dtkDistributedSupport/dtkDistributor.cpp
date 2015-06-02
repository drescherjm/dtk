/* dtkDistributor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:35:49 2012 (+0200)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 16:38:23 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 184
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerFilterView.h"
#include "dtkDistributedControllerHeaderView.h"
#include "dtkDistributedControllerJobView.h"
#include "dtkDistributedControllerStatusModel.h"
#include "dtkDistributedControllerStatusModelFilter.h"
#include "dtkDistributedControllerStatusView.h"
#include "dtkDistributedControllerSubmitView.h"
#include "dtkDistributedControllerTargetView.h"
#include "dtkDistributor.h"

#include <dtkWidgets/dtkToolBox.h>

class dtkDistributorPrivate
{
public:
    dtkDistributedController *controller;
    dtkDistributedControllerStatusModel *status_model;
    dtkDistributedControllerStatusModelFilter *filter_model;
    dtkDistributedControllerFilterView *filter_view;
    dtkDistributedControllerHeaderView *header_view;
    dtkDistributedControllerStatusView *status_view;
    dtkDistributedControllerSubmitView *submit_view;
    dtkDistributedControllerTargetView *target_view;
    dtkDistributedControllerJobView *job_view;

public:
    QComboBox *host_address;
    QPushButton *host_button;
};

dtkDistributor::dtkDistributor(QWidget *parent) : QFrame(parent), d(new dtkDistributorPrivate)
{
    d->host_address = new QComboBox(this);

    d->controller = dtkDistributedController::instance();
    QString port = QString::number(d->controller->defaultPort());

    d->host_address->addItem("dtk://<host>[:port]");
    d->host_address->addItem("dtk://nef-devel.inria.fr:"+port);
    d->host_address->addItem("dtk://fsophia.sophia.grid5000.fr:"+port);
    d->host_address->addItem("dtk://is-master.inria.fr:"+port);
    d->host_address->addItem("dtk://localhost:"+port);
    d->host_address->setEditable(true);
    d->host_address->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->host_button = new QPushButton("Connect", this);
    d->host_button->setAttribute(Qt::WA_MacShowFocusRect, false);


    d->status_model = new dtkDistributedControllerStatusModel(this);
    d->status_model->setController(d->controller);

    d->filter_model = new dtkDistributedControllerStatusModelFilter(this);
    d->filter_model->setSourceModel(d->status_model);

    d->status_view = new dtkDistributedControllerStatusView(this);
    d->status_view->setModel(d->filter_model);

    d->filter_view = new dtkDistributedControllerFilterView(this);

    d->submit_view = new dtkDistributedControllerSubmitView(this);
    d->submit_view->setController(d->controller);

    d->header_view = new dtkDistributedControllerHeaderView(this);
    d->header_view->setController(d->controller);

    d->target_view = new dtkDistributedControllerTargetView(this);
    d->target_view->setController(d->controller);

    d->job_view = new dtkDistributedControllerJobView(this);
    d->job_view->setController(d->controller);

    QHBoxLayout *t_layout = new QHBoxLayout;
    t_layout->setContentsMargins(5, 5, 5, 5);
    t_layout->addWidget(d->host_address);
    t_layout->addWidget(d->host_button);

    QFrame *top = new QFrame(this);
    top->setObjectName("dtkDistributorHeader");
    top->setLayout(t_layout);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(top);

    dtkToolBox *toolbox = new dtkToolBox(this);
    dtkToolBoxItem *item;

    layout->addWidget(toolbox);

    item = new dtkToolBoxItem(toolbox);
    item->setWidget(d->target_view,"Clusters");
    item->setExpanded(true);
    toolbox->addItem(item);

    item = new dtkToolBoxItem(toolbox);
    item->setWidget(d->header_view,"Cluster load");
    item->setExpanded(true);
    toolbox->addItem(item);

    item = new dtkToolBoxItem(toolbox);
    item->setWidget(d->status_view,"Nodes");
    toolbox->addItem(item);

    item = new dtkToolBoxItem(toolbox);
    item->setWidget(d->job_view,"Jobs");
    toolbox->addItem(item);

    item = new dtkToolBoxItem(toolbox);
    item->setWidget(d->filter_view,"Filter");
    toolbox->addItem(item);

    item = new dtkToolBoxItem(toolbox);
    item->setWidget(d->submit_view,"Submit");
    item->setExpanded(true);
    toolbox->addItem(item);

    connect(d->host_address, SIGNAL(activated(int)), this, SLOT(onConnect()));
    connect(d->host_button, SIGNAL(clicked()), this, SLOT(onConnect()));
    connect(d->filter_view, SIGNAL(updated()), this, SLOT(onFilterUpdated()));
    connect(d->target_view, SIGNAL(selected(const QString&)), d->status_model, SLOT(setCluster(const QString&)));
    connect(d->target_view, SIGNAL(selected(const QString&)), d->header_view, SLOT(setCluster(const QString&)));
    connect(d->target_view, SIGNAL(selected(const QString&)), d->job_view, SLOT(setCluster(const QString&)));
    connect(d->target_view, SIGNAL(selected(const QString&)), d->submit_view, SLOT(setCluster(const QString&)));
}

dtkDistributor::~dtkDistributor(void)
{
    delete d;

    d = NULL;
}

void dtkDistributor::setApplication(const QString& application)
{
    d->submit_view->setApplication(application);
}
void dtkDistributor::onConnect(void)
{
    QUrl url = QUrl(d->host_address->currentText());
    if (!d->controller->connect(url)) {
        // can't connect, try to deploy:
        if (!d->controller->deploy(url)) {
            return;
        } else {
            dtkInfo() << "Server is now deployed, retry to connect";
            if (!d->controller->connect(url))
                return;
        }
    }

    d->header_view->setCluster(d->host_address->currentText());
    d->status_model->setCluster(d->host_address->currentText());
    d->submit_view->setCluster(d->host_address->currentText());
}

void dtkDistributor::onFilterUpdated(void)
{
    d->filter_model->setNetworkFlags(d->filter_view->networkFlags());
    d->filter_model->setStateFlags(d->filter_view->stateFlags());
    d->filter_model->setBrandFlags(d->filter_view->brandFlags());
    d->filter_model->setArchFlags(d->filter_view->archFlags());
    d->filter_model->setModelFlags(d->filter_view->modelFlags());
}
