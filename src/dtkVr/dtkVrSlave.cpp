/* dtkVrSlave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 16 22:29:31 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 180
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

class dtkVrSlavePrivate
{
public:
    dtkVrScreen *screen;

    dtkAbstractView *view;
};

dtkVrSlave::dtkVrSlave(void) : dtkVrProcess(), d(new dtkVrSlavePrivate)
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

void dtkVrSlave::setView(dtkAbstractView *view)
{
    d->view = view;
}

void dtkVrSlave::process(void)
{
    // this->setupCameraLookAt
    // this->setupCameraFrustum
    
    d->view->update();
}

void dtkVrSlave::setupCameraLookAt(const QVector3D& eye, const QVector3D& center, const QVector3D& up)
{
    if (d->view)
        d->view->setupCameraLookAt(eye, center, up);
}

void dtkVrSlave::setupCameraFrustum(double left, double right, double bottom, double top, double near, double far)
{
    if (d->view)
        d->view->setupCameraFrustum(left, right, bottom, top, near, far);
}
