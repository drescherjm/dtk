/* dtkDeviceWiiAccelerationView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Jan 24 13:46:47 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Jan 24 13:47:35 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDEVICEWIIACCELERATIONVIEW_H
#define DTKDEVICEWIIACCELERATIONVIEW_H

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiAccelerationScene
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiAccelerationScenePrivate;

class dtkDeviceWiiAccelerationScene : public QGraphicsScene
{
public:
     dtkDeviceWiiAccelerationScene(void);
    ~dtkDeviceWiiAccelerationScene(void);

    void update(int x, int y, int z);

protected:
    void drawBackground(QPainter *painter, const QRectF& rect);

private:
    dtkDeviceWiiAccelerationScenePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiAccelerationView
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiAccelerationViewPrivate;

class dtkDeviceWiiAccelerationView : public QGraphicsView
{
public:
     dtkDeviceWiiAccelerationView(void);
    ~dtkDeviceWiiAccelerationView(void);

private:
    dtkDeviceWiiAccelerationViewPrivate *d;
};

#endif
