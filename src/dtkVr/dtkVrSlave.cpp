/* dtkVrSlave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 23 15:32:27 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 250
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrScreen.h"
#include "dtkVrSlave.h"
#include "dtkVrUser.h"
#include "dtkVrWand.h"

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>
#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>

class dtkVrSlavePrivate
{
public:
    dtkVrScreen *screen;

    dtkAbstractView *view;
};

dtkVrSlave::dtkVrSlave(dtkDistributedCommunicator *communicator) : dtkVrProcess(communicator), d(new dtkVrSlavePrivate)
{
    d->screen = new dtkVrScreen(
        dtkVrScreen::screens[this->rank()-1][0],
        dtkVrScreen::screens[this->rank()-1][1],
        dtkVrScreen::screens[this->rank()-1][2]
    );

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

void dtkVrSlave::process(void)
{
    dtkVec3 eye(this->user()->position());

    double focusDist = 10;
    dtkVec3 halfEyeDist(0.035, 0, 0);

    double x0   = (eye - d->screen->lowerLeft()) * d->screen->right();
    double y0   = (eye - d->screen->lowerLeft()) * d->screen->up();
    dtkVec3 center = d->screen->lowerLeft() + d->screen->right() * x0 + d->screen->up() * y0;
    double dist = (eye - center).length();
    dtkVec3 focusPoint = eye + (center-eye)/dist*focusDist;
    
    if (!qApp->arguments().contains("--stereo")) {

        this->setupCameraLookAt(eye, focusPoint, d->screen->up());
        
        double near   = 1e-2;
        double far    = 1e2;
        double left   = -x0 * near / dist;
        double bottom = -y0 * near / dist;
        double right  =  (d->screen->width() - x0) * near / dist;
        double top    = (d->screen->height() - y0) * near / dist;
        
        this->setupCameraFrustum(left, right, bottom, top, near, far);

    } else {

        dtkVec3 leftEye = eye + this->user()->orientation().rotate(-halfEyeDist);
        double x0   = (leftEye - d->screen->lowerLeft()) * d->screen->right();
        double y0   = (leftEye - d->screen->lowerLeft()) * d->screen->up();
        dtkVec3 center = d->screen->lowerLeft() + d->screen->right() * x0 + d->screen->up() * y0;
        double dist = (leftEye - center).length();

        this->setupLeftEyeCameraLookAt(leftEye, focusPoint, d->screen->up());
        
        double near   = 1e-2;
        double far    = 1e2;
        double left   = -x0 * near / dist;
        double bottom = -y0 * near / dist;
        double right  =  (d->screen->width() - x0) * near / dist;
        double top    = (d->screen->height() - y0) * near / dist;
        
        this->setupLeftEyeCameraFrustum(left, right, bottom, top, near, far);        
        
        dtkVec3 rightEye = eye + this->user()->orientation().rotate(halfEyeDist);
        x0   = (rightEye - d->screen->lowerLeft()) * d->screen->right();
        y0   = (rightEye - d->screen->lowerLeft()) * d->screen->up();
        center = d->screen->lowerLeft() + d->screen->right() * x0 + d->screen->up() * y0;
        dist = (rightEye - center).length();
        
        this->setupRightEyeCameraLookAt(rightEye, focusPoint, d->screen->up());
        
        near   = 1e-2;
        far    = 1e2;
        left   = -x0 * near / dist;
        bottom = -y0 * near / dist;
        right  =  (d->screen->width() - x0) * near / dist;
        top    = (d->screen->height() - y0) * near / dist;
        
        this->setupRightEyeCameraFrustum(left, right, bottom, top, near, far);
    }
    
    d->view->update();
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
