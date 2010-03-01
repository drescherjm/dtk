/* dtkVrSlave.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:06:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  1 08:56:58 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 64
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
    Q_OBJECT

public:
             dtkVrSlave(dtkDistributedCommunicator *communicator);
    virtual ~dtkVrSlave(void);

    void   initialize(void);
    void uninitialize(void);

    void show(void);
    void showFullScreen(void);

    void resize(int w, int h);
    void move(int x, int y);

    void setView(dtkAbstractView *view);

protected:
    void process(void);

    dtkVec3 scenePosition(void) const;
    dtkQuat sceneOrientation(void) const;

    void setupScenePosition(const dtkVec3& position);
    void setupSceneOrientation(const dtkQuat& orientation);

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
