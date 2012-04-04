/* dtkVrTrackerVrpn.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 20:32:08 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 11:03:42 2012 (+0200)
 *           By: tkloczko
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrTrackerVrpn.h"

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

void VRPN_CALLBACK vrpn_tracker_handle_button(void *data, const vrpn_BUTTONCB callback);
void VRPN_CALLBACK vrpn_tracker_handle_analog(void *data, const vrpn_ANALOGCB callback);
void VRPN_CALLBACK vrpn_tracker_handle_tracker(void *data, const vrpn_TRACKERCB callback);

// /////////////////////////////////////////////////////////////////
// dtkVrTrackerVrpnPrivate
// /////////////////////////////////////////////////////////////////

class dtkVrTrackerVrpnPrivate : public QThread
{
public:
    void run(void);
    void stop(void);

    void handle_button(const vrpn_BUTTONCB callback);
    void handle_analog(const vrpn_ANALOGCB callback);
    void handle_tracker(const vrpn_TRACKERCB callback);

public:
    bool running;

    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;

    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler> axes_handlers_1;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler> axes_handlers_2;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler> axes_handlers_3;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler> axes_handlers_4;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler> axes_handlers_5;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler> axes_handlers_6;

    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler> position_handlers_1;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler> position_handlers_2;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler> position_handlers_3;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler> position_handlers_4;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler> position_handlers_5;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler> position_handlers_6;

    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler> orientation_handlers_1;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler> orientation_handlers_2;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler> orientation_handlers_3;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler> orientation_handlers_4;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler> orientation_handlers_5;
    QList<dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler> orientation_handlers_6;

    QUrl url;

    dtkVrTrackerVrpn *q;
};

void dtkVrTrackerVrpnPrivate::run(void)
{
    vrpn_FILE_CONNECTIONS_SHOULD_PRELOAD = false;
    vrpn_FILE_CONNECTIONS_SHOULD_ACCUMULATE = false;

    this->analog = new vrpn_Analog_Remote(url.toString().toAscii().constData());
    this->button = new vrpn_Button_Remote(url.toString().toAscii().constData());
    this->tracker = new vrpn_Tracker_Remote(url.toString().toAscii().constData());

    if (!this->analog || !this->button || !this->tracker) {
        dtkError() << "Error connecting to server";
        return;
    }

    this->button->register_change_handler(this, vrpn_tracker_handle_button);
    this->analog->register_change_handler(this, vrpn_tracker_handle_analog);
    this->tracker->register_change_handler(this, vrpn_tracker_handle_tracker);

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

void dtkVrTrackerVrpnPrivate::stop(void)
{
    this->running = false;
}

void dtkVrTrackerVrpnPrivate::handle_button(const vrpn_BUTTONCB callback)
{
    switch(callback.button) {
    case 0: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton0) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton0); break;
    case 1: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton1) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton1); break;
    case 2: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton2) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton2); break;
    case 3: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton3) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton3); break;
    case 4: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton4) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton4); break;
    case 5: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton5) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton5); break;
    case 6: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton6) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton6); break;
    case 7: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton7) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton7); break;
    case 8: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton8) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton8); break;
    case 9: callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton9) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButton9); break;
    default:
        callback.state ? emit q->buttonPressed(dtkVrTrackerVrpn::dtkVrTrackerVrpnButtonUndefined) : emit q->buttonReleased(dtkVrTrackerVrpn::dtkVrTrackerVrpnButtonUndefined);
        break;
    };
}

void dtkVrTrackerVrpnPrivate::handle_analog(const vrpn_ANALOGCB callback)
{
    if (callback.num_channel >= 10) {
        dtkWarn() << "Only 10 analog channels are handled by dtkVrTrackerVrpn. Skipping all axes";
        return;
    }

    int maxId = 0; double maxVal = -1; bool allNull = true;

    for (int i = 0; i < callback.num_channel; i++) {
        if (fabs(callback.channel[i]) > maxVal) {
            maxId = i;
            maxVal = fabs(callback.channel[i]);
        }
        if (callback.channel[i]) allNull = false;
    }

    if (allNull) for (int i = 0; i < callback.num_channel; i++)  {
        q->runAxesHandlers1(i, 0);
        q->runAxesHandlers2(i, 0);
        q->runAxesHandlers3(i, 0);
        q->runAxesHandlers4(i, 0);
        q->runAxesHandlers5(i, 0);
        q->runAxesHandlers6(i, 0);

    } else {
        q->runAxesHandlers1(maxId, callback.channel[maxId]);
        q->runAxesHandlers2(maxId, callback.channel[maxId]);
        q->runAxesHandlers3(maxId, callback.channel[maxId]);
        q->runAxesHandlers4(maxId, callback.channel[maxId]);
        q->runAxesHandlers5(maxId, callback.channel[maxId]);
        q->runAxesHandlers6(maxId, callback.channel[maxId]);
    }
}

void dtkVrTrackerVrpnPrivate::handle_tracker(const vrpn_TRACKERCB callback)
{
    switch(callback.sensor) {
    case 0:
        q->runPositionHandlers1(callback.pos[0], callback.pos[1], callback.pos[2]);
        q->runOrientationHandlers1(callback.quat[0], callback.quat[1], callback.quat[2], callback.quat[3]);
        break;
    case 1:
        q->runPositionHandlers2(callback.pos[0], callback.pos[1], callback.pos[2]);
        q->runOrientationHandlers2(callback.quat[0], callback.quat[1], callback.quat[2], callback.quat[3]);
        break;
    case 2:
        q->runPositionHandlers3(callback.pos[0], callback.pos[1], callback.pos[2]);
        q->runOrientationHandlers3(callback.quat[0], callback.quat[1], callback.quat[2], callback.quat[3]);
        break;
    case 3:
        q->runPositionHandlers4(callback.pos[0], callback.pos[1], callback.pos[2]);
        q->runOrientationHandlers4(callback.quat[0], callback.quat[1], callback.quat[2], callback.quat[3]);
        break;
    case 4:
        q->runPositionHandlers5(callback.pos[0], callback.pos[1], callback.pos[2]);
        q->runOrientationHandlers5(callback.quat[0], callback.quat[1], callback.quat[2], callback.quat[3]);
        break;
    case 5:
        q->runPositionHandlers6(callback.pos[0], callback.pos[1], callback.pos[2]);
        q->runOrientationHandlers6(callback.quat[0], callback.quat[1], callback.quat[2], callback.quat[3]);
        break;
    };
}

// /////////////////////////////////////////////////////////////////
// dtkVrTrackerVrpn
// /////////////////////////////////////////////////////////////////

dtkVrTrackerVrpn::dtkVrTrackerVrpn(void) : dtkVrTracker(), d(new dtkVrTrackerVrpnPrivate)
{
    d->q = this;
    d->running = false;
}

dtkVrTrackerVrpn::~dtkVrTrackerVrpn(void)
{
    delete d;

    d = NULL;
}

void dtkVrTrackerVrpn::registerAxesHandler1(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler)
{
    d->axes_handlers_1 << handler;
}

void dtkVrTrackerVrpn::registerAxesHandler2(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler)
{
    d->axes_handlers_2 << handler;
}

void dtkVrTrackerVrpn::registerAxesHandler3(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler)
{
    d->axes_handlers_3 << handler;
}

void dtkVrTrackerVrpn::registerAxesHandler4(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler)
{
    d->axes_handlers_4 << handler;
}

void dtkVrTrackerVrpn::registerAxesHandler5(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler)
{
    d->axes_handlers_5 << handler;
}

void dtkVrTrackerVrpn::registerAxesHandler6(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler)
{
    d->axes_handlers_6 << handler;
}

void dtkVrTrackerVrpn::registerPositionHandler1(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler)
{
    d->position_handlers_1 << handler;
}

void dtkVrTrackerVrpn::registerPositionHandler2(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler)
{
    d->position_handlers_2 << handler;
}

void dtkVrTrackerVrpn::registerPositionHandler3(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler)
{
    d->position_handlers_3 << handler;
}

void dtkVrTrackerVrpn::registerPositionHandler4(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler)
{
    d->position_handlers_4 << handler;
}

void dtkVrTrackerVrpn::registerPositionHandler5(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler)
{
    d->position_handlers_5 << handler;
}

void dtkVrTrackerVrpn::registerPositionHandler6(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler)
{
    d->position_handlers_6 << handler;
}

void dtkVrTrackerVrpn::registerOrientationHandler1(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler)
{
    d->orientation_handlers_1 << handler;
}

void dtkVrTrackerVrpn::registerOrientationHandler2(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler)
{
    d->orientation_handlers_2 << handler;
}

void dtkVrTrackerVrpn::registerOrientationHandler3(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler)
{
    d->orientation_handlers_3 << handler;
}

void dtkVrTrackerVrpn::registerOrientationHandler4(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler)
{
    d->orientation_handlers_4 << handler;
}

void dtkVrTrackerVrpn::registerOrientationHandler5(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler)
{
    d->orientation_handlers_5 << handler;
}

void dtkVrTrackerVrpn::registerOrientationHandler6(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler)
{
    d->orientation_handlers_6 << handler;
}

QString dtkVrTrackerVrpn::description(void) const
{
    return "dtkVrTrackerVrpn";
}

void dtkVrTrackerVrpn::startConnection(const QUrl& server)
{
    d->running = true;
    d->url = server;

    d->start();
}

void dtkVrTrackerVrpn::stopConnection(void)
{
    d->stop();
}

void dtkVrTrackerVrpn::runAxesHandlers1(int axis, float angle)
{
    foreach(dtkVrTrackerVrpnAxesHandler handler, d->axes_handlers_1)
        (handler)(axis, angle);
}

void dtkVrTrackerVrpn::runAxesHandlers2(int axis, float angle)
{
    foreach(dtkVrTrackerVrpnAxesHandler handler, d->axes_handlers_2)
        (handler)(axis, angle);
}

void dtkVrTrackerVrpn::runAxesHandlers3(int axis, float angle)
{
    foreach(dtkVrTrackerVrpnAxesHandler handler, d->axes_handlers_3)
        (handler)(axis, angle);
}

void dtkVrTrackerVrpn::runAxesHandlers4(int axis, float angle)
{
    foreach(dtkVrTrackerVrpnAxesHandler handler, d->axes_handlers_4)
        (handler)(axis, angle);
}

void dtkVrTrackerVrpn::runAxesHandlers5(int axis, float angle)
{
    foreach(dtkVrTrackerVrpnAxesHandler handler, d->axes_handlers_5)
        (handler)(axis, angle);
}

void dtkVrTrackerVrpn::runAxesHandlers6(int axis, float angle)
{
    foreach(dtkVrTrackerVrpnAxesHandler handler, d->axes_handlers_6)
        (handler)(axis, angle);
}

void dtkVrTrackerVrpn::runPositionHandlers1(float x, float y, float z)
{
    foreach(dtkVrTrackerVrpnPositionHandler handler, d->position_handlers_1)
        (handler)(x, y, z);
}

void dtkVrTrackerVrpn::runPositionHandlers2(float x, float y, float z)
{
    foreach(dtkVrTrackerVrpnPositionHandler handler, d->position_handlers_2)
        (handler)(x, y, z);
}

void dtkVrTrackerVrpn::runPositionHandlers3(float x, float y, float z)
{
    foreach(dtkVrTrackerVrpnPositionHandler handler, d->position_handlers_3)
        (handler)(x, y, z);
}

void dtkVrTrackerVrpn::runPositionHandlers4(float x, float y, float z)
{
    foreach(dtkVrTrackerVrpnPositionHandler handler, d->position_handlers_4)
        (handler)(x, y, z);
}

void dtkVrTrackerVrpn::runPositionHandlers5(float x, float y, float z)
{
    foreach(dtkVrTrackerVrpnPositionHandler handler, d->position_handlers_5)
        (handler)(x, y, z);
}

void dtkVrTrackerVrpn::runPositionHandlers6(float x, float y, float z)
{
    foreach(dtkVrTrackerVrpnPositionHandler handler, d->position_handlers_6)
        (handler)(x, y, z);
}

void dtkVrTrackerVrpn::runOrientationHandlers1(float q0, float q1, float q2, float q3)
{
    foreach(dtkVrTrackerVrpnOrientationHandler handler, d->orientation_handlers_1)
        (handler)(q0, q1, q2, q3);
}

void dtkVrTrackerVrpn::runOrientationHandlers2(float q0, float q1, float q2, float q3)
{
    foreach(dtkVrTrackerVrpnOrientationHandler handler, d->orientation_handlers_2)
        (handler)(q0, q1, q2, q3);
}

void dtkVrTrackerVrpn::runOrientationHandlers3(float q0, float q1, float q2, float q3)
{
    foreach(dtkVrTrackerVrpnOrientationHandler handler, d->orientation_handlers_3)
        (handler)(q0, q1, q2, q3);
}

void dtkVrTrackerVrpn::runOrientationHandlers4(float q0, float q1, float q2, float q3)
{
    foreach(dtkVrTrackerVrpnOrientationHandler handler, d->orientation_handlers_4)
        (handler)(q0, q1, q2, q3);
}

void dtkVrTrackerVrpn::runOrientationHandlers5(float q0, float q1, float q2, float q3)
{
    foreach(dtkVrTrackerVrpnOrientationHandler handler, d->orientation_handlers_5)
        (handler)(q0, q1, q2, q3);
}

void dtkVrTrackerVrpn::runOrientationHandlers6(float q0, float q1, float q2, float q3)
{
    foreach(dtkVrTrackerVrpnOrientationHandler handler, d->orientation_handlers_6)
        (handler)(q0, q1, q2, q3);
}

// /////////////////////////////////////////////////////////////////
// vrpn callbacks
// /////////////////////////////////////////////////////////////////

void VRPN_CALLBACK vrpn_tracker_handle_button(void *data, const vrpn_BUTTONCB callback)
{
    if(dtkVrTrackerVrpnPrivate *tracker = static_cast<dtkVrTrackerVrpnPrivate *>(data))
        tracker->handle_button(callback);
}

void VRPN_CALLBACK vrpn_tracker_handle_analog(void *data, const vrpn_ANALOGCB callback)
{
    if(dtkVrTrackerVrpnPrivate *tracker = static_cast<dtkVrTrackerVrpnPrivate *>(data))
        tracker->handle_analog(callback);
}

void VRPN_CALLBACK vrpn_tracker_handle_tracker(void *data, const vrpn_TRACKERCB callback)
{
    if(dtkVrTrackerVrpnPrivate *tracker = static_cast<dtkVrTrackerVrpnPrivate *>(data))
        tracker->handle_tracker(callback);
}
