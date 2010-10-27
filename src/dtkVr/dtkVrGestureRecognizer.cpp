/* dtkVrGestureRecognizer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:12:40 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 26 22:36:51 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 245
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrGestureRecognizer.h"
#include "dtkVrGestureRecognizer_p.h"

#include <dtkMath/dtkMath.h>
#include <dtkMath/dtkQuaternion.h>
#include <dtkMath/dtkVector3D.h>

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// vrpn callbacks (Definition at EOF.)
// /////////////////////////////////////////////////////////////////

void VRPN_CALLBACK vrpn_gesture_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback);
void VRPN_CALLBACK vrpn_gesture_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback);
void VRPN_CALLBACK vrpn_gesture_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback);

// /////////////////////////////////////////////////////////////////
// dtkVrGestureRecognizerPrivate
// /////////////////////////////////////////////////////////////////

void dtkVrGestureRecognizerPrivate::run(void)
{
    vrpn_FILE_CONNECTIONS_SHOULD_PRELOAD = false;
    vrpn_FILE_CONNECTIONS_SHOULD_ACCUMULATE = false;

    this->analog = new vrpn_Analog_Remote(url.toString().toAscii().constData());
    this->button = new vrpn_Button_Remote(url.toString().toAscii().constData());
    this->tracker = new vrpn_Tracker_Remote(url.toString().toAscii().constData());

    if (!this->analog || !this->button || !this->tracker) {
        qDebug() << "Error connecting to server";
        return;
    }

    this->button->register_change_handler(this, vrpn_gesture_recognizer_handle_button);
    this->analog->register_change_handler(this, vrpn_gesture_recognizer_handle_analog);
    this->tracker->register_change_handler(this, vrpn_gesture_recognizer_handle_tracker);

    while(this->running) {
        this->analog->mainloop();
        this->button->mainloop();
        this->tracker->mainloop();
        vrpn_SleepMsecs(10);
    }

    delete this->analog;
    delete this->button;
    delete this->tracker;
}

void dtkVrGestureRecognizerPrivate::stop(void)
{
    this->running = false;
}

void dtkVrGestureRecognizerPrivate::handle_button(const vrpn_BUTTONCB callback)
{
    Q_UNUSED(callback);
}

void dtkVrGestureRecognizerPrivate::handle_analog(const vrpn_ANALOGCB callback)
{
    Q_UNUSED(callback);
}

void dtkVrGestureRecognizerPrivate::handle_tracker(const vrpn_TRACKERCB callback)
{
    if(callback.sensor == 100) {
        this->right_hand_position[0] = callback.pos[0];
        this->right_hand_position[1] = callback.pos[1];
        this->right_hand_position[2] = callback.pos[2];
    }

    if(callback.sensor == 1001) {
        this->right_index_position[0] = this->right_hand_position[0] + callback.pos[0];
        this->right_index_position[1] = this->right_hand_position[1] + callback.pos[1];
        this->right_index_position[2] = this->right_hand_position[2] + callback.pos[2];
    }

    if(callback.sensor == 1002) {
        this->right_major_position[0] = this->right_hand_position[0] + callback.pos[0];
        this->right_major_position[1] = this->right_hand_position[1] + callback.pos[1];
        this->right_major_position[2] = this->right_hand_position[2] + callback.pos[2];
    }

    if(callback.sensor == 101) {
        this->left_hand_position[0] = callback.pos[0];
        this->left_hand_position[1] = callback.pos[1];
        this->left_hand_position[2] = callback.pos[2];
    }

    if(callback.sensor == 1011) {
        this->left_index_position[0] = this->left_hand_position[0] + callback.pos[0];
        this->left_index_position[1] = this->left_hand_position[1] + callback.pos[1];
        this->left_index_position[2] = this->left_hand_position[2] + callback.pos[2];
    }

    if(callback.sensor == 1012) {
        this->left_major_position[0] = this->left_hand_position[0] + callback.pos[0];
        this->left_major_position[1] = this->left_hand_position[1] + callback.pos[1];
        this->left_major_position[2] = this->left_hand_position[2] + callback.pos[2];
    }

    if(callback.sensor == 1002)
        this->right_interaction = (callback.pos[0] <= 0);

    if(callback.sensor == 1012)
        this->left_interaction = (callback.pos[0] <= 0);

    if(this->left_interaction || this->right_interaction) {

        if (state == End) {
            this->left_index_start_position[0] = this->left_index_position[0];
            this->left_index_start_position[1] = this->left_index_position[1];
            this->left_index_start_position[2] = this->left_index_position[2];

            this->right_index_start_position[0] = this->right_index_position[0];
            this->right_index_start_position[1] = this->right_index_position[1];
            this->right_index_start_position[2] = this->right_index_position[2];

            state = Begin;
        }

        if (state == Begin) {

            if(this->left_interaction && this->right_interaction) {

                emit postPinchEvent(Qt::GestureStarted);

                state = Pinch;
            } else {
                
                emit postPanEvent(Qt::GestureStarted);

                state = Pan;
            }
        }

        if (state == Pan) {

            if(this->left_interaction && this->right_interaction) {

                emit postPanEvent(Qt::GestureFinished);
                emit postPinchEvent(Qt::GestureStarted);

                state = Pinch;
            }

            else if(this->left_interaction) { // Use left index to pan

                emit postPanEvent(Qt::GestureUpdated);

            } else { // Use right index to pan

                emit postSwipeEvent(Qt::GestureUpdated);

           }
        }

        if (state == Pinch) {

            if(this->left_interaction && !this->right_interaction) {

                emit postPinchEvent(Qt::GestureFinished);
                emit postPanEvent(Qt::GestureStarted);

                state = Pan;

            } else if(!this->left_interaction && this->right_interaction) {

                emit postPinchEvent(Qt::GestureFinished);
                emit postPanEvent(Qt::GestureStarted);

                state = Pan;

            } else {

                emit postPinchEvent(Qt::GestureUpdated);
            }
        }

    } else {

            
        if(state == Pinch) {
            
            state = End;
            
            emit postPinchEvent(Qt::GestureFinished);
            
        }
        
        if(state == Pan) {
            
            state = End;
            
            emit postPinchEvent(Qt::GestureFinished);
            
        }
        
        emit postClearEvent(Qt::GestureFinished);
    }
}

// /////////////////////////////////////////////////////////////////
// dtkVrGestureRecognizer
// /////////////////////////////////////////////////////////////////

dtkVrGestureRecognizer::dtkVrGestureRecognizer(void) : QObject(), d(new dtkVrGestureRecognizerPrivate)
{
    d->receiver = NULL;
    d->q = this;
    d->running = false;
    d->state = dtkVrGestureRecognizerPrivate::End;

    connect(d, SIGNAL(postPanEvent(Qt::GestureState)), this, SLOT(postPanEvent(Qt::GestureState)));
    connect(d, SIGNAL(postSwipeEvent(Qt::GestureState)), this, SLOT(postSwipeEvent(Qt::GestureState)));
    connect(d, SIGNAL(postPinchEvent(Qt::GestureState)), this, SLOT(postPinchEvent(Qt::GestureState)));
    connect(d, SIGNAL(postClearEvent(Qt::GestureState)), this, SLOT(postClearEvent(Qt::GestureState)));
}

dtkVrGestureRecognizer::~dtkVrGestureRecognizer(void)
{
    delete d;

    d = NULL;
}

void dtkVrGestureRecognizer::setReceiver(QObject *receiver)
{
    d->receiver = receiver;
}

void dtkVrGestureRecognizer::startConnection(const QUrl& server)
{
    d->running = true;
    d->url = server;

    d->start();
}

void dtkVrGestureRecognizer::stopConnection(void)
{
    d->stop();
}

void dtkVrGestureRecognizer::postPanEvent(Qt::GestureState state)
{
    if(!d->receiver)
        return;

    QPanGesture *gesture = new QPanGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);

    // QCoreApplication::postEvent(d->receiver, event);
}

void dtkVrGestureRecognizer::postSwipeEvent(Qt::GestureState state)
{
    if(!d->receiver)
        return;

    QSwipeGesture *gesture = new QSwipeGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);

    // QCoreApplication::postEvent(d->receiver, event);
}

#include <math.h>

void dtkVrGestureRecognizer::postPinchEvent(Qt::GestureState state)
{
    if(!d->receiver)
        return;

    dtkVector3D<double> s = dtkVector3D<double>(
        d->right_index_start_position[0] - d->left_index_start_position[0],
        d->right_index_start_position[2] - d->left_index_start_position[2],
      - d->right_index_start_position[1] + d->left_index_start_position[1]);

    dtkVector3D<double> u = dtkVector3D<double>(
        d->right_index_position[0] - d->left_index_position[0],
        d->right_index_position[2] - d->left_index_position[2],
      - d->right_index_position[1] + d->left_index_position[1]);

    dtkVector3D<double> i = dtkVector3D<double>(1.0, 0.0, 0.0);
    dtkVector3D<double> j = dtkVector3D<double>(0.0, 1.0, 0.0);
    dtkVector3D<double> k = dtkVector3D<double>(0.0, 0.0, 1.0);
    dtkVector3D<dtkVector3D<double> > from = dtkVector3D<dtkVector3D<double> >(i, j, k);

    dtkVector3D<double> l = dtkVector3D<double>(s[0], 0.0, s[2]).unit();
    dtkVector3D<double> m = dtkVector3D<double>(0.0, 1.0, 0.0).unit();
    dtkVector3D<double> n = (l%m).unit();
    dtkVector3D<dtkVector3D<double> > to = dtkVector3D<dtkVector3D<double> >(l, m, n);

    dtkMatrixSquared<double> t = dtkChangeOfBasis(from, to);

    dtkVector3D<double> ns = t*s;
    dtkVector3D<double> nu = t*u;

    // -- Computing scale factor --

    static qreal lastScaleFactor;

    qreal scaleFactor = nu.norm()/ns.norm();

    if(state == Qt::GestureStarted)
        lastScaleFactor = scaleFactor;

    // -- Computing rotation angle --

    static qreal lastRotationAngle;

    qreal rotationAngle = -1.0 * (acos(nu.unit() * ns.unit()) * ((ns % nu).unit() * k.unit())) * 180.0 / 3.141593;

    if(state == Qt::GestureStarted)
        lastRotationAngle = rotationAngle;

    // -- Post event --

    QPinchGesture *gesture = new QPinchGesture;
    if(state == Qt::GestureStarted)
        gesture->setProperty("State", "Started");
    if(state == Qt::GestureUpdated)
        gesture->setProperty("State", "Updated");
    if(state == Qt::GestureFinished)
        gesture->setProperty("State", "Finished");
    gesture->setScaleFactor(scaleFactor);
    gesture->setLastScaleFactor(lastScaleFactor);
    gesture->setRotationAngle(rotationAngle);
    gesture->setLastRotationAngle(lastRotationAngle);

    if  (  state == Qt::GestureStarted
       ||  state == Qt::GestureFinished
       || (state == Qt::GestureUpdated && qAbs(scaleFactor - lastScaleFactor)/lastScaleFactor > 0.01)
       || (state == Qt::GestureUpdated && qAbs(rotationAngle - lastRotationAngle)/lastRotationAngle > 0.01)) {
        QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);
        QCoreApplication::postEvent(d->receiver, event);
    }

    lastScaleFactor = scaleFactor;
    lastRotationAngle = rotationAngle;
}

void dtkVrGestureRecognizer::postClearEvent(Qt::GestureState state)
{
    if(!d->receiver)
        return;

    QGesture *gesture = new QGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);
    QCoreApplication::postEvent(d->receiver, event);
}

// /////////////////////////////////////////////////////////////////
// vrpn callbacks
// /////////////////////////////////////////////////////////////////

void VRPN_CALLBACK vrpn_gesture_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback)
{
    if(dtkVrGestureRecognizerPrivate *recognizer = static_cast<dtkVrGestureRecognizerPrivate *>(data))
        recognizer->handle_button(callback);
}

void VRPN_CALLBACK vrpn_gesture_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback)
{
    if(dtkVrGestureRecognizerPrivate *recognizer = static_cast<dtkVrGestureRecognizerPrivate *>(data))
        recognizer->handle_analog(callback);
}

void VRPN_CALLBACK vrpn_gesture_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback)
{
    if(dtkVrGestureRecognizerPrivate *recognizer = static_cast<dtkVrGestureRecognizerPrivate *>(data))
        recognizer->handle_tracker(callback);
}
