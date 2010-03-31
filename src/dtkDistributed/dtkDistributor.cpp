
/* dtkDistributor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 19:02:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 21:50:53 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 316
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
#include "dtkDistributorController.h"
#include "dtkDistributorInset.h"
#include "dtkDistributorScene.h"
#include "dtkDistributorView.h"

class dtkDistributorPrivate
{
public:
    dtkDistributedDiscoverer *discoverer;
    dtkDistributorButton *handle;
    dtkDistributorButton *connectButton;
    dtkDistributorButton *disconnectButton;
    dtkDistributorCombo *connectCombo;
    dtkDistributorLabel *connectLabel;
    dtkDistributorScene *scene;
    dtkDistributorView *view;
    dtkDistributorInset *inset;

    QStateMachine *machine;
    QState *s1;
    QState *s2;
};

dtkDistributor::dtkDistributor(QWidget *parent) : QWidget(parent), d(new dtkDistributorPrivate)
{
    d->discoverer = NULL;

    d->connectLabel = new dtkDistributorLabel;
    // d->connectLabel->setLabel("nef.inria.fr");
    d->connectLabel->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-connect-label.png"));
    d->connectLabel->setPos(0, -45);

    d->connectCombo = new dtkDistributorCombo;
    d->connectCombo->setPos(-64, 20);
    d->connectCombo->setOpacity(1.0);
    d->connectCombo->setZValue(10);

    d->handle = new dtkDistributorButton;
    d->handle->setPixmapNormal(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-handle.png"));
    d->handle->setPixmapPressed(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-handle-pressed.png"));
    d->handle->setOpacity(0);

    d->connectButton = new dtkDistributorButton;
    d->connectButton->setPixmapNormal(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-connect-button.png"));
    d->connectButton->setPixmapPressed(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-connect-button-pressed.png"));
    d->connectButton->setPos(0, 65);
    d->connectButton->setOpacity(1);

    d->disconnectButton = new dtkDistributorButton;
    d->disconnectButton->setPixmapNormal(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-disconnect-button.png"));
    d->disconnectButton->setPixmapPressed(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-disconnect-button-pressed.png"));
    d->disconnectButton->setPos(-300, -190);
    d->disconnectButton->setOpacity(0);

    d->inset = new dtkDistributorInset(this);
    d->inset->setMaximumHeight(0);

    d->scene = new dtkDistributorScene;
    d->scene->addItem(d->handle);
    d->scene->addItem(d->connectLabel);
    d->scene->addItem(d->connectCombo);
    d->scene->addItem(d->connectButton);
    d->scene->addItem(d->disconnectButton);

    d->view = new dtkDistributorView(this);
    d->view->setScene(d->scene);

    // Widget setup

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->inset);
    layout->addWidget(d->view);

    // State machine setup

    d->s1 = new QState;
    d->s1->assignProperty(d->handle, "opacity", 0.0);
    d->s1->assignProperty(d->connectLabel, "position", QPointF(0, -45));
    d->s1->assignProperty(d->connectButton, "opacity", 1.0);
    d->s1->assignProperty(d->disconnectButton, "opacity", 0.0);
    d->s1->assignProperty(d->scene, "connected", false);
    d->s1->assignProperty(d->connectCombo, "opacity", 1.0);
    d->s1->assignProperty(d->inset, "maximumHeight", 0);

    d->s2 = new QState;
    d->s2->assignProperty(d->handle, "opacity", 1.0);
    d->s2->assignProperty(d->connectLabel, "position", QPointF(-300, -300));
    d->s2->assignProperty(d->connectButton, "opacity", 0.0);
    d->s2->assignProperty(d->disconnectButton, "opacity", 1.0);
    d->s2->assignProperty(d->scene, "connected", true);
    d->s2->assignProperty(d->connectCombo, "opacity", 0.0);
    d->s2->assignProperty(d->inset, "maximumHeight", 0);

    connect(d->s1, SIGNAL(entered()), this, SLOT(clear()));
    connect(d->s2, SIGNAL(entered()), this, SLOT(discover()));

    QSignalTransition *s1s2 = d->s1->addTransition(d->connectButton, SIGNAL(clicked()), d->s2);
    s1s2->addAnimation(new QPropertyAnimation(d->connectLabel, "position"));
    s1s2->addAnimation(new QPropertyAnimation(d->connectButton, "opacity"));
    s1s2->addAnimation(new QPropertyAnimation(d->disconnectButton, "opacity"));

    QSignalTransition *s2s1 = d->s2->addTransition(d->disconnectButton, SIGNAL(clicked()), d->s1);
    s2s1->addAnimation(new QPropertyAnimation(d->connectLabel, "position"));
    s2s1->addAnimation(new QPropertyAnimation(d->connectButton, "opacity"));
    s2s1->addAnimation(new QPropertyAnimation(d->disconnectButton, "opacity"));
    s2s1->addAnimation(new QPropertyAnimation(d->inset, "maximumHeight"));

    d->machine = new QStateMachine(this);
    d->machine->addState(d->s1);
    d->machine->addState(d->s2);
    d->machine->setInitialState(d->s1);
    d->machine->start();

    // Events

    connect(d->handle, SIGNAL(clicked()), this, SLOT(toggle()));

    // Control

    connect(dtkDistributorController::instance(), SIGNAL(updated()), this, SLOT(update()));
}

dtkDistributor::~dtkDistributor(void)
{
    delete d->scene;
    delete d->s1;
    delete d->s2;
    delete d;

    d = NULL;
}

void dtkDistributor::clear(void)
{
    // Clear the scene

    foreach(QGraphicsItem *item, d->scene->items()) {
        if(dtkDistributorNode *node = dynamic_cast<dtkDistributorNode *>(item)) {
            d->scene->removeItem(item);
            delete item;
        }
    }

    // Clear the discoverer

    if (d->discoverer) {
        delete d->discoverer;
        d->discoverer = NULL;
    }    
}

void dtkDistributor::discover(void)
{
    if(!d->discoverer && d->connectCombo->text().contains("grid5000")) {
        d->discoverer = new dtkDistributedDiscovererOar;
    } else {
        d->discoverer = new dtkDistributedDiscovererTorque;
    }

    d->discoverer->discover(QUrl(d->connectCombo->text()));

    foreach(dtkDistributedNode *node, d->discoverer->nodes())
        d->scene->addItem(new dtkDistributorNode(node));

    d->connectLabel->setLabel(d->connectCombo->text());

    this->update();
}

void dtkDistributor::update(void)
{
    // Update nodes

    QList<dtkDistributorNode *> nodes;

    foreach(QGraphicsItem *item, d->scene->items())
        if(dtkDistributorNode *node = dynamic_cast<dtkDistributorNode *>(item))
            if(node->filter())
                nodes << node;
            else
                node->hide();

    qreal ox = d->scene->sceneRect().topLeft().x() + 128/2 + 150 + 10;
    qreal oy = d->scene->sceneRect().topLeft().y() + 128/2 + 10;
    qreal dx = 128;
    qreal dy = 128;
    qreal  x = ox;
    qreal  y = oy;

    foreach(dtkDistributorNode *node, nodes) {

        node->setPos(x, y);
        node->show();

        if(x + dx > d->scene->sceneRect().width()/2 - 128/2) {
            y += dy;
            x  = ox;
        } else {
            x += dx;
        }
    }

    d->scene->setSceneRect(
        d->scene->sceneRect().topLeft().x(),
        d->scene->sceneRect().topLeft().y(),
        d->scene->sceneRect().width(),
        qMax(y - d->scene->sceneRect().topLeft().y() + dy, d->scene->sceneRect().height()));

    d->view->ensureVisible(
        -d->view->size().width()/2,
        -d->view->size().height()/2,
        10,
        10);

    // Parent implementation

    QWidget::update();
}

void dtkDistributor::toggle(void)
{
    QPropertyAnimation *animation = new QPropertyAnimation(d->inset, "maximumHeight");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutBounce);

    if(!d->inset->height()) {
        animation->setStartValue(d->inset->height());
        animation->setEndValue(100);
    } else {
        animation->setStartValue(d->inset->height());
        animation->setEndValue(0);
    }

    animation->start();

    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));
}

void dtkDistributor::resizeEvent(QResizeEvent *event)
{
    // Update scene

    d->scene->setSceneRect(
        -event->size().width()/2,
        -event->size().height()/2,
         event->size().width()-20, // Prevent offset due to scrollbar
         event->size().height()
        );

    // Update states

    d->s2->assignProperty(d->connectLabel, "position", d->scene->sceneRect().topLeft() + QPointF(10 + 64, 10 + 64));

    // Update buttons

    d->handle->setPos(0, -event->size().height()/2);

    d->disconnectButton->setPos(d->scene->sceneRect().topLeft() + QPointF(10 + 64, 10 + 128 + +20 + 25));

    // Update labels

    if(d->scene->connected())
        d->connectLabel->setPos(d->scene->sceneRect().topLeft() + QPointF(10 + 64, 10 + 64));

    // Update items
    
    this->update();
}
