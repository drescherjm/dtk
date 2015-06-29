/* dtkVrTrackerVrpn.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 18 20:35:23 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 17:47:35 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkVrSupportExport.h"
#include "dtkVrTracker.h"
#include <dtkMathSupport/dtkVector3D.h>

#include <QtCore>

using namespace dtkDeprecated;

class dtkVrTrackerVrpnPrivate;

class DTKVRSUPPORT_EXPORT dtkVrTrackerVrpn : public dtkVrTracker
{
    Q_OBJECT

public:
     dtkVrTrackerVrpn(void);
    ~dtkVrTrackerVrpn(void);

public:
    void   initialize(void);
    void uninitialize(void);

public:
    void setUrl(const QUrl& url);

public:
    dtkVector3D<double>   headPosition(void);
    dtkVector3D<double> devicePosition(void);

    dtkQuaternion<double>   headOrientation(void);
    dtkQuaternion<double> deviceOrientation(void);

public:
    typedef void (*dtkVrTrackerVrpnAxesHandler)(int, float);

    void registerAxesHandler1(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler);
    void registerAxesHandler2(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler);
    void registerAxesHandler3(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler);
    void registerAxesHandler4(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler);
    void registerAxesHandler5(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler);
    void registerAxesHandler6(dtkVrTrackerVrpn::dtkVrTrackerVrpnAxesHandler handler);

    typedef void (*dtkVrTrackerVrpnPositionHandler)(float, float, float);

    void registerPositionHandler1(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler);
    void registerPositionHandler2(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler);
    void registerPositionHandler3(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler);
    void registerPositionHandler4(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler);
    void registerPositionHandler5(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler);
    void registerPositionHandler6(dtkVrTrackerVrpn::dtkVrTrackerVrpnPositionHandler handler);

    typedef void (*dtkVrTrackerVrpnOrientationHandler)(float, float, float, float);

    void registerOrientationHandler1(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler);
    void registerOrientationHandler2(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler);
    void registerOrientationHandler3(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler);
    void registerOrientationHandler4(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler);
    void registerOrientationHandler5(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler);
    void registerOrientationHandler6(dtkVrTrackerVrpn::dtkVrTrackerVrpnOrientationHandler handler);

    enum Button {
        dtkVrTrackerVrpnButton0,
        dtkVrTrackerVrpnButton1,
        dtkVrTrackerVrpnButton2,
        dtkVrTrackerVrpnButton3,
        dtkVrTrackerVrpnButton4,
        dtkVrTrackerVrpnButton5,
        dtkVrTrackerVrpnButton6,
        dtkVrTrackerVrpnButton7,
        dtkVrTrackerVrpnButton8,
        dtkVrTrackerVrpnButton9,
        dtkVrTrackerVrpnButtonUndefined
    };

    QString description(void) const;

signals:
     void buttonPressed(int button);
    void buttonReleased(int button);

public slots:
    void startConnection(const QUrl& server);
    void  stopConnection(void);

protected:
    void runAxesHandlers1(int axis, float angle);
    void runAxesHandlers2(int axis, float angle);
    void runAxesHandlers3(int axis, float angle);
    void runAxesHandlers4(int axis, float angle);
    void runAxesHandlers5(int axis, float angle);
    void runAxesHandlers6(int axis, float angle);

    void runPositionHandlers1(float x, float y, float z);
    void runPositionHandlers2(float x, float y, float z);
    void runPositionHandlers3(float x, float y, float z);
    void runPositionHandlers4(float x, float y, float z);
    void runPositionHandlers5(float x, float y, float z);
    void runPositionHandlers6(float x, float y, float z);

    void runOrientationHandlers1(float q0, float q1, float q2, float q3);
    void runOrientationHandlers2(float q0, float q1, float q2, float q3);
    void runOrientationHandlers3(float q0, float q1, float q2, float q3);
    void runOrientationHandlers4(float q0, float q1, float q2, float q3);
    void runOrientationHandlers5(float q0, float q1, float q2, float q3);
    void runOrientationHandlers6(float q0, float q1, float q2, float q3);

private:
    friend class dtkVrTrackerVrpnPrivate; dtkVrTrackerVrpnPrivate *d;
};

