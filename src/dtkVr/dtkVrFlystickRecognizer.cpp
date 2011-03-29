/* dtkVrFlystickRecognizer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  7 10:04:45 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  7 14:21:01 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrFlystickRecognizer.h"
#include "dtkVrFlystickRecognizer_p.h"
#include "dtkVrScreen.h"

#include <dtkMath/dtkMath.h>
#include <dtkMath/dtkQuaternion.h>
#include <dtkMath/dtkVector3D.h>

#include <dtkCore/dtkGlobal.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// vrpn callbacks (Definition at EOF.)
// /////////////////////////////////////////////////////////////////

#if defined(DTK_WRAP_VRPN)
void VRPN_CALLBACK vrpn_flystick_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback);
void VRPN_CALLBACK vrpn_flystick_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback);
void VRPN_CALLBACK vrpn_flystick_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback);
#endif

// /////////////////////////////////////////////////////////////////
// dtkVrFlystickRecognizerPrivate
// /////////////////////////////////////////////////////////////////

void dtkVrFlystickRecognizerPrivate::run(void)
{
#if defined(DTK_WRAP_VRPN)
    vrpn_FILE_CONNECTIONS_SHOULD_PRELOAD = false;
    vrpn_FILE_CONNECTIONS_SHOULD_ACCUMULATE = false;

    this->analog = new vrpn_Analog_Remote(url.toString().toAscii().constData());
    this->button = new vrpn_Button_Remote(url.toString().toAscii().constData());
    this->tracker = new vrpn_Tracker_Remote(url.toString().toAscii().constData());

    if (!this->analog || !this->button || !this->tracker) {
        qDebug() << "Error connecting to server";
        return;
    }

    this->button->register_change_handler(this, vrpn_flystick_recognizer_handle_button);
    this->analog->register_change_handler(this, vrpn_flystick_recognizer_handle_analog);
    this->tracker->register_change_handler(this, vrpn_flystick_recognizer_handle_tracker);

    while(this->running) {
        this->analog->mainloop();
        this->button->mainloop();
        this->tracker->mainloop();
        vrpn_SleepMsecs(10);
    }

    delete this->analog;
    delete this->button;
    delete this->tracker;
#endif
}

void dtkVrFlystickRecognizerPrivate::stop(void)
{
    this->running = false;
}

#if defined(DTK_WRAP_VRPN)

void dtkVrFlystickRecognizerPrivate::handle_button(const vrpn_BUTTONCB callback)
{
    callback.state
        ? emit buttonPressed(callback.button)
        : emit buttonReleased(callback.button);
}

void dtkVrFlystickRecognizerPrivate::handle_analog(const vrpn_ANALOGCB callback)
{
    Q_UNUSED(callback);
}

void dtkVrFlystickRecognizerPrivate::handle_tracker(const vrpn_TRACKERCB callback)
{
    if(callback.sensor == 5) {
        this->flystick_position[0] = callback.pos[0];
        this->flystick_position[1] = callback.pos[1];
        this->flystick_position[2] = callback.pos[2];

        emit moved();
    }
}

#endif

// /////////////////////////////////////////////////////////////////
// dtkVrFlystickRecognizer
// /////////////////////////////////////////////////////////////////

dtkVrFlystickRecognizer::dtkVrFlystickRecognizer(void) : QObject(), d(new dtkVrFlystickRecognizerPrivate)
{
    d->q = this;
    d->running = false;
    d->activated = true;

    d->last = dtkVector3D<double>(0.0, 0.0, 0.0);

    connect(d, SIGNAL(moved()), this, SLOT(onMoved()));
    connect(d, SIGNAL(buttonPressed(int)), this, SLOT(onButtonPressed(int)));
    connect(d, SIGNAL(buttonReleased(int)), this, SLOT(onButtonReleased(int)));
}

dtkVrFlystickRecognizer::~dtkVrFlystickRecognizer(void)
{
    delete d;

    d = NULL;
}

void dtkVrFlystickRecognizer::startConnection(const QUrl& server)
{
    d->running = true;
    d->url = server;

    d->start();
}

void dtkVrFlystickRecognizer::stopConnection(void)
{
    d->stop();
}

void dtkVrFlystickRecognizer::onMoved(void)
{
    // if(!d->activated)
    //     return;

    double x =  d->flystick_position[0];
    double y =  d->flystick_position[2];
    double z = -d->flystick_position[1];
    
    qDebug() << DTK_PRETTY_FUNCTION << x << y << z;
}

void dtkVrFlystickRecognizer::onButtonPressed(int button)
{
    qDebug() << DTK_PRETTY_FUNCTION << button;

    d->activated = true;
}

void dtkVrFlystickRecognizer::onButtonReleased(int button)
{
    qDebug() << DTK_PRETTY_FUNCTION << button;

    d->activated = false;
}

// /////////////////////////////////////////////////////////////////
// vrpn callbacks
// /////////////////////////////////////////////////////////////////

#if defined(DTK_WRAP_VRPN)

void VRPN_CALLBACK vrpn_flystick_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback)
{
    if(dtkVrFlystickRecognizerPrivate *recognizer = static_cast<dtkVrFlystickRecognizerPrivate *>(data))
        recognizer->handle_button(callback);
}

void VRPN_CALLBACK vrpn_flystick_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback)
{
    if(dtkVrFlystickRecognizerPrivate *recognizer = static_cast<dtkVrFlystickRecognizerPrivate *>(data))
        recognizer->handle_analog(callback);
}

void VRPN_CALLBACK vrpn_flystick_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback)
{
    if(dtkVrFlystickRecognizerPrivate *recognizer = static_cast<dtkVrFlystickRecognizerPrivate *>(data))
        recognizer->handle_tracker(callback);
}

#endif
