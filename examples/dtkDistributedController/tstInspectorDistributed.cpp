/* tstInspectorDistributed.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:17:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 14:00:23 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 153
 */

/* Cosmmentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstInspectorDistributed.h"

#include <dtkGui/dtkInspectorBox.h>

#include <dtkDistributed/dtkDistributedControllerViewFiltering.h>
#include <dtkDistributed/dtkDistributedControllerViewOverall.h>
#include <dtkDistributed/dtkDistributedControllerViewDetailed.h>

#include <QtGui>

class tstInspectorDistributedPrivate
{
public:
    dtkDistributedControllerViewFiltering *view_filtering;
    dtkDistributedControllerViewOverall *view_overall;
    dtkDistributedControllerViewDetailed *view_detailed;

public:
    dtkInspectorBox *box_connection;
    dtkInspectorBox *box_filtering;
    dtkInspectorBox *box_overall;
    dtkInspectorBox *box_detailed;

    QPushButton *box_connection_connect;

    QLineEdit *box_connection_address;

    QHBoxLayout *box_connection_layout;
    QVBoxLayout *box_filtering_layout;
    QVBoxLayout *box_overall_layout;
    QVBoxLayout *box_detailed_layout;
};

tstInspectorDistributed::tstInspectorDistributed(QWidget *parent) : QFrame(parent), d(new tstInspectorDistributedPrivate)
{
    d->view_filtering = new dtkDistributedControllerViewFiltering(this);
    d->view_overall = new dtkDistributedControllerViewOverall(this);
    d->view_detailed = new dtkDistributedControllerViewDetailed(this);

    d->box_connection = new dtkInspectorBox(this);
    d->box_filtering = new dtkInspectorBox(this);
    d->box_overall = new dtkInspectorBox(this);
    d->box_detailed = new dtkInspectorBox(this);

    d->box_connection_connect = new QPushButton("Connect", d->box_connection);

    d->box_connection_layout = new QHBoxLayout(d->box_connection);
    d->box_filtering_layout = new QVBoxLayout(d->box_filtering);
    d->box_overall_layout = new QVBoxLayout(d->box_overall);
    d->box_detailed_layout = new QVBoxLayout(d->box_detailed);

    d->box_connection_address = new QLineEdit(d->box_connection);
    d->box_connection_address->setText("dtk://nef-devel.inria.fr:9999");

    d->box_connection_layout->addWidget(d->box_connection_address);
    d->box_connection_layout->addSpacing(10);
    d->box_connection_layout->addWidget(d->box_connection_connect);

    d->box_filtering_layout->addWidget(d->view_filtering);
    d->box_overall_layout->addWidget(d->view_overall);
    d->box_detailed_layout->addWidget(d->view_detailed);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->box_connection);
    layout->addWidget(d->box_filtering);
    layout->addWidget(d->box_overall);
    layout->addWidget(d->box_detailed);

    QObject::connect(d->box_connection_connect, SIGNAL(clicked()), this, SLOT(onConnect()));
}

tstInspectorDistributed::~tstInspectorDistributed(void)
{
    delete d;

    d = NULL;
}

void tstInspectorDistributed::onConnect(void)
{
    emit connect(QUrl(d->box_connection_address->text()));
}

void tstInspectorDistributed::onConnected(const QUrl& server)
{
    Q_UNUSED(server);

    d->box_connection_address->setStyleSheet("background: green;");
    d->box_connection_connect->setText("Disconnect");
    
    QObject::disconnect(d->box_connection_connect, SIGNAL(clicked()), this, SLOT(onConnect()));
       QObject::connect(d->box_connection_connect, SIGNAL(clicked()), this, SLOT(onDisconnect()));
}

void tstInspectorDistributed::onDisconnect(void)
{
    emit disconnect(QUrl(d->box_connection_address->text()));
}

void tstInspectorDistributed::onDisconnected(const QUrl& server)
{
    Q_UNUSED(server);

    d->box_connection_address->setStyleSheet("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #5d5d5d, stop: 1 #4a4a4a);");
    d->box_connection_connect->setText("Connect");
    
    QObject::disconnect(d->box_connection_connect, SIGNAL(clicked()), this, SLOT(onDisconnect()));
       QObject::connect(d->box_connection_connect, SIGNAL(clicked()), this, SLOT(onConnect()));
}
