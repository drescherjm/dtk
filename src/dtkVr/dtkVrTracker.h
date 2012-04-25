/* dtkVrTracker.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 20:30:26 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 25 16:56:26 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRTRACKER_H
#define DTKVRTRACKER_H

#include "dtkVrExport.h"

#include <dtkMath/dtkQuaternion.h>
#include <dtkMath/dtkVector3D.h>

#include <QtCore>
#include <QtNetwork>

class dtkVrTrackerPrivate;

class DTKVR_EXPORT dtkVrTracker : public QObject
{
    Q_OBJECT

public:
     dtkVrTracker(void);
    ~dtkVrTracker(void);

public:
    virtual void   initialize(void);
    virtual void   initialize(const QUrl& server);
    virtual void uninitialize(void);

public:
    virtual dtkVector3D<double> headPosition(void);
    virtual dtkVector3D<double> handPosition(void);

public:
    virtual dtkQuaternion<double> headOrientation(void);

private:
    dtkVrTrackerPrivate *d;
};

#endif
