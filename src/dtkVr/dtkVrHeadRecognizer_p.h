/* dtkVrHeadRecognizer_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Oct 26 12:39:24 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Oct 26 13:39:35 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
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

#include <dtkMath/dtkVector3D.h>

class dtkAbstractView;
class dtkVrHeadRecognizer;

class dtkVrHeadRecognizerPrivate : public QThread
{
    Q_OBJECT

public:
    void run(void);
    void stop(void);

    void handle_button(const vrpn_BUTTONCB callback);
    void handle_analog(const vrpn_ANALOGCB callback);
    void handle_tracker(const vrpn_TRACKERCB callback);

    double head_position[3];

    bool activated;

    dtkVector3D<double> last;

public:
    bool running;

    vrpn_Button_Remote *button;
    vrpn_Analog_Remote *analog;
    vrpn_Tracker_Remote *tracker;

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
