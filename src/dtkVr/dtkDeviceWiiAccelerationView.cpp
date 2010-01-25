/* dtkDeviceWiiAccelerationView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Jan 24 13:47:50 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Jan 24 21:11:21 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDeviceWiiAccelerationView.h"

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiAccelerationScene
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiAccelerationScenePrivate
{
public:

};

dtkDeviceWiiAccelerationScene::dtkDeviceWiiAccelerationScene(void) : QGraphicsScene(), d(new dtkDeviceWiiAccelerationScenePrivate)
{

}

dtkDeviceWiiAccelerationScene::~dtkDeviceWiiAccelerationScene(void)
{
    delete d;

    d = NULL;
}

void dtkDeviceWiiAccelerationScene::update(int x, int y, int z)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(z);
}

void dtkDeviceWiiAccelerationScene::drawBackground(QPainter *painter, const QRectF& rect)
{
    painter->save();
    painter->fillRect(rect, QColor(0x49, 0x49, 0x49));
    painter->restore();
}

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiAccelerationView
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiAccelerationViewPrivate
{
public:
};

dtkDeviceWiiAccelerationView::dtkDeviceWiiAccelerationView(void) : QGraphicsView(), d(new dtkDeviceWiiAccelerationViewPrivate)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setRenderHints(QPainter::Antialiasing);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setFixedHeight(300);
    this->setFixedWidth(300);
    this->setWindowTitle("Acceleration view");
}

dtkDeviceWiiAccelerationView::~dtkDeviceWiiAccelerationView(void)
{
    delete d;

    d = NULL;
}
