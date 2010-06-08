
/* dtkDistributor.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 19:02:42 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jun  8 11:34:40 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 440
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
#include "dtkDistributorScene.h"
#include "dtkDistributorView.h"

#include <dtkGui/dtkInsetMenu.h>

class dtkDistributorPrivate
{
public:
    QPointF pos; int z; bool info;

    dtkDistributedDiscoverer *discoverer;
    dtkDistributorButton *handle;
    dtkDistributorButton *connectButton;
    dtkDistributorButton *disconnectButton;
    dtkDistributorCombo *connectCombo;
    dtkDistributorLabel *connectLabel;
    dtkDistributorScene *scene;
    dtkDistributorView *view;
    dtkInsetMenu *inset;

    QStateMachine *machine;
    QState *s1;
    QState *s2;
};

dtkDistributor::dtkDistributor(QWidget *parent) : QWidget(parent), d(new dtkDistributorPrivate)
{
    d->z = 0; d->info = false;

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

    d->inset = new dtkInsetMenu(this);
    d->inset->setMaximumHeight(0);

    d->inset->addTab("State"); {

        dtkInsetMenuPixmap *item1 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-free.png"));
        dtkInsetMenuPixmap *item2 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-jobexclusive.png"));
        dtkInsetMenuPixmap *item3 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-offline.png"));
        dtkInsetMenuPixmap *item4 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-down.png"));
        
        item1->setFlag(dtkDistributedNode::Free);
        item2->setFlag(dtkDistributedNode::JobExclusive);    
        item3->setFlag(dtkDistributedNode::Offline);
        item4->setFlag(dtkDistributedNode::Down);

        item1->setCheckable(true);
        item2->setCheckable(true);    
        item3->setCheckable(true);
        item4->setCheckable(true);
        
        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item4, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        d->inset->addItem(0, item1);
        d->inset->addItem(0, item2);
        d->inset->addItem(0, item3);
        d->inset->addItem(0, item4);
    }

    d->inset->addTab("Brand"); {

        dtkInsetMenuPixmap *item1 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-dell.png"));
        dtkInsetMenuPixmap *item2 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-ibm.png"));
        dtkInsetMenuPixmap *item3 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-hp.png"));

        item1->setFlag(dtkDistributedNode::Dell);
        item2->setFlag(dtkDistributedNode::Ibm);
        item3->setFlag(dtkDistributedNode::Hp);

        item1->setCheckable(true);
        item2->setCheckable(true);    
        item3->setCheckable(true);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        d->inset->addItem(1, item1);
        d->inset->addItem(1, item2);
        d->inset->addItem(1, item3);
    }

    d->inset->addTab("Network"); {

        dtkInsetMenuPixmap *item1 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-e1g.png"));
        dtkInsetMenuPixmap *item2 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-e10g.png"));
        dtkInsetMenuPixmap *item3 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-m2g.png"));
        dtkInsetMenuPixmap *item4 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-m10g.png"));
        dtkInsetMenuPixmap *item5 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i10g.png"));
        dtkInsetMenuPixmap *item6 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i20g.png"));
        dtkInsetMenuPixmap *item7 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i40g.png"));

        item1->setFlag(dtkDistributedNode::Ethernet1G);
        item2->setFlag(dtkDistributedNode::Ethernet10G);
        item3->setFlag(dtkDistributedNode::Myrinet2G);
        item4->setFlag(dtkDistributedNode::Myrinet10G);
        item5->setFlag(dtkDistributedNode::Infiniband10G);
        item6->setFlag(dtkDistributedNode::Infiniband20G);
        item7->setFlag(dtkDistributedNode::Infiniband40G);

        item1->setCheckable(true);
        item2->setCheckable(true);
        item3->setCheckable(true);
        item4->setCheckable(true);
        item5->setCheckable(true);
        item6->setCheckable(true);
        item7->setCheckable(true);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item4, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item5, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item6, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        d->inset->addItem(2, item1);
        d->inset->addItem(2, item2);
        d->inset->addItem(2, item3);
        d->inset->addItem(2, item4);
        d->inset->addItem(2, item5);
        d->inset->addItem(2, item6);
        d->inset->addItem(2, item7);
    }

    d->inset->addTab("Core"); {

        dtkInsetMenuPixmap *item1 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-1.png"));
        dtkInsetMenuPixmap *item2 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-2.png"));
        dtkInsetMenuPixmap *item3 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-4.png"));
        dtkInsetMenuPixmap *item4 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-8.png"));

        item1->setFlag(dtkDistributedCpu::Single);
        item2->setFlag(dtkDistributedCpu::Dual);
        item3->setFlag(dtkDistributedCpu::Quad);
        item4->setFlag(dtkDistributedCpu::Octo);

        item1->setCheckable(true);
        item2->setCheckable(true);
        item3->setCheckable(true);
        item4->setCheckable(true);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item4, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        d->inset->addItem(3, item1);
        d->inset->addItem(3, item2);
        d->inset->addItem(3, item3);
        d->inset->addItem(3, item4);
    }

    d->inset->addTab("Architecture"); {

        dtkInsetMenuPixmap *item1 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-x86.png"));
        dtkInsetMenuPixmap *item2 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-x86_64.png"));

        item1->setFlag(dtkDistributedCpu::x86);
        item2->setFlag(dtkDistributedCpu::x86_64);

        item1->setCheckable(true);
        item2->setCheckable(true);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        d->inset->addItem(4, item1);
        d->inset->addItem(4, item2);
    }

    d->inset->addTab("Model"); {

        dtkInsetMenuPixmap *item1 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-xeon.png"));
        dtkInsetMenuPixmap *item2 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-opteron.png"));

        item1->setFlag(dtkDistributedCpu::Xeon);
        item2->setFlag(dtkDistributedCpu::Opteron);

        item1->setCheckable(true);
        item2->setCheckable(true);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        d->inset->addItem(5, item1);
        d->inset->addItem(5, item2);
    }


    d->inset->addTab("Cluster"); {

        dtkInsetMenuPixmap *item1 = new dtkInsetMenuPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-cluster.png"));
        
        d->inset->addItem(6, item1);
    }

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

    foreach(dtkDistributedNode *node, d->discoverer->nodes()) {
        dtkDistributorNode *gnode = new dtkDistributorNode(node);
        connect(gnode, SIGNAL(showInformation(dtkDistributorNode *)), this, SLOT(showInformation(dtkDistributorNode *)));
        connect(gnode, SIGNAL(hideInformation(dtkDistributorNode *)), this, SLOT(hideInformation(dtkDistributorNode *)));
        d->scene->addItem(gnode);
    }

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

    connect(animation, SIGNAL(finished()), animation, SLOT(deleteLater()));

    animation->start();
}

void dtkDistributor::showInformation(dtkDistributorNode *node)
{
    if(d->info)
        return;

    d->pos = node->pos(); d->z = node->zValue(); d->info = true; node->setZValue(100000);

    QPropertyAnimation *animation1 = new QPropertyAnimation(node, "position");
    animation1->setDuration(1000);
    animation1->setEasingCurve(QEasingCurve::OutCubic);
    animation1->setStartValue(node->pos());
    animation1->setEndValue(d->view->mapToScene(this->width()/2, this->height()/2));

    QPropertyAnimation *animation2 = new QPropertyAnimation(node, "orientation");
    animation2->setDuration(1000);
    animation2->setEasingCurve(QEasingCurve::OutCubic);
    animation2->setStartValue(0);
    animation2->setEndValue(180);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(animation1);
    group->addAnimation(animation2);

    connect(group, SIGNAL(finished()), group, SLOT(deleteLater()));

    group->start();
}

void dtkDistributor::hideInformation(dtkDistributorNode *node)
{
    d->info = false; node->setZValue(d->z);

    QPropertyAnimation *animation1 = new QPropertyAnimation(node, "position");
    animation1->setDuration(1000);
    animation1->setEasingCurve(QEasingCurve::OutCubic);
    animation1->setStartValue(node->pos());
    animation1->setEndValue(d->pos);

    QPropertyAnimation *animation2 = new QPropertyAnimation(node, "orientation");
    animation2->setDuration(1000);
    animation2->setEasingCurve(QEasingCurve::OutCubic);
    animation2->setStartValue(180);
    animation2->setEndValue(0);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(animation1);
    group->addAnimation(animation2);

    connect(group, SIGNAL(finished()), group, SLOT(deleteLater()));

    group->start();
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
