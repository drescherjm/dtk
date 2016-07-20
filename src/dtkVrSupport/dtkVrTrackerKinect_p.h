/* dtkVrTrackerKinect_p.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 25 17:12:02 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 25 17:25:08 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKVRTRACKERKINECT_P_H
#define DTKVRTRACKERKINECT_P_H

#include <dtkMathSupport/dtkQuaternion.h>
#include <dtkMathSupport/dtkVector3D.h>

#include <QtCore>

class dtkVrTrackerKinectPrivateThread;

class dtkVrTrackerKinectPrivate : public QObject
{
    Q_OBJECT

public:
    dtkVrTrackerKinectPrivate(void);
    ~dtkVrTrackerKinectPrivate(void);

public:
    void *depthGenerator(void);
    void *handsGenerator(void);
    void *usersGenerator(void);

public slots:
    void   initialize(void);
    void uninitialize(void);

public slots:
    void rotate(int angle);

public slots:
    void setActive(void *listener);

public:
    dtkVector3D<double> hand(void);
    dtkVector3D<double> position(void);
    dtkQuaternion<double> orientation(void);

private:
    dtkVrTrackerKinectPrivateThread *d;

private:
    friend class dtkVrTrackerKinectPrivateThread;
};

#endif
