/* dtkDistributorScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:30:50 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 22:49:03 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 84
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributorScene.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributorLabel
// /////////////////////////////////////////////////////////////////

dtkDistributorLabel::dtkDistributorLabel(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{

}

dtkDistributorLabel::~dtkDistributorLabel(void)
{

}

void dtkDistributorLabel::setPixmap(const QPixmap& pixmap)
{
    QGraphicsPixmapItem::setPixmap(pixmap);

    this->setOffset(-pixmap.width()/2, -pixmap.height()/2);
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorButton
// /////////////////////////////////////////////////////////////////

dtkDistributorButton::dtkDistributorButton(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{

}

dtkDistributorButton::~dtkDistributorButton(void)
{

}

void dtkDistributorButton::setPixmapNormal(const QPixmap& pixmap)
{
    this->pixmap_normal = pixmap;

    this->setPixmap(pixmap_normal);
    this->setOffset(-pixmap_normal.width()/2, -pixmap_normal.height()/2);
}

void dtkDistributorButton::setPixmapPressed(const QPixmap& pixmap)
{
    this->pixmap_pressed = pixmap;
}

void dtkDistributorButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPixmap(this->pixmap_pressed);
    this->setOffset(-pixmap_pressed.width()/2, -pixmap_pressed.height()/2);
}

void dtkDistributorButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPixmap(this->pixmap_normal);
    this->setOffset(-pixmap_normal.width()/2, -pixmap_normal.height()/2);

    emit clicked();
}

// /////////////////////////////////////////////////////////////////
// dtkDistributorScene
// /////////////////////////////////////////////////////////////////

class dtkDistributorScenePrivate
{
public:
    bool connected;
};

dtkDistributorScene::dtkDistributorScene(void) : QGraphicsScene(), d(new dtkDistributorScenePrivate)
{
    d->connected = false;

    this->setBackgroundBrush(QColor(0xae, 0xae, 0xae));
}

dtkDistributorScene::~dtkDistributorScene(void)
{
    delete d;

    d = NULL;
}

bool dtkDistributorScene::connected(void)
{
    return d->connected;
}

void dtkDistributorScene::setConnected(bool connected)
{
    d->connected = connected;
}

void dtkDistributorScene::drawBackground(QPainter *painter, const QRectF& rect)
{
    painter->save();
    painter->fillRect(rect, this->backgroundBrush());
    if(d->connected) {
        painter->setPen(Qt::darkGray);
        painter->setBrush(Qt::gray);
        painter->drawRect(QRectF(rect.topLeft(), rect.bottomLeft() + QPointF(150, 0)).adjusted(-1, -1, 0, 0));
    }
    painter->restore();
}
