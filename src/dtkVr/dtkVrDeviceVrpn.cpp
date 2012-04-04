/* dtkVrDeviceVrpn.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 13:44:22 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 11:03:05 2012 (+0200)
 *           By: tkloczko
 *     Update #: 144
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrDeviceVrpn.h"

#include <vrpn_Shared.h>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <vrpn_Tracker.h>
#include <vrpn_FileConnection.h>
#include <quat.h>

#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// vrpn callbacks (Definition at EOF.)
// /////////////////////////////////////////////////////////////////

void VRPN_CALLBACK vrpn_device_handle_button(void *data, const vrpn_BUTTONCB callback);
void VRPN_CALLBACK vrpn_device_handle_analog(void *data, const vrpn_ANALOGCB callback);
void VRPN_CALLBACK vrpn_device_handle_tracker(void *data, const vrpn_TRACKERCB callback);

// /////////////////////////////////////////////////////////////////
// dtkVrDeviceVrpnPrivate
// /////////////////////////////////////////////////////////////////

class dtkVrDeviceVrpnPrivate : public QThread
{
public:
    void run(void);
    void stop(void);

    void handle_button(const vrpn_BUTTONCB callback);
    void handle_analog(const vrpn_ANALOGCB callback);
    void handle_tracker(const vrpn_TRACKERCB callback);

public:
    bool running;

    int sensor;

    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;

    QList<dtkVrDeviceVrpn::dtkVrDeviceVrpnAxesHandler> axes_handlers;
    QList<dtkVrDeviceVrpn::dtkVrDeviceVrpnPositionHandler> position_handlers;
    QList<dtkVrDeviceVrpn::dtkVrDeviceVrpnOrientationHandler> orientation_handlers;

    QUrl url;

    dtkVrDeviceVrpn *q;
};

void dtkVrDeviceVrpnPrivate::run(void)
{
    vrpn_FILE_CONNECTIONS_SHOULD_PRELOAD = false;
    vrpn_FILE_CONNECTIONS_SHOULD_ACCUMULATE = false;

    this->analog = new vrpn_Analog_Remote(url.path().toAscii().constData());
    this->button = new vrpn_Button_Remote(url.path().toAscii().constData());
    this->tracker = new vrpn_Tracker_Remote(url.path().toAscii().constData());

    if (!this->analog || !this->button || !this->tracker) {
        dtkError() << "Error connecting to server";
        return;
    }

    this->button->register_change_handler(this, vrpn_device_handle_button);
    this->analog->register_change_handler(this, vrpn_device_handle_analog);
    this->tracker->register_change_handler(this, vrpn_device_handle_tracker);

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

void dtkVrDeviceVrpnPrivate::handle_button(const vrpn_BUTTONCB callback)
{
    switch(callback.button) {
    case 0: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton0) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton0); break;
    case 1: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton1) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton1); break;
    case 2: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton2) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton2); break;
    case 3: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton3) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton3); break;
    case 4: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton4) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton4); break;
    case 5: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton5) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton5); break;
    case 6: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton6) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton6); break;
    case 7: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton7) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton7); break;
    case 8: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton8) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton8); break;
    case 9: callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton9) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButton9); break;
    default:
        callback.state ? emit q->buttonPressed(dtkVrDeviceVrpn::dtkVrDeviceVrpnButtonUndefined) : emit q->buttonReleased(dtkVrDeviceVrpn::dtkVrDeviceVrpnButtonUndefined);
        break;
    };
}

void dtkVrDeviceVrpnPrivate::handle_analog(const vrpn_ANALOGCB callback)
{
    q->runPositionHandlers(callback.channel[0], callback.channel[1], callback.channel[2]);

    q_type quat; q_from_euler(quat,
        Q_DEG_TO_RAD(callback.channel[3]),
        Q_DEG_TO_RAD(callback.channel[4]),
        Q_DEG_TO_RAD(callback.channel[5]));

    q->runOrientationHandlers(quat[0], quat[1], quat[2], quat[3]);
}

void dtkVrDeviceVrpnPrivate::handle_tracker(const vrpn_TRACKERCB callback)
{
    if(callback.sensor != this->sensor)
        return;

    q->runPositionHandlers(
        callback.pos[0],
        callback.pos[1],
        callback.pos[2]);

    q->runOrientationHandlers(
        callback.quat[0],
        callback.quat[1],
        callback.quat[2],
        callback.quat[3]);
}

// /////////////////////////////////////////////////////////////////
// dtkVrDeviceVrpn
// /////////////////////////////////////////////////////////////////

dtkVrDeviceVrpn::dtkVrDeviceVrpn(void) : dtkVrDevice(), d(new dtkVrDeviceVrpnPrivate)
{
    d->q = this;
    d->sensor = -1,
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
    return "dtkVrDeviceVrpn";
}

void dtkVrDeviceVrpn::startConnection(const QUrl& server)
{
    d->running = true;
    d->url = server;
    d->sensor = server.port();

    d->start();
}

void dtkVrDeviceVrpn::stopConnection(void)
{
    d->stop();
}

void dtkVrDeviceVrpn::runPositionHandlers(float x, float y, float z)
{
    foreach(dtkVrDeviceVrpn::dtkVrDeviceVrpnPositionHandler handler, d->position_handlers)
        (handler)(x, y, z);
}

void dtkVrDeviceVrpn::runOrientationHandlers(float q0, float q1, float q2, float q3)
{
    foreach(dtkVrDeviceVrpn::dtkVrDeviceVrpnOrientationHandler handler, d->orientation_handlers)
        (handler)(q0, q1, q2, q3);
}

// /////////////////////////////////////////////////////////////////
// vrpn callbacks
// /////////////////////////////////////////////////////////////////

void VRPN_CALLBACK vrpn_device_handle_button(void *data, const vrpn_BUTTONCB callback)
{
    if(dtkVrDeviceVrpnPrivate *device = static_cast<dtkVrDeviceVrpnPrivate *>(data))
        device->handle_button(callback);
}

void VRPN_CALLBACK vrpn_device_handle_analog(void *data, const vrpn_ANALOGCB callback)
{
    if(dtkVrDeviceVrpnPrivate *device = static_cast<dtkVrDeviceVrpnPrivate *>(data))
        device->handle_analog(callback);
}

void VRPN_CALLBACK vrpn_device_handle_tracker(void *data, const vrpn_TRACKERCB callback)
{
    if(dtkVrDeviceVrpnPrivate *device = static_cast<dtkVrDeviceVrpnPrivate *>(data))
        device->handle_tracker(callback);
}
