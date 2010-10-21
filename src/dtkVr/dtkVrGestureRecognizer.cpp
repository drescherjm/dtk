/* dtkVrGestureRecognizer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:12:40 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 21 19:26:05 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrGestureRecognizer.h"
#include "dtkVrGestureRecognizer_p.h"

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// vrpn callbacks (Definition at EOF.)
// /////////////////////////////////////////////////////////////////

void VRPN_CALLBACK vrpn_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback);
void VRPN_CALLBACK vrpn_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback);
void VRPN_CALLBACK vrpn_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback);

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

    this->button->register_change_handler(this, vrpn_recognizer_handle_button);
    this->analog->register_change_handler(this, vrpn_recognizer_handle_analog);
    this->tracker->register_change_handler(this, vrpn_recognizer_handle_tracker);

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

void dtkVrGestureRecognizerPrivate::stop(void)
{
    this->running = false;
}

void dtkVrGestureRecognizerPrivate::handle_button(const vrpn_BUTTONCB callback)
{
    qDebug() << __func__;
}

void dtkVrGestureRecognizerPrivate::handle_analog(const vrpn_ANALOGCB callback)
{
    qDebug() << __func__;
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

            if(this->left_interaction && this->right_interaction)
                state = Pinch;
            else
                state = Pan;
        }

        if (state == Pan) {

            if(this->left_interaction && this->right_interaction)
                state = Pinch;

            else if(this->left_interaction) { // Use left index to pan

                emit postPanEvent();

            } else { // Use right index to pan

               emit postSwipeEvent();

           }
        }

        if (state == Pinch) {

            if(this->left_interaction && !this->right_interaction)
                state = Pan;
            else if(!this->left_interaction && this->right_interaction)
                state = Pan;
            else
                emit postPinchEvent();

        }

    } else {

        if(state != End) {
            emit postClearEvent();
            state = End;
        }
    }
}

// /////////////////////////////////////////////////////////////////
// dtkVrGestureRecognizer
// /////////////////////////////////////////////////////////////////

dtkVrGestureRecognizer::dtkVrGestureRecognizer(QObject *receiver) : QObject(), d(new dtkVrGestureRecognizerPrivate)
{
    d->receiver = receiver;
    d->q = this;
    d->running = false;
    d->state = dtkVrGestureRecognizerPrivate::End;

    connect(d, SIGNAL(postPanEvent()), this, SLOT(postPanEvent()));
    connect(d, SIGNAL(postSwipeEvent()), this, SLOT(postSwipeEvent()));
    connect(d, SIGNAL(postPinchEvent()), this, SLOT(postPinchEvent()));
    connect(d, SIGNAL(postClearEvent()), this, SLOT(postClearEvent()));
}

dtkVrGestureRecognizer::~dtkVrGestureRecognizer(void)
{
    delete d;

    d = NULL;
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

void dtkVrGestureRecognizer::postPanEvent(void)
{    
    QPanGesture *gesture = new QPanGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);

    QCoreApplication::postEvent(d->receiver, event);
}

void dtkVrGestureRecognizer::postSwipeEvent(void)
{
    QSwipeGesture *gesture = new QSwipeGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);

    QCoreApplication::postEvent(d->receiver, event);
}

void dtkVrGestureRecognizer::postPinchEvent(void)
{
    QPinchGesture *gesture = new QPinchGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);

    QCoreApplication::postEvent(d->receiver, event);
}

void dtkVrGestureRecognizer::postClearEvent(void)
{
    QGesture *gesture = new QGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);
    QCoreApplication::postEvent(d->receiver, event);
}

// /////////////////////////////////////////////////////////////////
// vrpn callbacks
// /////////////////////////////////////////////////////////////////

void VRPN_CALLBACK vrpn_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback)
{
    if(dtkVrGestureRecognizerPrivate *recognizer = static_cast<dtkVrGestureRecognizerPrivate *>(data))
        recognizer->handle_button(callback);
}

void VRPN_CALLBACK vrpn_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback)
{
    if(dtkVrGestureRecognizerPrivate *recognizer = static_cast<dtkVrGestureRecognizerPrivate *>(data))
        recognizer->handle_analog(callback);
}

void VRPN_CALLBACK vrpn_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback)
{
    if(dtkVrGestureRecognizerPrivate *recognizer = static_cast<dtkVrGestureRecognizerPrivate *>(data))
        recognizer->handle_tracker(callback);
}
