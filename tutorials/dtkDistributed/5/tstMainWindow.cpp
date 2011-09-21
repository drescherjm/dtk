/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep 20 11:31:26 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. sept. 21 12:48:10 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 88
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedControllerStatusModel.h>
#include <dtkDistributed/dtkDistributedControllerStatusView.h>

#include <dtkJson/dtkJson.h>

// /////////////////////////////////////////////////////////////////
// tstMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    dtkDistributedController *controller;
    dtkDistributedControllerStatusModel *status_model;
    dtkDistributedControllerStatusView *status_view;

public:
    QLineEdit *host_address;
    QPushButton *host_button;

    QSpinBox *submit_nodes;
    QSpinBox *submit_cores;
    QSpinBox *submit_value;
    QPushButton *submit_button;
};

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->controller = new dtkDistributedController;

    d->status_model = new dtkDistributedControllerStatusModel(this);
    d->status_model->setController(d->controller);

    d->status_view = new dtkDistributedControllerStatusView(this);
    d->status_view->setModel(d->status_model);

    d->host_address = new QLineEdit("dtk://nef-devel.inria.fr:9999", this);
    d->host_address->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->host_button = new QPushButton("Connect", this);
    d->host_button->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->host_button->setFixedWidth(200);

    d->submit_nodes = new QSpinBox(this);
    d->submit_nodes->setMaximum(100);
    d->submit_nodes->setValue(2);

    d->submit_cores = new QSpinBox(this);
    d->submit_cores->setMaximum(48);
    d->submit_cores->setValue(8);

    d->submit_value = new QSpinBox(this);
    d->submit_value->setMaximum(100000);
    d->submit_value->setValue(100000);

    d->submit_button = new QPushButton("Submit", this);
    d->submit_button->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->submit_button->setFixedWidth(200);

    QHBoxLayout *host_layout = new QHBoxLayout;
    host_layout->addWidget(d->host_address);
    host_layout->addWidget(d->host_button);

    QHBoxLayout *submit_layout = new QHBoxLayout;
    submit_layout->addWidget(d->submit_nodes);
    submit_layout->addWidget(d->submit_cores);
    submit_layout->addWidget(d->submit_value);
    submit_layout->addWidget(d->submit_button);

    QWidget *host_widget = new QWidget(this);
    host_widget->setLayout(host_layout);

    QWidget *submit_widget = new QWidget(this);
    submit_widget->setLayout(submit_layout);

    QWidget *central = new QWidget(this);

    QVBoxLayout *central_layout = new QVBoxLayout(central);
    central_layout->setContentsMargins(0, 0, 0, 0);
    central_layout->setSpacing(0);
    central_layout->addWidget(host_widget);
    central_layout->addWidget(d->status_view);
    central_layout->addWidget(submit_widget);

    this->setCentralWidget(central);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkDistributedTutorial - Step #5");

    connect(d->host_button, SIGNAL(clicked()), this, SLOT(onConnect()));
    connect(d->submit_button, SIGNAL(clicked()), this, SLOT(onSubmit()));
}

tstMainWindow::~tstMainWindow(void)
{
    delete d->controller;
    delete d;
}

void tstMainWindow::onConnect(void)
{
    d->controller->connect(QUrl(d->host_address->text()));
}

void tstMainWindow::onSubmit(void)
{
    QVariantMap job;
    QVariantMap resources;
    resources.insert("cores", d->submit_cores->text());
    resources.insert("nodes", d->submit_nodes->text());
    job.insert("resources", resources);
    job.insert("walltime", "00:15:00");
    job.insert("application", "dtkDistributedTutorial4Slave "
               + d->submit_value->text()
               + " --server " + d->host_address->text());
    QByteArray data = dtkJson::serialize(job);
    d->controller->submit(QUrl(d->host_address->text()),data);
}

void tstMainWindow::onConnected(const QUrl& server)
{
    Q_UNUSED(server);

    d->host_button->setText("Disconnect");
    
    QObject::disconnect(d->host_button, SIGNAL(clicked()), this, SLOT(onConnect()));
       QObject::connect(d->host_button, SIGNAL(clicked()), this, SLOT(onDisconnect()));
}

void tstMainWindow::onDisconnect(void)
{
    d->controller->disconnect(QUrl(d->host_address->text()));
}

void tstMainWindow::onDisconnected(const QUrl& server)
{
    Q_UNUSED(server);

    d->host_button->setText("Connect");
    
    QObject::disconnect(d->host_button, SIGNAL(clicked()), this, SLOT(onDisconnect()));
       QObject::connect(d->host_button, SIGNAL(clicked()), this, SLOT(onConnect()));
}
