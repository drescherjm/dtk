/* dtkDeviceWiiInfraredMotionView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jan 22 12:31:14 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Jan 24 13:16:58 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDeviceWiiInfraredMotionView.h"

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiInfraredMotionScene
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiInfraredMotionScenePrivate
{
public:
    QGraphicsEllipseItem *cursor;
    QGraphicsEllipseItem *ir0;
    QGraphicsEllipseItem *ir1;
    QGraphicsEllipseItem *ir2;
    QGraphicsEllipseItem *ir3;
};

dtkDeviceWiiInfraredMotionScene::dtkDeviceWiiInfraredMotionScene(void) : QGraphicsScene(), d(new dtkDeviceWiiInfraredMotionScenePrivate)
{
    d->cursor = new QGraphicsEllipseItem(-10, -10, 20, 20);
    d->cursor->setBrush(Qt::red);
    d->cursor->setPen(Qt::NoPen);

    d->ir0 = new QGraphicsEllipseItem(-10, -10, 20, 20);
    d->ir0->setBrush(QColor(0xa7, 0xb6, 0xd3));
    d->ir0->setPen(Qt::NoPen);

    d->ir1 = new QGraphicsEllipseItem(-10, -10, 20, 20);
    d->ir1->setBrush(QColor(0xa7, 0xb6, 0xd3));
    d->ir1->setPen(Qt::NoPen);

    d->ir2 = new QGraphicsEllipseItem(-10, -10, 20, 20);
    d->ir2->setBrush(QColor(0xa7, 0xb6, 0xd3));
    d->ir2->setPen(Qt::NoPen);

    d->ir3 = new QGraphicsEllipseItem(-10, -10, 20, 20);
    d->ir3->setBrush(QColor(0xa7, 0xb6, 0xd3));
    d->ir3->setPen(Qt::NoPen);

    this->addItem(d->cursor);
    this->addItem(d->ir0);
    this->addItem(d->ir1);
    this->addItem(d->ir2);
    this->addItem(d->ir3);

    this->setSceneRect(0, 0, 1023, 700);
}

dtkDeviceWiiInfraredMotionScene::~dtkDeviceWiiInfraredMotionScene(void)
{
    delete d;

    d = NULL;
}

void dtkDeviceWiiInfraredMotionScene::update(float x, float y)
{
    d->cursor->setPos(x, y);
}

void dtkDeviceWiiInfraredMotionScene::update(float x, float y, float s, int n)
{
    if (n == 0) {
        d->ir0->setRect(-s/2, -s/2, s*10, s*10);
        d->ir0->setPos(x, y);
    }

    if (n == 1) {
        d->ir1->setRect(-s/2, -s/2, s*10, s*10);
        d->ir1->setPos(x, y);
    }

    if (n == 2) {
        d->ir2->setRect(-s/2, -s/2, s, s);
        d->ir2->setPos(x, y);
    }

    if (n == 3) {
        d->ir3->setRect(-s/2, -s/2, s, s);
        d->ir3->setPos(x, y);
    }
}

void dtkDeviceWiiInfraredMotionScene::drawBackground(QPainter *painter, const QRectF& rect)
{
    painter->save();
    painter->fillRect(rect, QColor(0x49, 0x49, 0x49));
    painter->restore();
}

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiInfraredMotionView
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiInfraredMotionViewPrivate
{
public:
};

dtkDeviceWiiInfraredMotionView::dtkDeviceWiiInfraredMotionView(void) : QGraphicsView(), d(new dtkDeviceWiiInfraredMotionViewPrivate)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setFixedHeight(1023);
    this->setFixedWidth(700);
    this->setWindowTitle("Infrared motion view");
}

dtkDeviceWiiInfraredMotionView::~dtkDeviceWiiInfraredMotionView(void)
{
    delete d;

    d = NULL;
}
