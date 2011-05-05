/* dtkVrSlave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu May  5 09:17:17 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 598
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrScreen.h"
#include "dtkVrSlave.h"

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>
#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

#include <dtkDistributed/dtkDistributedCommunicator.h>

class dtkVrSlavePrivate
{
public:
    dtkVrScreen *screen;

    dtkAbstractView *view;

    bool stereo;
};

dtkVrSlave::dtkVrSlave(dtkDistributedCommunicator *communicator) : dtkVrProcess(communicator), d(new dtkVrSlavePrivate)
{
    if(communicator->size() > 2) {

    d->screen = new dtkVrScreen(
        dtkVrScreen::screens[this->rank()-1][0],
        dtkVrScreen::screens[this->rank()-1][1],
        dtkVrScreen::screens[this->rank()-1][2]
    );

    } else {

    d->screen = new dtkVrScreen(
        dtkVrScreen::screens[1][0],
        dtkVrScreen::screens[1][1],
        dtkVrScreen::screens[1][2]
    );
    
    }

    d->view = NULL;
}

dtkVrSlave::~dtkVrSlave(void)
{
    delete d->screen;
    delete d;
    
    d = NULL;
}

void dtkVrSlave::initialize(void)
{
    if (d->view)
        d->view->initialize();
}

void dtkVrSlave::uninitialize(void)
{
    if (d->view)
        d->view->uninitialize();
}

void dtkVrSlave::show(void)
{
    if (d->view) {
        d->view->showNormal();
        d->view->widget()->setWindowTitle(d->view->widget()->windowTitle() + " - Rank " + QString::number(this->rank()));
    }
}

void dtkVrSlave::showFullScreen(void)
{
    if (d->view)
        d->view->showFullScreen();
}

void dtkVrSlave::resize(int w, int h)
{
    if (d->view)
        d->view->widget()->resize(w, h);
}

void dtkVrSlave::move(int x, int y)
{
    if (d->view)
        d->view->widget()->move(x, y);
}

void dtkVrSlave::setView(dtkAbstractView *view)
{
    d->view = view;
}

void dtkVrSlave::setStereo(bool on)
{
    d->stereo = on;
}

void dtkVrSlave::process(void)
{
    // Wand management /////////////////////////////////////////////////////////////////

    // static bool dirty = true;
    // static bool dirty2 = false;
    // static dtkVec3 initialPosition;
    // static dtkQuat initialOrientation;
    // static dtkVec3 magic;
    
    // this->setupWandPosition(this->wand()->currentPosition());
    // this->setupWandOrientation(this->wand()->currentOrientation());

    // if(this->wand()->action() == dtkVrWand::dtkVrWandPicking && this->wand()->mode() == dtkVrWand::dtkVrWandNavigation) {
        
    //     if(dirty) {
    //         initialPosition = this->scenePosition();
    //         initialOrientation = this->sceneOrientation();
    //         dirty = false;
    //         dirty2 = true;
    //     }

    //     dtkVec3 wp  = this->wand()->currentPosition();
    //     dtkVec3 wp0 = this->wand()->referencePosition();
    //     dtkQuat wq  = this->wand()->currentOrientation();
    //     dtkQuat wq0 = this->wand()->referenceOrientation();
    //     dtkVec3 sp0 = initialPosition;
    //     dtkQuat sq0 = initialOrientation;

    //     dtkVec3 dt  = wp - wp0;
    //     dtkQuat dq  = wq * wq0.inv();

    //     this->setupSceneOrientation(dq * sq0);
    //     this->setupScenePosition(dq.inv().rotate(sp0 + wp - wp0) - dq.inv().rotate(wp) + wp);
    // }

    // if(this->wand()->action() == dtkVrWand::dtkVrWandNone && this->wand()->mode() == dtkVrWand::dtkVrWandNavigation) {

    //     if(dirty2) {
    //         dirty = true;
    //         dirty2 = false;            
    //     }

    // }

    // // User management /////////////////////////////////////////////////////////////////

    // dtkVec3 eye(this->user()->position());

    // double focusDist = 5;
    // dtkVec3 halfEyeDist(0.035, 0, 0);

    // double x0   = (eye - d->screen->lowerLeft()) * d->screen->right();
    // double y0   = (eye - d->screen->lowerLeft()) * d->screen->up();
    // dtkVec3 center = d->screen->lowerLeft() + d->screen->right() * x0 + d->screen->up() * y0;
    // double dist = (eye - center).length();
    // dtkVec3 focusPoint = eye + (center-eye)/dist*focusDist;
    
    // if (!qApp->arguments().contains("--stereo")) {

    //     this->setupCameraLookAt(eye, focusPoint, d->screen->up());
        
    //     double near   = 1e-2;
    //     double far    = 1e2;
    //     double left   = -x0 * near / dist;
    //     double bottom = -y0 * near / dist;
    //     double right  =  (d->screen->width() - x0) * near / dist;
    //     double top    = (d->screen->height() - y0) * near / dist;
        
    //     this->setupCameraFrustum(left, right, bottom, top, near, far);

    // } else {

    //     dtkVec3 leftEye = eye + this->user()->orientation().rotate(-halfEyeDist);
    //     double x0   = (leftEye - d->screen->lowerLeft()) * d->screen->right();
    //     double y0   = (leftEye - d->screen->lowerLeft()) * d->screen->up();
    //     dtkVec3 center = d->screen->lowerLeft() + d->screen->right() * x0 + d->screen->up() * y0;
    //     double dist = (leftEye - center).length();

    //     this->setupLeftEyeCameraLookAt(leftEye, focusPoint, d->screen->up());
        
    //     double near   = 1e-2;
    //     double far    = 1e2;
    //     double left   = -x0 * near / dist;
    //     double bottom = -y0 * near / dist;
    //     double right  =  (d->screen->width() - x0) * near / dist;
    //     double top    = (d->screen->height() - y0) * near / dist;
        
    //     this->setupLeftEyeCameraFrustum(left, right, bottom, top, near, far);        
        
    //     dtkVec3 rightEye = eye + this->user()->orientation().rotate(halfEyeDist);
    //     x0   = (rightEye - d->screen->lowerLeft()) * d->screen->right();
    //     y0   = (rightEye - d->screen->lowerLeft()) * d->screen->up();
    //     center = d->screen->lowerLeft() + d->screen->right() * x0 + d->screen->up() * y0;
    //     dist = (rightEye - center).length();
        
    //     this->setupRightEyeCameraLookAt(rightEye, focusPoint, d->screen->up());
        
    //     near   = 1e-2;
    //     far    = 1e2;
    //     left   = -x0 * near / dist;
    //     bottom = -y0 * near / dist;
    //     right  =  (d->screen->width() - x0) * near / dist;
    //     top    = (d->screen->height() - y0) * near / dist;
        
    //     this->setupRightEyeCameraFrustum(left, right, bottom, top, near, far);
    // }
    
    d->view->update();
}

dtkVec3 dtkVrSlave::scenePosition(void) const
{
    if (d->view)
        return d->view->scenePosition();
}

dtkQuat dtkVrSlave::sceneOrientation(void) const
{
    if (d->view)
        return d->view->sceneOrientation();
}

void dtkVrSlave::setupWandPosition(const dtkVec3& position)
{
    if (d->view)
        d->view->setupWandPosition(position);
}

void dtkVrSlave::setupWandOrientation(const dtkQuat& orientation)
{
    if (d->view)
        d->view->setupWandOrientation(orientation);
}

void dtkVrSlave::setupScenePosition(const dtkVec3& position)
{
    if (d->view)
        d->view->setupScenePosition(position);
}

void dtkVrSlave::setupSceneOrientation(const dtkQuat& orientation)
{
    if (d->view)
        d->view->setupSceneOrientation(orientation);
}

void dtkVrSlave::setupCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up)
{
    if (d->view)
        d->view->setupCameraLookAt(eye, center, up);
}

void dtkVrSlave::setupLeftEyeCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up)
{
    if (d->view)
        d->view->setupLeftEyeCameraLookAt(eye, center, up);
}

void dtkVrSlave::setupRightEyeCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up)
{
    if (d->view)
        d->view->setupRightEyeCameraLookAt(eye, center, up);
}

void dtkVrSlave::setupCameraFrustum(double left, double right, double bottom, double top, double near, double far)
{
    if (d->view)
        d->view->setupCameraFrustum(left, right, bottom, top, near, far);
}

void dtkVrSlave::setupLeftEyeCameraFrustum(double left, double right, double bottom, double top, double near, double far)
{
    if (d->view)
        d->view->setupLeftEyeCameraFrustum(left, right, bottom, top, near, far);
}

void dtkVrSlave::setupRightEyeCameraFrustum(double left, double right, double bottom, double top, double near, double far)
{
    if (d->view)
        d->view->setupRightEyeCameraFrustum(left, right, bottom, top, near, far);
}
