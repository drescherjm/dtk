/* dtkVrHeadRecognizer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct 26 12:39:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 28 11:05:51 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#if defined(HAVE_VRPN)
#include <vrpn_Shared.h>
#include <vrpn_Button.h>
#include <vrpn_Analog.h>
#include <vrpn_Tracker.h>
#include <vrpn_FileConnection.h>
#include <quat.h>
#endif

#include <QtCore>

#include <dtkMath/dtkVector3D.h>

class dtkAbstractView;
class dtkVrHeadRecognizer;

class dtkVrHeadRecognizerPrivate : public QThread
{
    Q_OBJECT

public:
    void run(void);
    void stop(void);

#if defined(HAVE_VRPN)
    void handle_button(const vrpn_BUTTONCB callback);
    void handle_analog(const vrpn_ANALOGCB callback);
    void handle_tracker(const vrpn_TRACKERCB callback);
#endif

    double head_position[3];

    bool activated;

    dtkVector3D<double> last;

public:
    bool running;

#if defined(HAVE_VRPN)
    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;
#endif

    QUrl url;

public:
    dtkAbstractView *receiver;

public:
    dtkVrHeadRecognizer *q;

signals:
    void moved(void);
    void buttonPressed(int);
    void buttonReleased(int);
};
