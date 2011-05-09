/* dtkVrSlave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 10:03:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:46:21 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 600
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
    d->view->update();
}
