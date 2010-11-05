/* dtkVrGestureRecognizer.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:12:40 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Nov  5 17:44:47 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 662
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrGestureRecognizer.h"
#include "dtkVrGestureRecognizer_p.h"
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
void VRPN_CALLBACK vrpn_gesture_recognizer_handle_button(void *data, const vrpn_BUTTONCB callback);
void VRPN_CALLBACK vrpn_gesture_recognizer_handle_analog(void *data, const vrpn_ANALOGCB callback);
void VRPN_CALLBACK vrpn_gesture_recognizer_handle_tracker(void *data, const vrpn_TRACKERCB callback);
#endif

// /////////////////////////////////////////////////////////////////
// dtkVrGestureRecognizerPrivate
// /////////////////////////////////////////////////////////////////

void dtkVrGestureRecognizerPrivate::run(void)
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
#endif
}

void dtkVrGestureRecognizerPrivate::stop(void)
{
    this->running = false;
}

#if defined(HAVE_VRPN)

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
    if(!this->acknowledge)
        return;

    if(callback.sensor == 100) {
        this->right_hand_position[0] = callback.pos[0];
        this->right_hand_position[1] = callback.pos[1];
        this->right_hand_position[2] = callback.pos[2];
    }

    if(callback.sensor == 1000) {
        this->right_thumb_position[0] = this->right_hand_position[0] + callback.pos[0];
        this->right_thumb_position[1] = this->right_hand_position[1] + callback.pos[1];
        this->right_thumb_position[2] = this->right_hand_position[2] + callback.pos[2];
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

    if(callback.sensor == 1010) {
        this->left_thumb_position[0] = this->left_hand_position[0] + callback.pos[0];
        this->left_thumb_position[1] = this->left_hand_position[1] + callback.pos[1];
        this->left_thumb_position[2] = this->left_hand_position[2] + callback.pos[2];
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
        this->right_major_interaction = (callback.pos[0] <= 0);

    if(callback.sensor == 1012)
        this->left_major_interaction = (callback.pos[0] <= 0);

    if(this->left_major_interaction || this->right_major_interaction) {

        if (state == End) {

            this->left_thumb_start_position[0] = this->left_thumb_position[0];
            this->left_thumb_start_position[1] = this->left_thumb_position[1];
            this->left_thumb_start_position[2] = this->left_thumb_position[2];

            this->right_thumb_start_position[0] = this->right_thumb_position[0];
            this->right_thumb_start_position[1] = this->right_thumb_position[1];
            this->right_thumb_start_position[2] = this->right_thumb_position[2];

            this->left_index_start_position[0] = this->left_index_position[0];
            this->left_index_start_position[1] = this->left_index_position[1];
            this->left_index_start_position[2] = this->left_index_position[2];

            this->right_index_start_position[0] = this->right_index_position[0];
            this->right_index_start_position[1] = this->right_index_position[1];
            this->right_index_start_position[2] = this->right_index_position[2];

            state = Begin;
        }

        if (state == Begin) {

            if(this->left_major_interaction && this->right_major_interaction) {

                state = Pinch;
                
                // this->mutex.lock();
                // this->acknowledge = false;
                // this->mutex.unlock();                

                emit postPinchEvent(Qt::GestureStarted);

            } else {

                state = Pan;
                
                // this->mutex.lock();
                // this->acknowledge = false;
                // this->mutex.unlock();

                emit postPanEvent(Qt::GestureStarted);
            }
        }

        if (state == Pan) {

            if(this->left_major_interaction && this->right_major_interaction) {

                state = End;

                this->mutex.lock();
                this->acknowledge = false;
                this->mutex.unlock();

                emit postPanEvent(Qt::GestureFinished);

            } else {

                // this->mutex.lock();
                // this->acknowledge = false;
                // this->mutex.unlock();

                emit postPanEvent(Qt::GestureUpdated);

            }
        }

        if (state == Pinch) {

            if(this->left_major_interaction && this->right_major_interaction) {

                // this->mutex.lock();
                // this->acknowledge = false;
                // this->mutex.unlock();

                emit postPinchEvent(Qt::GestureUpdated);

            } else {

                state = End;

                this->mutex.lock();
                this->acknowledge = false;
                this->mutex.unlock();

                emit postPinchEvent(Qt::GestureFinished);
            }
        }

    } else {
            
        if(state == Pinch) {
            
            state = End;

            this->mutex.lock();
            this->acknowledge = false;
            this->mutex.unlock();

            emit postPinchEvent(Qt::GestureFinished);
        }
        
        if(state == Pan) {
            
            state = End;

            this->mutex.lock();
            this->acknowledge = false;
            this->mutex.unlock();

            emit postPanEvent(Qt::GestureFinished);
        }
    }
}

#endif

// /////////////////////////////////////////////////////////////////
// dtkVrGestureRecognizer
// /////////////////////////////////////////////////////////////////

dtkVrGestureRecognizer::dtkVrGestureRecognizer(void) : QObject(), d(new dtkVrGestureRecognizerPrivate)
{
    d->view = NULL;
    d->receiver = NULL;
    d->q = this;
    d->running = false;
    d->acknowledge = true;
    d->state = dtkVrGestureRecognizerPrivate::End;

    connect(d, SIGNAL(postPanEvent(Qt::GestureState)), this, SLOT(postPanEvent(Qt::GestureState)));
    connect(d, SIGNAL(postSwipeEvent(Qt::GestureState)), this, SLOT(postSwipeEvent(Qt::GestureState)));
    connect(d, SIGNAL(postPinchEvent(Qt::GestureState)), this, SLOT(postPinchEvent(Qt::GestureState)));
    connect(d, SIGNAL(postCustomEvent(Qt::GestureState)), this, SLOT(postCustomEvent(Qt::GestureState)));
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

void dtkVrGestureRecognizer::setView(dtkAbstractView *view)
{
    d->view = view;
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

    if(state == Qt::GestureFinished) {
        d->mutex.lock();
        d->acknowledge = true;
        d->mutex.unlock();
    }

    static dtkVector3D<double> lastPosition;

    dtkVector3D<double> position;

    if(d->left_major_interaction && !d->right_major_interaction) {
        
        position = dtkVector3D<double>(
            d->left_index_position[0],
            d->left_index_position[2],
          - d->left_index_position[1]);

    }
        
    else if(!d->left_major_interaction && d->right_major_interaction) {
        position = dtkVector3D<double>(
            d->right_index_position[0],
            d->right_index_position[2],
          - d->right_index_position[1]);

    } else {

        position = lastPosition;
    }

    position[2] = 0;

    if(state == Qt::GestureStarted)
        lastPosition = position;

    dtkVector3D<double> offset = position-lastPosition;

    float xmin, xmax;
    float ymin, ymax;
    float zmin, zmax;

    double camera_up[3];
    double camera_position[3];
    double camera_focalpnt[3];

    d->view->bounds(xmin, xmax, ymin, ymax, zmin, zmax);
    d->view->cameraUp(camera_up);
    d->view->cameraPosition(camera_position);
    d->view->cameraFocalPoint(camera_focalpnt);

    dtkVector3D<double> a = dtkVector3D<double>(xmin, ymin, zmin);
    dtkVector3D<double> b = dtkVector3D<double>(xmax, ymax, zmax);

    double dg = (b-a).norm();

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

    dtkVector3D<double> f_art = dtkVector3D<double>(
        (   dtkVrScreen::screens[4][1][0] +    dtkVrScreen::screens[4][0][0]) / 2,
        (-1*dtkVrScreen::screens[4][2][2] + -1*dtkVrScreen::screens[4][1][2]) / 2,
            dtkVrScreen::screens[4][0][1]);
    dtkVector3D<double> z_art = dtkVector3D<double>(0, f_art[1], 0);
    dtkVector3D<double> p_art = position;
    dtkVector3D<double> d_art = offset;

    dtkVector3D<double> o_xtk = cam_to_xtk*offset;
    o_xtk *= dg;
    o_xtk *= -1;

    QPanGesture *gesture = new QPanGesture(this);
    if(state == Qt::GestureStarted)
        gesture->setProperty("State", "Started");
    if(state == Qt::GestureUpdated)
        gesture->setProperty("State", "Updated");
    if(state == Qt::GestureFinished)
        gesture->setProperty("State", "Finished");

    if(state == Qt::GestureStarted) {
        gesture->setProperty("PanGestureOffsetX", 0.0);
        gesture->setProperty("PanGestureOffsetY", 0.0);
        gesture->setProperty("PanGestureOffsetZ", 0.0);
    } else {
        gesture->setProperty("PanGestureOffsetX", o_xtk[0]);
        gesture->setProperty("PanGestureOffsetY", o_xtk[1]);
        gesture->setProperty("PanGestureOffsetZ", o_xtk[2]);
    }

    if  (  state == Qt::GestureStarted
       ||  state == Qt::GestureFinished
       || (state == Qt::GestureUpdated && (offset.norm() > 0.005))) {

        if(state == Qt::GestureFinished)
            qDebug() << "POSTING PAN FINISHED";

        QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);        
        QCoreApplication::postEvent(d->receiver, event);   
    }

    lastPosition = position;
}

void dtkVrGestureRecognizer::postSwipeEvent(Qt::GestureState state)
{
    if(!d->receiver)
        return;

    if(state == Qt::GestureFinished) {
        d->mutex.lock();
        d->acknowledge = true;
        d->mutex.unlock();
    }

    QSwipeGesture *gesture = new QSwipeGesture(this);
    QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);

    // QCoreApplication::postEvent(d->receiver, event);
}

#include <math.h>

void dtkVrGestureRecognizer::postPinchEvent(Qt::GestureState state)
{
    if(!d->receiver)
        return;

    if(state == Qt::GestureFinished) {
        d->mutex.lock();
        d->acknowledge = true;
        d->mutex.unlock();
    }

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

    dtkVector3D<double> ns = t*s; ns[2] = 0;
    dtkVector3D<double> nu = t*u; nu[2] = 0;

    // -- Computing scale factor --

    static qreal lastScaleFactor;

    qreal scaleFactor = nu.norm()/ns.norm();

    if(state == Qt::GestureStarted)
        lastScaleFactor = scaleFactor;

    // -- Computing rotation angle --

    static qreal lastRotationAngle;

    qreal rotationAngle = -1.0 * (acos(nu.unit() * ns.unit()) * ((ns % nu).unit() * n.unit())) * 180.0 / 3.141593;

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
       || (state == Qt::GestureUpdated && qAbs((rotationAngle - lastRotationAngle)/lastRotationAngle) > 0.01)) {
        QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);
        QCoreApplication::postEvent(d->receiver, event);
    }

    lastScaleFactor = scaleFactor;
    lastRotationAngle = rotationAngle;
}

void dtkVrGestureRecognizer::postCustomEvent(Qt::GestureState state)
{
    if(!d->receiver)
        return;

    if(state == Qt::GestureFinished) {
        d->mutex.lock();
        d->acknowledge = true;
        d->mutex.unlock();
    }

    dtkVector3D<double> nis = dtkVector3D<double>(
        d->left_thumb_start_position[0] - d->left_index_start_position[0],
        d->left_thumb_start_position[2] - d->left_index_start_position[2],
      - d->left_thumb_start_position[1] + d->left_index_start_position[1]);

    dtkVector3D<double> njs = dtkVector3D<double>(
        d->right_index_start_position[0] - d->left_index_start_position[0],
        d->right_index_start_position[2] - d->left_index_start_position[2],
      - d->right_index_start_position[1] + d->left_index_start_position[1]);

    dtkVector3D<double> nks = nis%njs;

    dtkVector3D<double> niu = dtkVector3D<double>(
        d->left_thumb_position[0] - d->left_index_position[0],
        d->left_thumb_position[2] - d->left_index_position[2],
      - d->left_thumb_position[1] + d->left_index_position[1]);

    dtkVector3D<double> nju = dtkVector3D<double>(
        d->right_index_position[0] - d->left_index_position[0],
        d->right_index_position[2] - d->left_index_position[2],
      - d->right_index_position[1] + d->left_index_position[1]);

    dtkVector3D<double> nku = niu%nju;

    // double camera_up[3];
    // double camera_position[3];
    // double camera_focalpnt[3];

    // d->view->cameraUp(camera_up);
    // d->view->cameraPosition(camera_position);
    // d->view->cameraFocalPoint(camera_focalpnt);

    // dtkVector3D<double> u_xtk = dtkVector3D<double>(camera_up[0], camera_up[1], camera_up[2]);
    // dtkVector3D<double> p_xtk = dtkVector3D<double>(camera_position[0], camera_position[1], camera_position[2]);
    // dtkVector3D<double> f_xtk = dtkVector3D<double>(camera_focalpnt[0], camera_focalpnt[1], camera_focalpnt[2]);

    // dtkVector3D<double> l = dtkVector3D<double>(1.0, 0.0, 0.0);
    // dtkVector3D<double> m = dtkVector3D<double>(0.0, 1.0, 0.0);
    // dtkVector3D<double> n = dtkVector3D<double>(0.0, 0.0, 1.0);
    // dtkVector3D<dtkVector3D<double> > xtk_in_xtk = dtkVector3D<dtkVector3D<double> >(l, m, n);
    
    // dtkVector3D<double> j = u_xtk;
    // dtkVector3D<double> k = p_xtk-f_xtk;
    // dtkVector3D<double> i = j%k;
    // dtkVector3D<dtkVector3D<double> > cam_in_xtk = dtkVector3D<dtkVector3D<double> >(i.unit(), j.unit(), k.unit());
    
    // dtkMatrixSquared<double> t = dtkChangeOfBasis(cam_in_xtk, xtk_in_xtk);

    // dtkVector3D<double> nnjs = t*njs;
    // dtkVector3D<double> nnju = t*nju;
    // dtkVector3D<double> nnks = t*nks;
    // dtkVector3D<double> nnku = t*nku;

    // dtkVector3D<double> nnjs_mn = nnjs; nnjs_mn[0] = 0; 
    // dtkVector3D<double> nnjs_nl = nnjs; nnjs_nl[1] = 0; 
    // dtkVector3D<double> nnjs_lm = nnjs; nnjs_lm[2] = 0; 

    // dtkVector3D<double> nnju_mn = nnju; nnju_mn[0] = 0; 
    // dtkVector3D<double> nnju_nl = nnju; nnju_nl[1] = 0; 
    // dtkVector3D<double> nnju_lm = nnju; nnju_lm[2] = 0; 

    // dtkVector3D<double> nnks_mn = nnks; nnks_mn[0] = 0; 
    // dtkVector3D<double> nnks_nl = nnks; nnks_nl[1] = 0; 
    // dtkVector3D<double> nnks_lm = nnks; nnks_lm[2] = 0; 

    // dtkVector3D<double> nnku_mn = nnku; nnku_mn[0] = 0; 
    // dtkVector3D<double> nnku_nl = nnku; nnku_nl[1] = 0; 
    // dtkVector3D<double> nnku_lm = nnku; nnku_lm[2] = 0; 

    // // -- Computing rotation angle --

    // static qreal lastAzAngle;
    // static qreal lastElAngle;
    // static qreal lastRoAngle;

    // qreal azAngle = -0.0 * (acos(nnju_lm.unit() * nnjs_lm.unit()) * ((nnjs_lm % nnju_lm).unit() * j.unit())) * 180.0 / 3.141593;

    // qreal elAngle =  0.0 * (acos(nnku_mn.unit() * nnks_mn.unit()) * ((nnks_mn % nnku_mn).unit() * i.unit())) * 180.0 / 3.141593;

    // qreal roAngle =  1.0 * (acos(nnju_nl.unit() * nnjs_nl.unit()) * ((nnjs_nl % nnju_nl).unit() * k.unit())) * 180.0 / 3.141593;

    // if(state == Qt::GestureStarted) {
    //     lastAzAngle = azAngle;
    //     lastElAngle = elAngle;
    //     lastRoAngle = roAngle;
    // }

    // -- Computing rotation angle --

    dtkVector3D<double> i = dtkVector3D<double>(1.0, 0.0, 0.0);
    dtkVector3D<double> j = dtkVector3D<double>(0.0, 1.0, 0.0);
    dtkVector3D<double> k = dtkVector3D<double>(0.0, 0.0, 1.0);

    dtkVector3D<double> njs_ki = njs; njs_ki[1] = 0; 
    dtkVector3D<double> nju_ki = nju; nju_ki[1] = 0; 

    dtkVector3D<double> njs_ij = njs; njs_ij[2] = 0; 
    dtkVector3D<double> nju_ij = nju; nju_ij[2] = 0; 

    dtkVector3D<double> nks_jk = nks; nks_jk[0] = 0; 
    dtkVector3D<double> nku_jk = nku; nku_jk[0] = 0; 

    static qreal lastAzAngle;
    static qreal lastElAngle;
    static qreal lastRoAngle;

    qreal azAngle = -1.0 * (acos(nju_ki.unit() * njs_ki.unit()) * ((njs_ki % nju_ki).unit() * j.unit())) * 180.0 / 3.141593;

    qreal elAngle =  0.0 * (acos(nku_jk.unit() * nks_jk.unit()) * ((nks_jk % nku_jk).unit() * i.unit())) * 180.0 / 3.141593;

    qreal roAngle =  1.0 * (acos(nju_ij.unit() * njs_ij.unit()) * ((njs_ij % nju_ij).unit() * k.unit())) * 180.0 / 3.141593;

    if(state == Qt::GestureStarted) {
        lastAzAngle = azAngle;
        lastElAngle = elAngle;
        lastRoAngle = roAngle;
    }

    // -- Post event --

    QGesture *gesture = new QGesture;
    if(state == Qt::GestureStarted)
        gesture->setProperty("State", "Started");
    if(state == Qt::GestureUpdated)
        gesture->setProperty("State", "Updated");
    if(state == Qt::GestureFinished)
        gesture->setProperty("State", "Finished");
    gesture->setProperty("Type", "Custom");
    gesture->setProperty("CustomGestureAngleAz", (azAngle - lastAzAngle));
    gesture->setProperty("CustomGestureAngleEl", (elAngle - lastElAngle));
    gesture->setProperty("CustomGestureAngleRo", (roAngle - lastRoAngle));

    if  (  state == Qt::GestureStarted
       ||  state == Qt::GestureFinished
       || (state == Qt::GestureUpdated && qAbs((azAngle - lastAzAngle)/lastAzAngle) > 0.01)
       || (state == Qt::GestureUpdated && qAbs((elAngle - lastElAngle)/lastElAngle) > 0.01)
       || (state == Qt::GestureUpdated && qAbs((roAngle - lastRoAngle)/lastRoAngle) > 0.01)) {

        qDebug() << "posting sutom gesture";

        QGestureEvent *event = new QGestureEvent(QList<QGesture *>() << gesture);
        QCoreApplication::postEvent(d->receiver, event);
    }

    lastAzAngle = azAngle;
    lastElAngle = elAngle;
    lastRoAngle = roAngle;
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

#if defined(HAVE_VRPN)

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

#endif
