/* dtkDistributorInset.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar 25 13:12:35 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 20:58:32 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 624
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCpu.h"
#include "dtkDistributedNode.h"
#include "dtkDistributorController.h"
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

    int current;
    int count;
};

dtkDistributorInsetScroller::dtkDistributorInsetScroller(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), d(new dtkDistributorInsetScrollerPrivate)
{
    this->setType(None);

    d->current = 1;
    d->count = 1;
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

void dtkDistributorInsetScroller::setCount(int count)
{
    d->count = count;
}

void dtkDistributorInsetScroller::reset(void)
{
    d->current = 1;
}

void dtkDistributorInsetScroller::incr(void)
{
    d->current++;
}

void dtkDistributorInsetScroller::decr(void)
{
    d->current--;
}

void dtkDistributorInsetScroller::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setFont(QFont("Helvetica", 9));
    painter->drawText(this->boundingRect(), Qt::AlignCenter, QString("Page %1 of %2").arg(d->current).arg(d->count));
    painter->restore();
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

class dtkDistributorInsetPixmapPrivate
{
public:
    int index;
    int flag;
};

dtkDistributorInsetPixmap::dtkDistributorInsetPixmap(const QPixmap& pixmap, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(pixmap, parent), d(new dtkDistributorInsetPixmapPrivate)
{
    d->index = -1;
    d->flag = -1;
}

dtkDistributorInsetPixmap::~dtkDistributorInsetPixmap(void)
{
    delete d;

    d = NULL;
}

void dtkDistributorInsetPixmap::setIndex(int index)
{
    d->index = index;
}

void dtkDistributorInsetPixmap::setFlag(int flag)
{
    d->flag = flag;

    if(d->index == 0 && dtkDistributorController::instance()->states().testFlag((dtkDistributedNode::State)d->flag))
        this->setGraphicsEffect(new QGraphicsBlurEffect(this));

    if(d->index == 1 && dtkDistributorController::instance()->brands().testFlag((dtkDistributedNode::Brand)d->flag))
        this->setGraphicsEffect(new QGraphicsBlurEffect(this));

    if(d->index == 2 && dtkDistributorController::instance()->networks().testFlag((dtkDistributedNode::Network)d->flag))
        this->setGraphicsEffect(new QGraphicsBlurEffect(this));

    if(d->index == 3 && dtkDistributorController::instance()->cardinalities().testFlag((dtkDistributedCpu::Cardinality)d->flag))
        this->setGraphicsEffect(new QGraphicsBlurEffect(this));

    if(d->index == 4 && dtkDistributorController::instance()->architectures().testFlag((dtkDistributedCpu::Architecture)d->flag))
        this->setGraphicsEffect(new QGraphicsBlurEffect(this));

    if(d->index == 5 && dtkDistributorController::instance()->models().testFlag((dtkDistributedCpu::Model)d->flag))
        this->setGraphicsEffect(new QGraphicsBlurEffect(this));
}

void dtkDistributorInsetPixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->graphicsEffect()) {
        this->setGraphicsEffect(new QGraphicsBlurEffect(this));
        emit toggled(d->index, d->flag, true);
    } else {
        this->setGraphicsEffect(0);
        emit toggled(d->index, d->flag, false);
    }
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

    qreal offset;

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

    d->scroller->reset();
}

void dtkDistributorInsetBody::update(void)
{
    // Set up item opacity

    QRectF rect(
        d->scene->sceneRect().x(),
        d->scene->sceneRect().y(),
        d->scene->sceneRect().width() - d->scroller->sceneBoundingRect().width(),
        d->scene->sceneRect().height());

    foreach(dtkDistributorInsetPixmap *item, d->items) {
        if (rect.contains(item->sceneBoundingRect().topRight()))
            item->setOpacity(1);
        else
            item->setOpacity(0);
    }

    // Set up scroller type

    if (d->items.count() && d->items.first()->pos().x()  < 0 && d->items.last()->opacity() == 0)
        d->scroller->setType(dtkDistributorInsetScroller::Both);

    if (d->items.count() && d->items.first()->pos().x() >= 0 && d->items.last()->opacity() == 1)
        d->scroller->setType(dtkDistributorInsetScroller::None);

    if (d->items.count() && d->items.first()->pos().x() >= 0 && d->items.last()->opacity() == 0)
        d->scroller->setType(dtkDistributorInsetScroller::Right);

    if (d->items.count() && d->items.first()->pos().x()  < 0 && d->items.last()->opacity() == 1)
        d->scroller->setType(dtkDistributorInsetScroller::Left);

    if (rect.width())
        d->scroller->setCount(((d->items.count() * (int)(d->item_width + d->item_margins)) / (int)rect.width()) + 1);

    // Parent method

    QFrame::update();
}

void dtkDistributorInsetBody::scrollLeft(void)
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

    foreach(QGraphicsItem *item, d->scene->items()) {

        if(dtkDistributorInsetPixmap *pixmap = dynamic_cast<dtkDistributorInsetPixmap *>(item)) {

            pixmap->setOpacity(1);

            QPropertyAnimation *animation = new QPropertyAnimation(pixmap, "pos");
            animation->setDuration(500);
            animation->setEasingCurve(QEasingCurve::OutQuad);
            animation->setStartValue(pixmap->pos());
            animation->setEndValue(pixmap->pos() + QPoint(d->offset, 0));
            
            group->addAnimation(animation);
        }
    }

    d->scroller->decr();

    connect(group, SIGNAL(finished()), this, SLOT(update()));

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void dtkDistributorInsetBody::scrollRight(void)
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        
    foreach(QGraphicsItem *item, d->scene->items()) {

        if(dtkDistributorInsetPixmap *pixmap = dynamic_cast<dtkDistributorInsetPixmap *>(item)) {

            pixmap->setOpacity(1);

            QPropertyAnimation *animation = new QPropertyAnimation(pixmap, "pos");
            animation->setDuration(500);
            animation->setEasingCurve(QEasingCurve::OutQuad);
            animation->setStartValue(pixmap->pos());
            animation->setEndValue(pixmap->pos() - QPoint(d->offset, 0));
            
            group->addAnimation(animation);
        }
    }

    d->scroller->incr();

    connect(group, SIGNAL(finished()), this, SLOT(update()));

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void dtkDistributorInsetBody::setCurrentIndex(int index)
{
    static int current_index = -1;
    
    if(index == current_index)
        return;

    this->clear();

    if(index == 0) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-free.png"));
        item1->setIndex(0);
        item1->setFlag(dtkDistributedNode::Free);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-jobexclusive.png"));
        item2->setIndex(0);
        item2->setFlag(dtkDistributedNode::JobExclusive);

        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-offline.png"));
        item3->setIndex(0);
        item3->setFlag(dtkDistributedNode::Offline);

        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item4 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-down.png"));
        item4->setIndex(0);
        item4->setFlag(dtkDistributedNode::Down);

        connect(item4, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation4 = new QPropertyAnimation(item4, "pos");
        animation4->setDuration(500);
        animation4->setEasingCurve(QEasingCurve::OutQuad);
        animation4->setStartValue(QPointF(-100, 0));
        animation4->setEndValue(QPointF(3 * (d->item_margins + d->item_width), 0));

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
        item1->setIndex(1);
        item1->setFlag(dtkDistributedNode::Dell);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-ibm.png"));

        item2->setIndex(1);
        item2->setFlag(dtkDistributedNode::Ibm);

        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-hp.png"));

        item3->setIndex(1);
        item3->setFlag(dtkDistributedNode::Hp);

        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (d->item_margins + d->item_width), 0));

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

        item1->setIndex(2);
        item1->setFlag(dtkDistributedNode::Ethernet1G);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-e10g.png"));

        item2->setIndex(2);
        item2->setFlag(dtkDistributedNode::Ethernet10G);

        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-m2g.png"));

        item3->setIndex(2);
        item3->setFlag(dtkDistributedNode::Myrinet2G);

        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item4 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-m10g.png"));

        item4->setIndex(2);
        item4->setFlag(dtkDistributedNode::Myrinet10G);

        connect(item4, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item5 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i10g.png"));

        item5->setIndex(2);
        item5->setFlag(dtkDistributedNode::Infiniband10G);

        connect(item5, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item6 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i20g.png"));

        item6->setIndex(2);
        item6->setFlag(dtkDistributedNode::Infiniband20G);

        connect(item6, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item7 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-i40g.png"));

        item7->setIndex(2);
        item7->setFlag(dtkDistributedNode::Infiniband40G);

        connect(item7, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation4 = new QPropertyAnimation(item4, "pos");
        animation4->setDuration(500);
        animation4->setEasingCurve(QEasingCurve::OutQuad);
        animation4->setStartValue(QPointF(-100, 0));
        animation4->setEndValue(QPointF(3 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation5 = new QPropertyAnimation(item5, "pos");
        animation5->setDuration(500);
        animation5->setEasingCurve(QEasingCurve::OutQuad);
        animation5->setStartValue(QPointF(-100, 0));
        animation5->setEndValue(QPointF(4 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation6 = new QPropertyAnimation(item6, "pos");
        animation6->setDuration(500);
        animation6->setEasingCurve(QEasingCurve::OutQuad);
        animation6->setStartValue(QPointF(-100, 0));
        animation6->setEndValue(QPointF(5 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation7 = new QPropertyAnimation(item7, "pos");
        animation7->setDuration(500);
        animation7->setEasingCurve(QEasingCurve::OutQuad);
        animation7->setStartValue(QPointF(-100, 0));
        animation7->setEndValue(QPointF(6 * (d->item_margins + d->item_width), 0));

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

        item1->setIndex(3);
        item1->setFlag(dtkDistributedCpu::Single);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-2.png"));

        item2->setIndex(3);
        item2->setFlag(dtkDistributedCpu::Dual);

        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-4.png"));

        item3->setIndex(3);
        item3->setFlag(dtkDistributedCpu::Quad);

        connect(item3, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item4 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-core-8.png"));

        item4->setIndex(3);
        item4->setFlag(dtkDistributedCpu::Octo);

        connect(item4, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation3 = new QPropertyAnimation(item3, "pos");
        animation3->setDuration(500);
        animation3->setEasingCurve(QEasingCurve::OutQuad);
        animation3->setStartValue(QPointF(-100, 0));
        animation3->setEndValue(QPointF(2 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation4 = new QPropertyAnimation(item4, "pos");
        animation4->setDuration(500);
        animation4->setEasingCurve(QEasingCurve::OutQuad);
        animation4->setStartValue(QPointF(-100, 0));
        animation4->setEndValue(QPointF(3 * (d->item_margins + d->item_width), 0));

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

        item1->setIndex(4);
        item1->setFlag(dtkDistributedCpu::x86);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));
        
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-x86_64.png"));

        item2->setIndex(4);
        item2->setFlag(dtkDistributedCpu::x86_64);

        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (d->item_margins + d->item_width), 0));

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

        item1->setIndex(5);
        item1->setFlag(dtkDistributedCpu::Xeon);

        connect(item1, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-opteron.png"));

        item2->setIndex(5);
        item2->setFlag(dtkDistributedCpu::Opteron);

        connect(item2, SIGNAL(toggled(int, int, bool)), dtkDistributorController::instance(), SLOT(toggle(int, int, bool)));

        QPropertyAnimation *animation1 = new QPropertyAnimation(item1, "pos");
        animation1->setDuration(500);
        animation1->setEasingCurve(QEasingCurve::OutQuad);
        animation1->setStartValue(QPointF(-100, 0));
        animation1->setEndValue(QPointF(0 * (d->item_margins + d->item_width), 0));

        QPropertyAnimation *animation2 = new QPropertyAnimation(item2, "pos");
        animation2->setDuration(500);
        animation2->setEasingCurve(QEasingCurve::OutQuad);
        animation2->setStartValue(QPointF(-100, 0));
        animation2->setEndValue(QPointF(1 * (d->item_margins + d->item_width), 0));

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
        animation1->setEndValue(QPointF(0 * (d->item_margins + d->item_width), 0));

        QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        group->addAnimation(animation1);

        d->scene->addItem(item1);

        d->items << item1;
        
        connect(group, SIGNAL(finished()), this, SLOT(update()));

        group->start(QAbstractAnimation::DeleteWhenStopped);
    }

    current_index = index;
}

void dtkDistributorInsetBody::resizeEvent(QResizeEvent *event)
{
    d->scene->setSceneRect(0, 0, this->width(), this->height());

    d->scroller->setPos(this->width()-d->scroller->boundingRect().width()-d->item_margins, this->height()/2 - d->scroller->boundingRect().height()/2);

    d->offset = (int)(this->width() - d->scroller->boundingRect().width()) - (int)(this->width() - d->scroller->boundingRect().width()) % ((int)d->item_width + (int)d->item_margins);

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
