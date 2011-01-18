/* dtkVrGestureRecognizer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:12:59 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Nov  5 17:31:39 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#if defined(DTK_WRAP_VRPN)
#include <vrpn_Shared.h>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <vrpn_Tracker.h>
#include <vrpn_FileConnection.h>
#include <quat.h>
#endif

#include <QtCore>

class dtkAbstractView;
class dtkVrGestureRecognizer;

class dtkVrGestureRecognizerPrivate : public QThread
{
    Q_OBJECT

public:
    enum State {
        Begin,
        Pan,
        Pinch,
        End
    };

public:
    void run(void);
    void stop(void);

#if defined(DTK_WRAP_VRPN)
    void handle_button(const vrpn_BUTTONCB callback);
    void handle_analog(const vrpn_ANALOGCB callback);
    void handle_tracker(const vrpn_TRACKERCB callback);
#endif

public:
    bool running;
    bool acknowledge;

#if defined(DTK_WRAP_VRPN)
    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;
#endif

    QUrl url;

    QMutex mutex;

public:
    bool left_major_interaction;
    bool right_major_interaction;

    float left_hand_position[3];
    float left_thumb_position[3];
    float left_thumb_start_position[3];
    float left_index_position[3];
    float left_index_start_position[3];
    float left_major_position[3];

    float right_hand_position[3];
    float right_thumb_position[3];
    float right_thumb_start_position[3];
    float right_index_position[3];
    float right_index_start_position[3];
    float right_major_position[3];

    State state;

public:
    QObject *receiver;
    dtkAbstractView *view;

public:
    dtkVrGestureRecognizer *q;

signals:
    void postPanEvent(Qt::GestureState state);
    void postSwipeEvent(Qt::GestureState state);
    void postPinchEvent(Qt::GestureState state);
    void postCustomEvent(Qt::GestureState state);
    void postClearEvent(Qt::GestureState state);
};
