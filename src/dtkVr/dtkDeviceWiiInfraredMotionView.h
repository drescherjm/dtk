/* dtkDeviceWiiInfraredMotionView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jan 22 12:30:30 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Jan 24 13:15:02 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDEVICEWIIINFRAREDMOTIONVIEW_H
#define DTKDEVICEWIIINFRAREDMOTIONVIEW_H

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiInfraredMotionScene
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiInfraredMotionScenePrivate;

class dtkDeviceWiiInfraredMotionScene : public QGraphicsScene
{
public:
     dtkDeviceWiiInfraredMotionScene(void);
    ~dtkDeviceWiiInfraredMotionScene(void);

    void update(float x, float y);
    void update(float x, float y, float s, int n);

protected:
    void drawBackground(QPainter *painter, const QRectF& rect);

private:
    dtkDeviceWiiInfraredMotionScenePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiInfraredMotionView
// /////////////////////////////////////////////////////////////////

class dtkDeviceWiiInfraredMotionViewPrivate;

class dtkDeviceWiiInfraredMotionView : public QGraphicsView
{
public:
     dtkDeviceWiiInfraredMotionView(void);
    ~dtkDeviceWiiInfraredMotionView(void);

private:
    dtkDeviceWiiInfraredMotionViewPrivate *d;
};

#endif
