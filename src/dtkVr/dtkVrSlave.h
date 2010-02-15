/* dtkVrSlave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 13 21:27:01 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 37
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVRSLAVE_H
#define DTKVRSLAVE_H

#include "dtkVrProcess.h"

#include <QtGui>

class dtkAbstractView;

class dtkVrSlavePrivate;

class dtkVrSlave : public dtkVrProcess
{
public:
             dtkVrSlave(void);
    virtual ~dtkVrSlave(void);

    virtual void   initialize(void);
    virtual void uninitialize(void);
    
    void setView(dtkAbstractView *view);

protected:
    void process(void);

    void setupCameraLookAt(const QVector3D& eye, const QVector3D& center, const QVector3D& up);
    void setupCameraFrustum(double left, double right, double bottom, double top, double near, double far);

private:
    dtkVrSlavePrivate *d;
};

#endif
