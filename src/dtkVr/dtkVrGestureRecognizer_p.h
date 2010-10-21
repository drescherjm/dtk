/* dtkVrGestureRecognizer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:12:59 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 21 19:13:10 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <vrpn_Shared.h>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <vrpn_Tracker.h>
#include <vrpn_FileConnection.h>
#include <quat.h>

#include <QtCore>

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

    void handle_button(const vrpn_BUTTONCB callback);
    void handle_analog(const vrpn_ANALOGCB callback);
    void handle_tracker(const vrpn_TRACKERCB callback);

public:
    bool running;

    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;

    QUrl url;

public:
    bool left_interaction;
    bool right_interaction;

    float left_hand_position[3];
    float left_index_position[3];
    float left_index_start_position[3];
    float left_major_position[3];

    float right_hand_position[3];
    float right_index_position[3];
    float right_index_start_position[3];
    float right_major_position[3];

    State state;

public:
    QObject *receiver;

public:
    dtkVrGestureRecognizer *q;

signals:
    void postPanEvent(void);
    void postSwipeEvent(void);
    void postPinchEvent(void);
    void postClearEvent(void);
};
