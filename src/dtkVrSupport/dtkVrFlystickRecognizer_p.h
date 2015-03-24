/* dtkVrFlystickRecognizer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb  7 10:09:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 17:25:35 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

#include <dtkConfig.h>

#include <dtkMathSupport/dtkQuaternion.h>
#include <dtkMathSupport/dtkVector3D.h>

#if defined(DTK_HAVE_VRPN)
#include <vrpn_Shared.h>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <vrpn_Tracker.h>
#include <vrpn_FileConnection.h>
#include <quat.h>
#endif

class dtkAbstractView;
class dtkVrFlystickRecognizer;

class dtkVrFlystickRecognizerPrivate : public QThread
{
    Q_OBJECT

public:
    void run(void);
    void stop(void);

#if defined(DTK_HAVE_VRPN)
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

#if defined(DTK_HAVE_VRPN)
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
