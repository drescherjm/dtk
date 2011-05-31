/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:12:47 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 14:54:11 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 192
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

#include <dtkGui/dtkAnchoredBar.h>
#include <dtkGui/dtkSpacer.h>

#include <dtkDistributed/dtkDistributedController.h>
#include <dtkDistributed/dtkDistributedControllerViewFiltering.h>
#include <dtkDistributed/dtkDistributedControllerViewOverall.h>
#include <dtkDistributed/dtkDistributedControllerViewDetailed.h>

// /////////////////////////////////////////////////////////////////
// tstMainWindowPrivate
// /////////////////////////////////////////////////////////////////

class tstMainWindowPrivate
{
public:
    dtkDistributedController *controller;
    dtkDistributedControllerViewFiltering *view_filtering;
    dtkDistributedControllerViewOverall *view_overall;
    dtkDistributedControllerViewDetailed *view_detailed;

public:
    QLineEdit *host_address;
    QPushButton *host_button;
};

// /////////////////////////////////////////////////////////////////
// tstMainWindow
// /////////////////////////////////////////////////////////////////

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->controller = new dtkDistributedController;

    // d->view_filtering = new dtkDistributedControllerViewFiltering(this);
    // d->view_filtering->setController(d->controller);

    d->view_overall = new dtkDistributedControllerViewOverall(this);
    d->view_overall->setController(d->controller);

    d->view_detailed = new dtkDistributedControllerViewDetailed(this);
    d->view_detailed->setController(d->controller);

    dtkAnchoredBar *anchoredBar = new dtkAnchoredBar(d->view_overall);
    anchoredBar->setMinimumWidth(200);
    anchoredBar->setMaximumWidth(400);

    d->host_address = new QLineEdit("dtk://nef-devel.inria.fr:9999", anchoredBar);
    d->host_address->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->host_address->setFixedHeight(16);
    d->host_address->setStyleSheet("border: 1px solid darkGray; border-radius: 8px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #cccccc); color: black; font-size: 10px;");

    d->host_button = new QPushButton("Connect", anchoredBar);
    d->host_button->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->host_button->setFixedHeight(16);
    d->host_button->setStyleSheet("border: 1px solid darkGray; border-radius: 8px; background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff, stop: 1 #cccccc); color: black; font-size: 10px;");

    anchoredBar->addWidget(d->host_address);
    anchoredBar->addWidget(d->host_button);
    anchoredBar->addWidget(new dtkSpacer(anchoredBar, 16));

    QWidget *side = new QWidget(this);

    QVBoxLayout *side_layout = new QVBoxLayout(side);
    side_layout->setContentsMargins(0, 0, 0, 0);
    side_layout->setSpacing(0);
    side_layout->addWidget(d->view_overall);
    side_layout->addWidget(anchoredBar);

    QWidget *central = new QWidget(this);

    QHBoxLayout *layout = new QHBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(side);
    layout->addWidget(d->view_detailed);

    this->setCentralWidget(central);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle("dtkDistributedController");

    connect(d->host_button, SIGNAL(clicked()), this, SLOT(onConnect()));
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
