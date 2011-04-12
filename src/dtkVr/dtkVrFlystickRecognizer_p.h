/* dtkVrFlystickRecognizer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  7 10:09:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 30 13:28:47 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
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

#include <dtkMath/dtkQuaternion.h>
#include <dtkMath/dtkVector3D.h>

class dtkAbstractView;
class dtkVrFlystickRecognizer;

class dtkVrFlystickRecognizerPrivate : public QThread
{
    Q_OBJECT

public:
    void run(void);
    void stop(void);

#if defined(DTK_WRAP_VRPN)
    void handle_button(const vrpn_BUTTONCB callback);
    void handle_analog(const vrpn_ANALOGCB callback);
    void handle_tracker(const vrpn_TRACKERCB callback);
#endif

    double flystick_position[3];
    double flystick_orientation[4];

    bool activated;

    dtkVector3D<double> last_position;
    dtkQuaternion<double> last_orientation;

public:
    bool running;

#if defined(DTK_WRAP_VRPN)
    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;
#endif

    QUrl url;

public:
    dtkVrFlystickRecognizer *q;

signals:
    void moved(void);
    void rotated(void);
    void buttonPressed(int);
    void buttonReleased(int);
};
