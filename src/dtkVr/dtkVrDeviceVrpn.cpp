/* dtkVrDeviceVrpn.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 13:44:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 16:35:02 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 50
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrDeviceVrpn.h"

#include <dtkCore/dtkLog.h>

#include <vrpn_Shared.h>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <vrpn_Tracker.h>
#include <vrpn_FileConnection.h>

// /////////////////////////////////////////////////////////////////
// dtkVrDeviceVrpnPrivate
// /////////////////////////////////////////////////////////////////

class dtkVrDeviceVrpnPrivate : public QThread
{
public:
    void run(void);
    void stop(void);

public:
    bool running;

    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;

    QList<dtkVrDeviceVrpn::dtkVrDeviceVrpnPositionHandler> position_handlers;
    QList<dtkVrDeviceVrpn::dtkVrDeviceVrpnOrientationHandler> orientation_handlers;

    QUrl url;
};

void dtkVrDeviceVrpnPrivate::run(void)
{
    vrpn_FILE_CONNECTIONS_SHOULD_PRELOAD = false;
    vrpn_FILE_CONNECTIONS_SHOULD_ACCUMULATE = false;

    this->analog = new vrpn_Analog_Remote("");
    this->button = new vrpn_Button_Remote("");
    this->tracker = new vrpn_Tracker_Remote("");

    if (!this->analog || !this->button || !this->tracker) {
        dtkWarning() << "Error connecting to tracker";
        return;
    }

    while(this->running) {
        this->analog->mainloop();
        this->button->mainloop();
        this->tracker->mainloop();
        vrpn_SleepMsecs(1);
    }

    delete this->analog;
    delete this->button;
    delete this->tracker;
}

void dtkVrDeviceVrpnPrivate::stop(void)
{
    this->running = false;
}

// /////////////////////////////////////////////////////////////////
// dtkVrDeviceVrpn
// /////////////////////////////////////////////////////////////////

dtkVrDeviceVrpn::dtkVrDeviceVrpn(void) : dtkVrDevice(), d(new dtkVrDeviceVrpnPrivate)
{
    d->running = false;
}

dtkVrDeviceVrpn::~dtkVrDeviceVrpn(void)
{
    d->stop();
    d->wait();

    delete d;

    d = NULL;
}

void dtkVrDeviceVrpn::registerPositionHandler(dtkVrDeviceVrpn::dtkVrDeviceVrpnPositionHandler handler)
{
    d->position_handlers << handler;
}

void dtkVrDeviceVrpn::registerOrientationHandler(dtkVrDeviceVrpn::dtkVrDeviceVrpnOrientationHandler handler)
{
    d->orientation_handlers << handler;
}

QString dtkVrDeviceVrpn::description(void) const
{
    return QString();
}

void dtkVrDeviceVrpn::startConnection(const QUrl& server)
{
    d->url = server;

    d->start();
}

void dtkVrDeviceVrpn::stopConnection(void)
{
    d->stop();
}

void dtkVrDeviceVrpn::runPositionHandlers(float x, float y, float z)
{
    
}

void dtkVrDeviceVrpn::runOrientationHandlers(float q0, float q1, float q2, float q3)
{

}
