/* dtkVrSlave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 23 10:25:16 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 53
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
class dtkVec3;
class dtkVrSlavePrivate;
class dtkQuat;

class dtkVrSlave : public dtkVrProcess
{
public:
             dtkVrSlave(dtkDistributedCommunicator *communicator);
    virtual ~dtkVrSlave(void);

    virtual void   initialize(void);
    virtual void uninitialize(void);

    void show(void);
    void showFullScreen(void);

    void resize(int w, int h);
    void move(int x, int y);

    void setView(dtkAbstractView *view);

protected:
    void process(void);

    void         setupCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up);
    void  setupLeftEyeCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up);
    void setupRightEyeCameraLookAt(const dtkVec3& eye, const dtkVec3& center, const dtkVec3& up);

    void         setupCameraFrustum(double left, double right, double bottom, double top, double near, double far);
    void  setupLeftEyeCameraFrustum(double left, double right, double bottom, double top, double near, double far);
    void setupRightEyeCameraFrustum(double left, double right, double bottom, double top, double near, double far);

private:
    dtkVrSlavePrivate *d;
};

#endif
