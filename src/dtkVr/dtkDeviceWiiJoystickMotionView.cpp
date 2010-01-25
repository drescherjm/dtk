/* dtkDeviceWiiJoystickMotionView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 21 16:15:26 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jan 22 11:39:34 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 56
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDeviceWiiJoystickMotionView.h"

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiJoystickMotionScene
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiJoystickMotionScenePrivate
{
public:
    QGraphicsEllipseItem *target;
};

dtkDeviceWiiJoystickMotionScene::dtkDeviceWiiJoystickMotionScene(void) : QGraphicsScene(), d(new dtkDeviceWiiJoystickMotionScenePrivate)
{
    d->target = new QGraphicsEllipseItem(-10, -10, 20, 20);
    d->target->setBrush(QColor(0xa7, 0xb6, 0xd3));
    d->target->setPen(Qt::NoPen);

    this->addItem(d->target);
    this->setSceneRect(29, 34, 225-29, 228-34);
}

dtkDeviceWiiJoystickMotionScene::~dtkDeviceWiiJoystickMotionScene(void)
{
    delete d;

    d = NULL;
}

void dtkDeviceWiiJoystickMotionScene::update(int x, int y)
{
    d->target->setPos(x, y);
}

void dtkDeviceWiiJoystickMotionScene::drawBackground(QPainter *painter, const QRectF& rect)
{
    painter->save();
    painter->fillRect(rect, QColor(0x49, 0x49, 0x49));
    painter->setPen(Qt::gray);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(this->sceneRect());
    painter->restore();
}

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiJoystickMotionView
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiJoystickMotionViewPrivate
{
public:
};

dtkDeviceWiiJoystickMotionView::dtkDeviceWiiJoystickMotionView(void) : QGraphicsView(), d(new dtkDeviceWiiJoystickMotionViewPrivate)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setFixedHeight(300);
    this->setFixedWidth(300);
    this->setWindowTitle("Joystick motion view");
}

dtkDeviceWiiJoystickMotionView::~dtkDeviceWiiJoystickMotionView(void)
{
    delete d;

    d = NULL;
}
