/* dtkDistributorInset.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Mar 25 13:12:35 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 28 01:26:08 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 294
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
    QPushButton *button1 = new QPushButton("State", this); button1->setFixedHeight(21); button1->setCheckable(true);
    QPushButton *button2 = new QPushButton("Brand", this); button2->setFixedHeight(21); button2->setCheckable(true);
    QPushButton *button3 = new QPushButton("Network", this); button3->setFixedHeight(21); button3->setCheckable(true);
    QPushButton *button4 = new QPushButton("Core", this); button4->setFixedHeight(21); button4->setCheckable(true);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(button1, 0);
    group->addButton(button2, 1);
    group->addButton(button3, 2);
    group->addButton(button4, 3);
    group->setExclusive(true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    layout->setContentsMargins(10, 3, 10, 3);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);

    this->setFixedHeight(26);

    connect(group, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));
}

dtkDistributorInsetHeader::~dtkDistributorInsetHeader(void)
{

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
    // QStackedWidget *stack;

    dtkDistributorInsetScene *scene;
    dtkDistributorInsetView *view;
};

dtkDistributorInsetBody::dtkDistributorInsetBody(QWidget *parent) : QFrame(parent), d(new dtkDistributorInsetBodyPrivate)
{
    d->scene = new dtkDistributorInsetScene(this);

    d->view = new dtkDistributorInsetView(this);
    d->view->setScene(d->scene);
    
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(d->view);

    this->setFixedHeight(74);
}

dtkDistributorInsetBody::~dtkDistributorInsetBody(void)
{
    delete d;
    
    d = NULL;
}

void dtkDistributorInsetBody::setCurrentIndex(int index)
{
    d->scene->clear();
    
    if(index == 0) {

        dtkDistributorInsetPixmap *item1 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-free.png"));
        dtkDistributorInsetPixmap *item2 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-jobexclusive.png"));
        dtkDistributorInsetPixmap *item3 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-down.png"));
        dtkDistributorInsetPixmap *item4 = new dtkDistributorInsetPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-distributed-inset-offline.png"));

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
        
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void dtkDistributorInsetBody::resizeEvent(QResizeEvent *event)
{
    d->scene->setSceneRect(0, 0, this->width(), this->height());
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
