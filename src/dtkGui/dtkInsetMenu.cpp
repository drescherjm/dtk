/* dtkInsetMenu.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jun  2 13:30:45 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun  8 11:18:45 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 128
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInsetMenu.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuHeader
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuHeaderPrivate
{
public:
    QButtonGroup *group;
    QHBoxLayout *layout;

    int count;
};

dtkInsetMenuHeader::dtkInsetMenuHeader(QWidget *parent) : QFrame(parent), d(new dtkInsetMenuHeaderPrivate)
{
    d->count = 0;

    d->group = new QButtonGroup(this);
    d->group->setExclusive(true);

    d->layout = new QHBoxLayout(this);
    d->layout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    d->layout->setContentsMargins(10, 3, 10, 3);

    this->setFixedHeight(26);

    connect(d->group, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));
}

dtkInsetMenuHeader::~dtkInsetMenuHeader(void)
{
    delete d;

    d = NULL;
}

int dtkInsetMenuHeader::addTab(const QString& name)
{
    QPushButton *button = new QPushButton(name, this);
    button->setCheckable(true);

    d->layout->addWidget(button);

    d->group->addButton(button, d->count++);

    return d->group->id(button);
}

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuScoller
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuScrollerPrivate
{
public:
    dtkInsetMenuScroller::Type type;

    int current;
    int count;
};

dtkInsetMenuScroller::dtkInsetMenuScroller(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent), d(new dtkInsetMenuScrollerPrivate)
{
    this->setType(None);

    d->current = 1;
    d->count = 1;
}

dtkInsetMenuScroller::~dtkInsetMenuScroller(void)
{
    delete d;

    d = NULL;
}

void dtkInsetMenuScroller::setType(Type type)
{
    switch(type) {
    case Both:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-gui-inset-menu-scroller-both.png"));
        break;
    case Left:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-gui-inset-menu-scroller-left.png"));
        break;
    case Right:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-gui-inset-menu-scroller-right.png"));
        break;
    default:
        this->setPixmap(QPixmap(":dtkDistributed/pixmaps/dtk-gui-inset-menu-scoller-none.png"));
        break;
    };

    d->type = type;
}

void dtkInsetMenuScroller::setCount(int count)
{
    d->count = count;
}

void dtkInsetMenuScroller::reset(void)
{
    d->current = 1;
}

void dtkInsetMenuScroller::incr(void)
{
    d->current++;
}

void dtkInsetMenuScroller::decr(void)
{
    d->current--;
}

void dtkInsetMenuScroller::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    painter->save();
    painter->setPen(Qt::darkGray);
    painter->setFont(QFont("Helvetica", 9));
    painter->drawText(this->boundingRect(), Qt::AlignCenter, QString("Page %1 of %2").arg(d->current).arg(d->count));
    painter->restore();
}

void dtkInsetMenuScroller::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(d->type == None)
        return;

    if((d->type == Both || d->type == Left) && event->pos().x() < 30)
        emit scrollLeft();

    if((d->type == Both || d->type == Right) && event->pos().x() > this->boundingRect().width()-30)
        emit scrollRight();
}

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuScene
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuScene : public QGraphicsScene
{
public:
     dtkInsetMenuScene(QObject *parent);
    ~dtkInsetMenuScene(void);
};

dtkInsetMenuScene::dtkInsetMenuScene(QObject *parent) : QGraphicsScene(parent)
{

}

dtkInsetMenuScene::~dtkInsetMenuScene(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuView
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuView : public QGraphicsView
{
public:
     dtkInsetMenuView(QWidget *parent);
    ~dtkInsetMenuView(void);
};

dtkInsetMenuView::dtkInsetMenuView(QWidget *parent) : QGraphicsView(parent)
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

dtkInsetMenuView::~dtkInsetMenuView(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuPixmap
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuPixmapPrivate
{
public:
    bool checkable;
    int index;
    int flag;
};

dtkInsetMenuPixmap::dtkInsetMenuPixmap(const QPixmap& pixmap, QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(pixmap, parent), d(new dtkInsetMenuPixmapPrivate)
{
    d->checkable = false;
    d->index = -1;
    d->flag = -1;
}

dtkInsetMenuPixmap::~dtkInsetMenuPixmap(void)
{
    delete d;

    d = NULL;
}

void dtkInsetMenuPixmap::setIndex(int index)
{
    d->index = index;
}

void dtkInsetMenuPixmap::setFlag(int flag)
{
    d->flag = flag;
}

void dtkInsetMenuPixmap::setCheckable(bool checkable)
{
    d->checkable = checkable;
}

bool dtkInsetMenuPixmap::checkable(void)
{
    return d->checkable;
}

void dtkInsetMenuPixmap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!d->checkable) {
        if(!this->graphicsEffect())
            this->setGraphicsEffect(new QGraphicsColorizeEffect(this));
    } else {
        if(!this->graphicsEffect()) {
            this->setGraphicsEffect(new QGraphicsBlurEffect(this));
            emit toggled(d->index, d->flag, true);
        } else {
            this->setGraphicsEffect(0);
            emit toggled(d->index, d->flag, false);
        }
    }
}

void dtkInsetMenuPixmap::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!d->checkable) {
        if (this->graphicsEffect())
            this->setGraphicsEffect(0);

        emit triggered();
    }
}

// /////////////////////////////////////////////////////////////////
// dtkInsetMenuBody
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuBodyPrivate
{
public:
    dtkInsetMenuScroller *scroller;
    dtkInsetMenuScene *scene;
    dtkInsetMenuView *view;

    qreal item_width;
    qreal item_height;
    qreal item_margins;

    qreal offset;

    QMap<int, QList<dtkInsetMenuPixmap *> > items;

    int index;
};

dtkInsetMenuBody::dtkInsetMenuBody(QWidget *parent) : QFrame(parent), d(new dtkInsetMenuBodyPrivate)
{
    d->index = -1;

    d->item_width = 76;
    d->item_height = 76;
    d->item_margins = 10;

    d->scroller = new dtkInsetMenuScroller;

    d->scene = new dtkInsetMenuScene(this);
    d->scene->addItem(d->scroller);

    d->view = new dtkInsetMenuView(this);
    d->view->setScene(d->scene);
    
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(d->view);

    this->setFixedHeight(74);

    connect(d->scroller, SIGNAL(scrollLeft()), this, SLOT(scrollLeft()));
    connect(d->scroller, SIGNAL(scrollRight()), this, SLOT(scrollRight()));
}

dtkInsetMenuBody::~dtkInsetMenuBody(void)
{
    delete d->scroller;
    delete d;
    
    d = NULL;
}

int dtkInsetMenuBody::addItem(int tab, const QPixmap& pixmap)
{
    dtkInsetMenuPixmap *item = new dtkInsetMenuPixmap(pixmap);
    item->setIndex(tab);
    
    // connect(item, SIGNAL(toggled(int, int, bool)), this, SIGNAL(toggled(int, int, bool)));

    d->items[tab] << item;

	return tab; //?
}

int dtkInsetMenuBody::addItem(int tab, dtkInsetMenuPixmap *item)
{
    item->setIndex(tab);
    
    d->items[tab] << item;

	return tab; //?
}

void dtkInsetMenuBody::clear(void)
{
    foreach(dtkInsetMenuPixmap *item, d->items.value(d->index))
        d->scene->removeItem(item);

    d->scroller->reset();
}

void dtkInsetMenuBody::update(void)
{
    // Set up item opacity

    QRectF rect(
        d->scene->sceneRect().x(),
        d->scene->sceneRect().y(),
        d->scene->sceneRect().width() - d->scroller->sceneBoundingRect().width(),
        d->scene->sceneRect().height());

    foreach(dtkInsetMenuPixmap *item, d->items.value(d->index)) {
        if (rect.contains(item->sceneBoundingRect().topRight()))
            item->setOpacity(1);
        else
            item->setOpacity(0);
    }

    // Set up scroller type

    if (d->items.value(d->index).count() && d->items.value(d->index).first()->pos().x()  < 0 && d->items.value(d->index).last()->opacity() == 0)
        d->scroller->setType(dtkInsetMenuScroller::Both);

    if (d->items.value(d->index).count() && d->items.value(d->index).first()->pos().x() >= 0 && d->items.value(d->index).last()->opacity() == 1)
        d->scroller->setType(dtkInsetMenuScroller::None);

    if (d->items.value(d->index).count() && d->items.value(d->index).first()->pos().x() >= 0 && d->items.value(d->index).last()->opacity() == 0)
        d->scroller->setType(dtkInsetMenuScroller::Right);

    if (d->items.value(d->index).count() && d->items.value(d->index).first()->pos().x()  < 0 && d->items.value(d->index).last()->opacity() == 1)
        d->scroller->setType(dtkInsetMenuScroller::Left);

    if (rect.width())
        d->scroller->setCount(((d->items.value(d->index).count() * (int)(d->item_width + d->item_margins)) / (int)rect.width()) + 1);

    // Parent method

    QFrame::update();
}

void dtkInsetMenuBody::scrollLeft(void)
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

    foreach(QGraphicsItem *item, d->scene->items()) {

        if(dtkInsetMenuPixmap *pixmap = dynamic_cast<dtkInsetMenuPixmap *>(item)) {

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

void dtkInsetMenuBody::scrollRight(void)
{
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
        
    foreach(QGraphicsItem *item, d->scene->items()) {

        if(dtkInsetMenuPixmap *pixmap = dynamic_cast<dtkInsetMenuPixmap *>(item)) {

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

void dtkInsetMenuBody::setCurrentIndex(int index)
{
    if(index == d->index)
        return;

    this->clear();

    d->index = index;

    int count = 0;

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);

    foreach(dtkInsetMenuPixmap *item, d->items.value(d->index)) {

        QPropertyAnimation *animation = new QPropertyAnimation(item, "pos");
        animation->setDuration(500);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->setStartValue(QPointF(-100, 0));
        animation->setEndValue(QPointF(d->item_margins + count++ * (d->item_margins + d->item_width), 0));

        group->addAnimation(animation);

        d->scene->addItem(item);

        connect(group, SIGNAL(finished()), this, SLOT(update()));
    }

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void dtkInsetMenuBody::resizeEvent(QResizeEvent *event)
{
    d->scene->setSceneRect(0, 0, this->width(), this->height());

    d->scroller->setPos(this->width()-d->scroller->boundingRect().width()-d->item_margins, this->height()/2 - d->scroller->boundingRect().height()/2);

    d->offset = (int)(this->width() - d->scroller->boundingRect().width()) - (int)(this->width() - d->scroller->boundingRect().width()) % ((int)d->item_width + (int)d->item_margins);

    this->update();
}

// /////////////////////////////////////////////////////////////////
// dtkInsetMenu
// /////////////////////////////////////////////////////////////////

class dtkInsetMenuPrivate
{
public:
    dtkInsetMenuHeader *header;
    dtkInsetMenuBody *body;
};

dtkInsetMenu::dtkInsetMenu(QWidget *parent) : QFrame(parent), d(new dtkInsetMenuPrivate)
{
    d->header = new dtkInsetMenuHeader(this);
    d->body = new dtkInsetMenuBody(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->header);
    layout->addWidget(d->body);

    this->setFixedHeight(0);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setStyleSheet(dtkReadFile(":dtkGui/dtkInsetMenu.qss"));

    connect(d->header, SIGNAL(buttonClicked(int)), d->body, SLOT(setCurrentIndex(int)));
}

dtkInsetMenu::~dtkInsetMenu(void)
{
    delete d;

    d = NULL;
}

QSize dtkInsetMenu::sizeHint(void) const
{
    return QSize(100, 100);
}

int dtkInsetMenu::addTab(const QString& name)
{
    return d->header->addTab(name);
}

int dtkInsetMenu::addItem(int tab, const QPixmap& pixmap)
{
    return d->body->addItem(tab, pixmap);
}

int dtkInsetMenu::addItem(int tab, dtkInsetMenuPixmap *item)
{
    return d->body->addItem(tab, item);
}

void dtkInsetMenu::setStyle(dtkInsetMenu::Style style)
{
    switch(style) {
    case dtkInsetMenuStyleDefault:
    case dtkInsetMenuStyleBlue:
        this->setStyleSheet(dtkReadFile(":dtkGui/dtkInsetMenu.qss"));
        break;
    case dtkInsetMenuStyleGreen:
        this->setStyleSheet(dtkReadFile(":dtkGui/dtkInsetMenu-green.qss"));
        break;
    case dtkInsetMenuStyleOrange:
        this->setStyleSheet(dtkReadFile(":dtkGui/dtkInsetMenu-orange.qss"));
        break;
    default:
        break;
    }
}
