/* dtkDeviceWiiJoystickMotionView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 21 16:12:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jan 22 09:25:15 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDEVICEWIIJOYSTICKMOTIONVIEW_H
#define DTKDEVICEWIIJOYSTICKMOTIONVIEW_H

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiJoystickMotionScene
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiJoystickMotionScenePrivate;

class dtkDeviceWiiJoystickMotionScene : public QGraphicsScene
{
public:
     dtkDeviceWiiJoystickMotionScene(void);
    ~dtkDeviceWiiJoystickMotionScene(void);

    void update(int x, int y);

protected:
    void drawBackground(QPainter *painter, const QRectF& rect);

private:
    dtkDeviceWiiJoystickMotionScenePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiJoystickMotionView
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiJoystickMotionViewPrivate;

class dtkDeviceWiiJoystickMotionView : public QGraphicsView
{
public:
     dtkDeviceWiiJoystickMotionView(void);
    ~dtkDeviceWiiJoystickMotionView(void);

private:
    dtkDeviceWiiJoystickMotionViewPrivate *d;
};

#endif
