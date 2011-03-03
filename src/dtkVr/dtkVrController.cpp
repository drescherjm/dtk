/* dtkVrController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  6 12:01:59 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 26 11:27:48 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 268
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrController.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkVec3.h>

#if defined(DTK_WRAP_VRPN)
#include <dtkVr/dtkVrTrackerVrpn.h>
#include <dtkVr/dtkVrDeviceVrpn.h>
#include <dtkVr/dtkVrScreen.h>
#endif

#include <dtkCore/dtkAbstractView.h>

#include <dtkMath/dtkMath.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkVrControllerPrivate
// /////////////////////////////////////////////////////////////////

class dtkVrControllerPrivate
{
public:
    static void positionHandler1(float x, float y, float z);

public:
    QUrl trackerUrl;
    QUrl deviceUrl;

    bool activated;

#if defined(DTK_WRAP_VRPN)
    dtkVrTrackerVrpn *tracker;
    dtkVrDeviceVrpn *device;
#endif
    
    static dtkVector3D<float> last;

    dtkAbstractView *view;

    static dtkVrControllerPrivate *self;

    dtkVrController *q;
};

void dtkVrControllerPrivate::positionHandler1(float x, float y, float z)
{
    if(!self->activated)
        return;

    dtkVector3D<float> l = dtkVector3D<float>(1.0, 0.0, 0.0);
    dtkVector3D<float> m = dtkVector3D<float>(0.0, 1.0, 0.0);
    dtkVector3D<float> n = dtkVector3D<float>(0.0, 0.0, 1.0);
    dtkVector3D<dtkVector3D<float> > to = dtkVector3D<dtkVector3D<float> >(l, m, n);

    dtkQuaternion<float> q = dtkQuaternionFromAxisAngle(l, (float)(90.0));

    dtkVector3D<float> o = dtkVector3D<float>(x, y, z - 1.7);
    dtkVector3D<float> p = dtkMatSquaredFromQuaternion(q) * o;

    dtkVector3D<float> delta = p - last;

    last = p;

    if(self->view) {

        double camera_up[3];
        double camera_position[3];
        double camera_focalpnt[3];

        self->view->cameraUp(camera_up);
        self->view->cameraPosition(camera_position);
        self->view->cameraFocalPoint(camera_focalpnt);

        dtkVector3D<float> j = dtkVector3D<float>(camera_up[0], camera_up[1], camera_up[2]);
        dtkVector3D<float> k = dtkVector3D<float>(camera_position[0] - camera_focalpnt[0],
                                                  camera_position[1] - camera_focalpnt[1],
                                                  camera_position[2] - camera_focalpnt[2]);
        dtkVector3D<float> i = j%k;

        dtkVector3D<dtkVector3D<float> > fr = dtkVector3D<dtkVector3D<float> >(i.unit(), j.unit(), k.unit());

        dtkMatrixSquared<float> t = dtkChangeOfBasis(fr, to);

        delta = t * delta;

        float xmin, xmax, ymin, ymax, zmin, zmax; self->view->bounds(xmin, xmax, ymin, ymax, zmin, zmax);

        float ratio_x_scene = xmax-xmin;
        float ratio_y_scene = ymax-ymin;
        float ratio_z_scene = zmax-zmin;
        
        float ratio_x_world = 1;
        float ratio_y_world = 1;
        float ratio_z_world = 1;

#if defined(DTK_WRAP_VRPN)
        ratio_x_world = dtkVrScreen::screens[4][1].x()-dtkVrScreen::screens[4][0].x();
        ratio_y_world = dtkVrScreen::screens[4][2].z()-dtkVrScreen::screens[4][0].z(); // This is not a mistake
        ratio_z_world = 4;
#endif

        camera_position[0] += 1.5*delta[0]*ratio_x_scene/ratio_x_world;
        camera_position[1] += 1.5*delta[1]*ratio_y_scene/ratio_y_world;
        camera_position[2] += 1.5*delta[2]*ratio_z_scene/ratio_z_world;

        self->view->setCameraPosition(camera_position[0], camera_position[1], camera_position[2]);
        self->view->update();
    }
}

dtkVector3D<float> dtkVrControllerPrivate::last = dtkVector3D<float>(0.0, 0.0, 0.0);

dtkVrControllerPrivate *dtkVrControllerPrivate::self = NULL;

// /////////////////////////////////////////////////////////////////
// dtkVrController
// /////////////////////////////////////////////////////////////////

dtkVrController *dtkVrController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkVrController;

    return s_instance;
}

void dtkVrController::setTracker(const QUrl& url)
{
#if defined(DTK_WRAP_VRPN)
    if(!d->tracker) {
        d->tracker = new dtkVrTrackerVrpn;
        d->tracker->registerPositionHandler1(dtkVrControllerPrivate::positionHandler1);
        d->tracker->startConnection(url);
        connect(qApp, SIGNAL(aboutToQuit()), d->tracker, SLOT(stopConnection()));
    }
#else
    Q_UNUSED(url);

    qDebug() << "Please build dtk with vrpn support to enable tracking.";
#endif
}

void dtkVrController::setDevice(const QUrl& url)
{
#if defined(DTK_WRAP_VRPN)
    if(!d->device) {
        d->device = new dtkVrDeviceVrpn;
        d->device->startConnection(url);
        connect(d->device, SIGNAL(buttonPressed(int)), this, SLOT(onButtonPressed(int)));
        connect(d->device, SIGNAL(buttonReleased(int)), this, SLOT(onButtonReleased(int)));
        connect(qApp, SIGNAL(aboutToQuit()), d->device, SLOT(stopConnection()));
    }
#else
    Q_UNUSED(url);

    qDebug() << "Please build dtk with vrpn support to enable devices.";
#endif
}

void dtkVrController::assign(dtkAbstractView *view)
{
    d->view = view;
}

void dtkVrController::onButtonPressed(int button)
{
    d->activated = true;

    d->view->disableInteraction();
}

void dtkVrController::onButtonReleased(int button)
{
    d->activated = false;

    d->view->enableInteraction();
}

dtkVrController::dtkVrController(void) : QObject(), d(new dtkVrControllerPrivate)
{
    d->q = this;
    d->self = d;
    d->view = NULL;

    d->activated = false;

#if defined(DTK_WRAP_VRPN)
    d->tracker = NULL;
    d->device = NULL;
#endif
}

dtkVrController::~dtkVrController(void)
{
    delete d;

    d = NULL;
}

dtkVrController *dtkVrController::s_instance = NULL;
