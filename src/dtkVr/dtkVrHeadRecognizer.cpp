/* dtkVrHeadRecognizer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct 26 12:40:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 28 11:04:46 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 189
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrHeadRecognizer.h"
#include "dtkVrHeadRecognizer_p.h"
#include "dtkVrScreen.h"

#include <dtkMath/dtkMath.h>
#include <dtkMath/dtkQuaternion.h>
#include <dtkMath/dtkVector3D.h>

#include <dtkCore/dtkAbstractView.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// vrpn callbacks (Definition at EOF.)
// /////////////////////////////////////////////////////////////////

#if defined(HAVE_VRPN)
void VRPN_CALLBACK vrpn_head_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback);
void VRPN_CALLBACK vrpn_head_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback);
void VRPN_CALLBACK vrpn_head_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback);
#endif

// /////////////////////////////////////////////////////////////////
// dtkVrHeadRecognizerPrivate
// /////////////////////////////////////////////////////////////////

void dtkVrHeadRecognizerPrivate::run(void)
{
#if defined(HAVE_VRPN)
    vrpn_FILE_CONNECTIONS_SHOULD_PRELOAD = false;
    vrpn_FILE_CONNECTIONS_SHOULD_ACCUMULATE = false;

    this->analog = new vrpn_Analog_Remote(url.toString().toAscii().constData());
    this->button = new vrpn_Button_Remote(url.toString().toAscii().constData());
    this->tracker = new vrpn_Tracker_Remote(url.toString().toAscii().constData());

    if (!this->analog || !this->button || !this->tracker) {
        qDebug() << "Error connecting to server";
        return;
    }

    this->button->register_change_handler(this, vrpn_head_recognizer_handle_button);
    this->analog->register_change_handler(this, vrpn_head_recognizer_handle_analog);
    this->tracker->register_change_handler(this, vrpn_head_recognizer_handle_tracker);

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

void dtkVrHeadRecognizerPrivate::stop(void)
{
    this->running = false;
}

#if defined(HAVE_VRPN)

void dtkVrHeadRecognizerPrivate::handle_button(const vrpn_BUTTONCB callback)
{
    callback.state
        ? emit buttonPressed(callback.button)
        : emit buttonReleased(callback.button);
}

void dtkVrHeadRecognizerPrivate::handle_analog(const vrpn_ANALOGCB callback)
{
    Q_UNUSED(callback);
}

void dtkVrHeadRecognizerPrivate::handle_tracker(const vrpn_TRACKERCB callback)
{
    if(callback.sensor == 0) {
        this->head_position[0] = callback.pos[0];
        this->head_position[1] = callback.pos[1];
        this->head_position[2] = callback.pos[2];

        emit moved();
    }
}

#endif

// /////////////////////////////////////////////////////////////////
// dtkVrHeadRecognizer
// /////////////////////////////////////////////////////////////////

dtkVrHeadRecognizer::dtkVrHeadRecognizer(void) : QObject(), d(new dtkVrHeadRecognizerPrivate)
{
    d->receiver = NULL;
    d->q = this;
    d->running = false;
    d->activated = true;

    d->last = dtkVector3D<double>(0.0, 0.0, 0.0);

    connect(d, SIGNAL(moved()), this, SLOT(onMoved()));
    connect(d, SIGNAL(buttonPressed(int)), this, SLOT(onButtonPressed(int)));
    connect(d, SIGNAL(buttonReleased(int)), this, SLOT(onButtonReleased(int)));
}

dtkVrHeadRecognizer::~dtkVrHeadRecognizer(void)
{
    delete d;

    d = NULL;
}

void dtkVrHeadRecognizer::setReceiver(dtkAbstractView *receiver)
{
    d->receiver = receiver;
}

void dtkVrHeadRecognizer::startConnection(const QUrl& server)
{
    d->running = true;
    d->url = server;

    d->start();
}

void dtkVrHeadRecognizer::stopConnection(void)
{
    d->stop();
}

void dtkVrHeadRecognizer::onMoved(void)
{
    if(!d->activated || !d->receiver)
        return;

    double x =  d->head_position[0];
    double y =  d->head_position[2];
    double z = -d->head_position[1];

    dtkVector3D<double> f_art = dtkVector3D<double>(
        (   dtkVrScreen::screens[4][1][0] +    dtkVrScreen::screens[4][0][0]) / 2,
        (-1*dtkVrScreen::screens[4][2][2] + -1*dtkVrScreen::screens[4][1][2]) / 2,
            dtkVrScreen::screens[4][0][1]);

    dtkVector3D<double> z_art = dtkVector3D<double>(0, f_art[1], 0);
    dtkVector3D<double> p_art = dtkVector3D<double>(x, y, z);
    dtkVector3D<double> d_art = p_art - d->last;

    if(d_art.norm()/d->last.norm() < 0.01)
        return;

    double camera_up[3];
    double camera_position[3];
    double camera_focalpnt[3];
    
    d->receiver->cameraUp(camera_up);
    d->receiver->cameraPosition(camera_position);
    d->receiver->cameraFocalPoint(camera_focalpnt);

    dtkVector3D<double> u_xtk = dtkVector3D<double>(camera_up[0], camera_up[1], camera_up[2]);
    dtkVector3D<double> p_xtk = dtkVector3D<double>(camera_position[0], camera_position[1], camera_position[2]);
    dtkVector3D<double> f_xtk = dtkVector3D<double>(camera_focalpnt[0], camera_focalpnt[1], camera_focalpnt[2]);

    dtkVector3D<double> l = dtkVector3D<double>(1.0, 0.0, 0.0);
    dtkVector3D<double> m = dtkVector3D<double>(0.0, 1.0, 0.0);
    dtkVector3D<double> n = dtkVector3D<double>(0.0, 0.0, 1.0);
    dtkVector3D<dtkVector3D<double> > xtk_in_xtk = dtkVector3D<dtkVector3D<double> >(l, m, n);
    
    dtkVector3D<double> j = u_xtk;
    dtkVector3D<double> k = p_xtk-f_xtk;
    dtkVector3D<double> i = j%k;
    dtkVector3D<dtkVector3D<double> > cam_in_xtk = dtkVector3D<dtkVector3D<double> >(i.unit(), j.unit(), k.unit());
    
    dtkMatrixSquared<double> cam_to_xtk = dtkChangeOfBasis(cam_in_xtk, xtk_in_xtk);
    dtkMatrixSquared<double> xtk_to_cam = dtkChangeOfBasis(xtk_in_xtk, cam_in_xtk);

    dtkVector3D<double> d_xtk = cam_to_xtk*d_art;
    dtkVector3D<double> c_xtk = ((p_xtk - f_xtk).norm() / (z_art - f_art).norm()) * d_xtk + p_xtk;
    
    d->receiver->setCameraPosition(c_xtk[0], c_xtk[1], c_xtk[2]);
    d->receiver->update();

    d->last = p_art;
}

void dtkVrHeadRecognizer::onButtonPressed(int)
{
    if(!d->receiver)
        return;

    // d->activated = true;

    // d->receiver->disableInteraction();
}

void dtkVrHeadRecognizer::onButtonReleased(int)
{
    if(!d->receiver)
        return;

    // d->activated = false;

    // d->receiver->enableInteraction();
}

// /////////////////////////////////////////////////////////////////
// vrpn callbacks
// /////////////////////////////////////////////////////////////////

#if defined(HAVE_VRPN)

void VRPN_CALLBACK vrpn_head_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback)
{
    if(dtkVrHeadRecognizerPrivate *recognizer = static_cast<dtkVrHeadRecognizerPrivate *>(data))
        recognizer->handle_button(callback);
}

void VRPN_CALLBACK vrpn_head_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback)
{
    if(dtkVrHeadRecognizerPrivate *recognizer = static_cast<dtkVrHeadRecognizerPrivate *>(data))
        recognizer->handle_analog(callback);
}

void VRPN_CALLBACK vrpn_head_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback)
{
    if(dtkVrHeadRecognizerPrivate *recognizer = static_cast<dtkVrHeadRecognizerPrivate *>(data))
        recognizer->handle_tracker(callback);
}

#endif
