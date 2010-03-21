/* dtkDistributor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 19:02:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 23:09:11 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 83
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedDiscoverer.h"
#include "dtkDistributedDiscovererOar.h"
#include "dtkDistributedDiscovererTorque.h"
#include "dtkDistributor.h"
#include "dtkDistributorScene.h"
#include "dtkDistributorView.h"

class dtkDistributorPrivate
{
public:
    dtkDistributedDiscoverer *discoverer;
    dtkDistributorButton *connectButton;
    dtkDistributorButton *disconnectButton;
    dtkDistributorLabel *connectLabel;
    dtkDistributorScene *scene;
    dtkDistributorView *view;

    QStateMachine *machine;
    QState *s1;
    QState *s2;
};

dtkDistributor::dtkDistributor(QWidget *parent) : QWidget(parent), d(new dtkDistributorPrivate)
{
    d->discoverer = new dtkDistributedDiscovererTorque;

    d->connectLabel = new dtkDistributorLabel;
    d->connectLabel->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-connect-label.png"));
    d->connectLabel->setPos(0, -45);

    d->connectButton = new dtkDistributorButton;
    d->connectButton->setPixmapNormal(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-connect-button.png"));
    d->connectButton->setPixmapPressed(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-connect-button-pressed.png"));
    d->connectButton->setPos(0, 45);
    d->connectButton->setOpacity(1);

    d->disconnectButton = new dtkDistributorButton;
    d->disconnectButton->setPixmapNormal(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-disconnect-button.png"));
    d->disconnectButton->setPixmapPressed(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-disconnect-button-pressed.png"));
    d->disconnectButton->setPos(-300, -210);
    d->disconnectButton->setOpacity(0);

    d->scene = new dtkDistributorScene;
    d->scene->addItem(d->connectLabel);
    d->scene->addItem(d->connectButton);
    d->scene->addItem(d->disconnectButton);

    d->view = new dtkDistributorView(this);
    d->view->setScene(d->scene);

    // Widget setup

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->view);

    // State machine setup

    d->s1 = new QState;
    d->s1->assignProperty(d->connectLabel, "position", QPointF(0, -45));
    d->s1->assignProperty(d->connectButton, "opacity", 1.0);
    d->s1->assignProperty(d->disconnectButton, "opacity", 0.0);
    d->s1->assignProperty(d->scene, "connected", false);

    d->s2 = new QState;
    d->s2->assignProperty(d->connectLabel, "position", QPointF(-300, -300));
    d->s2->assignProperty(d->connectButton, "opacity", 0.0);
    d->s2->assignProperty(d->disconnectButton, "opacity", 1.0);
    d->s2->assignProperty(d->scene, "connected", true);

    connect(d->s2, SIGNAL(entered()), d->discoverer, SLOT(discover()));

    QSignalTransition *s1s2 = d->s1->addTransition(d->connectButton, SIGNAL(clicked()), d->s2);
    s1s2->addAnimation(new QPropertyAnimation(d->connectLabel, "position"));
    s1s2->addAnimation(new QPropertyAnimation(d->connectButton, "opacity"));
    s1s2->addAnimation(new QPropertyAnimation(d->disconnectButton, "opacity"));

    QSignalTransition *s2s1 = d->s2->addTransition(d->disconnectButton, SIGNAL(clicked()), d->s1);
    s2s1->addAnimation(new QPropertyAnimation(d->connectLabel, "position"));
    s2s1->addAnimation(new QPropertyAnimation(d->connectButton, "opacity"));
    s2s1->addAnimation(new QPropertyAnimation(d->disconnectButton, "opacity"));

    d->machine = new QStateMachine(this);
    d->machine->addState(d->s1);
    d->machine->addState(d->s2);
    d->machine->setInitialState(d->s1);
    d->machine->start();
}

dtkDistributor::~dtkDistributor(void)
{
    delete d->scene;
    delete d->s1;
    delete d->s2;
    delete d;

    d = NULL;
}

void dtkDistributor::resizeEvent(QResizeEvent *event)
{
    d->scene->setSceneRect(-event->size().width()/2, -event->size().height()/2, event->size().width(), event->size().height());

    d->s2->assignProperty(d->connectLabel, "position", d->scene->sceneRect().topLeft() + QPointF(10 + 64, 10 + 64));

    d->disconnectButton->setPos(d->scene->sceneRect().topLeft() + QPointF(10 + 64, 10 + 128 + 25));

    if(d->scene->connected())
        d->connectLabel->setPos(d->scene->sceneRect().topLeft() + QPointF(10 + 64, 10 + 64));
}
