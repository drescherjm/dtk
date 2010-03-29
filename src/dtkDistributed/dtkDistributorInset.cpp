/* dtkDistributorInset.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar 25 13:12:35 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 29 15:18:46 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 424
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributorInset.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetHeader
// /////////////////////////////////////////////////////////////////

dtkDistributorInsetHeader::dtkDistributorInsetHeader(QWidget *parent) : QFrame(parent)
{
    QPushButton *button1 = new QPushButton("State", this);
    button1->setCheckable(true);
    
    QPushButton *button2 = new QPushButton("Brand", this);
    button2->setCheckable(true);
    
    QPushButton *button3 = new QPushButton("Network", this);
    button3->setCheckable(true);
    
    QPushButton *button4 = new QPushButton("Core", this);
    button4->setCheckable(true);

    QPushButton *button5 = new QPushButton("Architecture", this);
    button5->setCheckable(true);

    QPushButton *button6 = new QPushButton("Model", this);
    button6->setCheckable(true);

    QPushButton *button7 = new QPushButton("Cluster", this);
    button7->setCheckable(true);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(button1, 0);
    group->addButton(button2, 1);
    group->addButton(button3, 2);
    group->addButton(button4, 3);
    group->addButton(button5, 4);
    group->addButton(button6, 5);
    group->addButton(button7, 6);
    group->setExclusive(true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    layout->setContentsMargins(10, 3, 10, 3);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);
    layout->addWidget(button6);
    layout->addWidget(button7);

    this->setFixedHeight(26);

    connect(group, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));
}

dtkDistributorInsetHeader::~dtkDistributorInsetHeader(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetScoller
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetScrollerPrivate
{
public:
    dtkDistributorInsetScroller::Type type;
};

dtkDistributorInsetScroller::dtkDistributorInsetScroller(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), d(new dtkDistributorInsetScrollerPrivate)
{
    this->setType(None);
}

dtkDistributorInsetScroller::~dtkDistributorInsetScroller(void)
{
    delete d;

    d = NULL;
}

void dtkDistributorInsetScroller::setType(Type type)
{
    switch(type) {
    case Both:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-scroller-both.png"));
        break;
    case Left:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-scroller-left.png"));
        break;
    case Right:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-scroller-right.png"));
        break;
    default:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-scroller-none.png"));
        break;
    };

    d->type = type;
}

void dtkDistributorInsetScroller::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(d->type == None)
        return;

    if((d->type == Both || d->type == Left) && event->pos().x() < 30)
        emit scrollLeft();

    if((d->type == Both || d->type == Right) && event->pos().x() > this->boundingRect().width()-30)
        emit scrollRight();
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetScene
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetScene : public QGraphicsScene
{
public:
     dtkDistributorInsetScene(QObject *parent);
    ~dtkDistributorInsetScene(void);
};

dtkDistributorInsetScene::dtkDistributorInsetScene(QObject *parent) : QGraphicsScene(parent)
{

}

dtkDistributorInsetScene::~dtkDistributorInsetScene(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetView
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetView : public QGraphicsView
{
public:
     dtkDistributorInsetView(QWidget *parent);
    ~dtkDistributorInsetView(void);
};

dtkDistributorInsetView::dtkDistributorInsetView(QWidget *parent) : QGraphicsView(parent)
{
    QPalette p = this->palette(); p.setBrush(backgroundRole(), Qt::NoBrush);

    this->setAttribute(Qt::WA_TranslucentBackground);    
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setPalette(p);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

dtkDistributorInsetView::~dtkDistributorInsetView(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetPixmap
// /////////////////////////////////////////////////////////////////

dtkDistributorInsetPixmap::dtkDistributorInsetPixmap(const QPixmap& pixmap, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(pixmap, parent)
{

}

dtkDistributorInsetPixmap::~dtkDistributorInsetPixmap(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkDistributorInsetBody
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetBodyPrivate
{
public:
    dtkDistributorInsetScroller *scroller;
    dtkDistributorInsetScene *scene;
    dtkDistributorInsetView *view;

    qreal item_width;
    qreal item_height;
    qreal item_margins;

    QList<dtkDistributorInsetPixmap *> items;
};

dtkDistributorInsetBody::dtkDistributorInsetBody(QWidget *parent) : QFrame(parent), d(new dtkDistributorInsetBodyPrivate)
{
    d->item_width = 76;
    d->item_height = 76;
    d->item_margins = 10;

    d->scroller = new dtkDistributorInsetScroller;

    d->scene = new dtkDistributorInsetScene(this);
    d->scene->addItem(d->scroller);

    d->view = new dtkDistributorInsetView(this);
    d->view->setScene(d->scene);
    
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(d->view);

    this->setFixedHeight(74);

    connect(d->scroller, SIGNAL(scrollLeft()), this, SLOT(scrollLeft()));
    connect(d->scroller, SIGNAL(scrollRight()), this, SLOT(scrollRight()));
}

dtkDistributorInsetBody::~dtkDistributorInsetBody(void)
{
    delete d->scroller;
    delete d;
    
    d = NULL;
}

void dtkDistributorInsetBody::clear(void)
{
    foreach(dtkDistributorInsetPixmap *item, d->items) {
        d->scene->removeItem(item);
        delete item;
    }

    d->items.clear();
}

void dtkDistributorInsetBody::update(void)
{
    // Set up item opacity

    foreach(dtkDistributorInsetPixmap *item, d->items) {
        if (item->sceneBoundingRect().right() > d->scroller->sceneBoundingRect().left())
            item->setOpacity(0);
        else
            item->setOpacity(1);
    }

    // Set up scroller type

    if (d->items.count() && d->items.first()->pos().x() < 0 && d->items.last()->opacity() == 0)
        d->scroller->setType(dtkDistributorInsetScroller::Both);

    if (d->items.count() && d->items.first()->pos().x() >= 0 && d->items.last()->opacity() == 1)
        d->scroller->setType(dtkDistributorInsetScroller::None);

    if (d->items.count() && d->items.first()->pos().x() >= 0 && d->items.last()->opacity() == 0)
        d->scroller->setType(dtkDistributorInsetScroller::Right);

    if (d->items.count() && d->items.first()->pos().x() < 0 && d->items.last()->opacity() == 1)
        d->scroller->setType(dtkDistributorInsetScroller::Left);

    // Parent method

    QFrame::update();
}

void dtkDistributorInsetBody::scrollLeft(void)
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        
    foreach(QGraphicsItem *item, d->scene->items()) {
        if(dtkDistributorInsetPixmap *pixmap = dynamic_cast<dtkDistributorInsetPixmap *>(item)) {

                pixmap->setOpacity(1.0);

                QPropertyAnimation *animation = new QPropertyAnimation(pixmap, "pos");
                animation->setDuration(500);
                animation->setEasingCurve(QEasingCurve::OutQuad);
                animation->setStartValue(pixmap->pos());
                animation->setEndValue(pixmap->pos() + QPoint(this->width() - d->scroller->boundingRect().width(), 0));

                group->addAnimation(animation);
        }
    }

    connect(group, SIGNAL(finished()), this, SLOT(update()));

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void dtkDistributorInsetBody::scrollRight(void)
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        
    foreach(QGraphicsItem *item, d->scene->items()) {
        if(dtkDistributorInsetPixmap *pixmap = dynamic_cast<dtkDistributorInsetPixmap *>(item)) {

                QPropertyAnimation *animation = new QPropertyAnimation(pixmap, "pos");
                animation->setDuration(500);
                animation->setEasingCurve(QEasingCurve::OutQuad);
                animation->setStartValue(pixmap->pos());
                animation->setEndValue(pixmap->pos() - QPoint(this->width() - d->scroller->boundingRect().width(), 0));

                group->addAnimation(animation);
        }
    }

    connect(group, SIGNAL(finished()), this, SLOT(update()));

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void dtkDistributorInsetBody::setCurrentIndex(int index)
{
    this->clear();

    if(index == 0) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-free.png"));
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-jobexclusive.png"));
        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-offline.png"));
        dtkDistributorInsetPixmap *item4 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-down.png"));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (10 + 76), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (10 + 76), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (10 + 76), 0));

        QPropertyAnimation *animation4 = new QPropertyAnimation(item4, "pos");
        animation4->setDuration(500);
        animation4->setEasingCurve(QEasingCurve::OutQuad);
        animation4->setStartValue(QPointF(-100, 0));
        animation4->setEndValue(QPointF(3 * (10 + 76), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);
        group->addAnimation(animation2);
        group->addAnimation(animation3);
        group->addAnimation(animation4);

        d->scene->addItem(item1);
        d->scene->addItem(item2);
        d->scene->addItem(item3);
        d->scene->addItem(item4);

        d->items << item1 << item2 << item3 << item4;

        connect(group, SIGNAL(finished()), this, SLOT(update()));
        
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if(index == 1) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-dell.png"));
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-ibm.png"));
        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-hp.png"));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (10 + 76), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (10 + 76), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (10 + 76), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);
        group->addAnimation(animation2);
        group->addAnimation(animation3);

        d->scene->addItem(item1);
        d->scene->addItem(item2);
        d->scene->addItem(item3);

        d->items << item1 << item2 << item3;

        connect(group, SIGNAL(finished()), this, SLOT(update()));
        
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if(index == 2) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-e1g.png"));
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-e10g.png"));
        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-m2g.png"));
        dtkDistributorInsetPixmap *item4 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-m10g.png"));
        dtkDistributorInsetPixmap *item5 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i10g.png"));
        dtkDistributorInsetPixmap *item6 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i20g.png"));
        dtkDistributorInsetPixmap *item7 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i40g.png"));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (10 + 76), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (10 + 76), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (10 + 76), 0));

        QPropertyAnimation *animation4 = new QPropertyAnimation(item4, "pos");
        animation4->setDuration(500);
        animation4->setEasingCurve(QEasingCurve::OutQuad);
        animation4->setStartValue(QPointF(-100, 0));
        animation4->setEndValue(QPointF(3 * (10 + 76), 0));

        QPropertyAnimation *animation5 = new QPropertyAnimation(item5, "pos");
        animation5->setDuration(500);
        animation5->setEasingCurve(QEasingCurve::OutQuad);
        animation5->setStartValue(QPointF(-100, 0));
        animation5->setEndValue(QPointF(4 * (10 + 76), 0));

        QPropertyAnimation *animation6 = new QPropertyAnimation(item6, "pos");
        animation6->setDuration(500);
        animation6->setEasingCurve(QEasingCurve::OutQuad);
        animation6->setStartValue(QPointF(-100, 0));
        animation6->setEndValue(QPointF(5 * (10 + 76), 0));

        QPropertyAnimation *animation7 = new QPropertyAnimation(item7, "pos");
        animation7->setDuration(500);
        animation7->setEasingCurve(QEasingCurve::OutQuad);
        animation7->setStartValue(QPointF(-100, 0));
        animation7->setEndValue(QPointF(6 * (10 + 76), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);
        group->addAnimation(animation2);
        group->addAnimation(animation3);
        group->addAnimation(animation4);
        group->addAnimation(animation5);
        group->addAnimation(animation6);
        group->addAnimation(animation7);

        d->scene->addItem(item1);
        d->scene->addItem(item2);
        d->scene->addItem(item3);
        d->scene->addItem(item4);
        d->scene->addItem(item5);
        d->scene->addItem(item6);
        d->scene->addItem(item7);

        d->items << item1 << item2 << item3 << item4 << item5 << item6 << item7;
        
        connect(group, SIGNAL(finished()), this, SLOT(update()));

        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if(index == 3) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-1.png"));
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-2.png"));
        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-4.png"));
        dtkDistributorInsetPixmap *item4 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-8.png"));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (10 + 76), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (10 + 76), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (10 + 76), 0));

        QPropertyAnimation *animation4 = new QPropertyAnimation(item4, "pos");
        animation4->setDuration(500);
        animation4->setEasingCurve(QEasingCurve::OutQuad);
        animation4->setStartValue(QPointF(-100, 0));
        animation4->setEndValue(QPointF(3 * (10 + 76), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);
        group->addAnimation(animation2);
        group->addAnimation(animation3);
        group->addAnimation(animation4);

        d->scene->addItem(item1);
        d->scene->addItem(item2);
        d->scene->addItem(item3);
        d->scene->addItem(item4);

        d->items << item1 << item2 << item3 << item4;

        connect(group, SIGNAL(finished()), this, SLOT(update()));
        
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if(index == 4) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-x86.png"));
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-x86_64.png"));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (10 + 76), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (10 + 76), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);
        group->addAnimation(animation2);

        d->scene->addItem(item1);
        d->scene->addItem(item2);

        d->items << item1 << item2;

        connect(group, SIGNAL(finished()), this, SLOT(update()));
        
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if(index == 5) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-xeon.png"));
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-opteron.png"));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (10 + 76), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (10 + 76), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);
        group->addAnimation(animation2);

        d->scene->addItem(item1);
        d->scene->addItem(item2);

        d->items << item1 << item2;

        connect(group, SIGNAL(finished()), this, SLOT(update()));
        
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    if(index == 6) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-cluster.png"));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (10 + 76), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);

        d->scene->addItem(item1);

        d->items << item1;
        
        connect(group, SIGNAL(finished()), this, SLOT(update()));

        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void dtkDistributorInsetBody::resizeEvent(QResizeEvent *event)
{
    d->scene->setSceneRect(0, 0, this->width(), this->height());

    d->scroller->setPos(this->width()-d->scroller->boundingRect().width()-10, this->height()/2 - d->scroller->boundingRect().height()/2);

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorInset
// /////////////////////////////////////////////////////////////////

class dtkDistributorInsetPrivate
{
public:
    dtkDistributorInsetHeader *header;
    dtkDistributorInsetBody *body;
};

dtkDistributorInset::dtkDistributorInset(QWidget *parent) : QFrame(parent), d(new dtkDistributorInsetPrivate)
{
    d->header = new dtkDistributorInsetHeader(this);
    d->body = new dtkDistributorInsetBody(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->header);
    layout->addWidget(d->body);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet(dtkReadFile(":dtkDistributed/dtkDistributorInset.qss"));

    connect(d->header, SIGNAL(buttonClicked(int)), d->body, SLOT(setCurrentIndex(int)));
}

dtkDistributorInset::~dtkDistributorInset(void)
{
    delete d;

    d = NULL;
}
