/* dtkDeviceWii.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 13:00:57 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 25 13:01:00 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDEVICEWII_H
#define DTKDEVICEWII_H

#include <QtCore>

class dtkDeviceWiiPrivate;

class dtkDeviceWii : public QObject
{
    Q_OBJECT

public:
     dtkDeviceWii(void);
    ~dtkDeviceWii(void);

    typedef void (*dtkDeviceWiiJoystickMotionHandler)(int x, int y);
    typedef void (*dtkDeviceWiiAccelerationHandler)(int x, int y, int z);
    typedef void (*dtkDeviceWiiInfraredCursorMotionHandler)(float x, float y);
    typedef void (*dtkDeviceWiiInfraredSingleMotionHandler)(float x, float y, float s, int n);

    void registerJoystickMotionHandler(dtkDeviceWii::dtkDeviceWiiJoystickMotionHandler handler);
    void registerRemoteAccelerationHandler(dtkDeviceWii::dtkDeviceWiiAccelerationHandler handler);
    void registerNunchukAccelerationHandler(dtkDeviceWii::dtkDeviceWiiAccelerationHandler handler);
    void registerInfraredCursorMotionHandler(dtkDeviceWii::dtkDeviceWiiInfraredCursorMotionHandler handler);
    void registerInfraredSingleMotionHandler(dtkDeviceWii::dtkDeviceWiiInfraredSingleMotionHandler handler);

    enum dtkDeviceWiiButton {
        dtkDeviceWiiButtonA,
        dtkDeviceWiiButtonB,
        dtkDeviceWiiButtonC,
        dtkDeviceWiiButtonZ,
        dtkDeviceWiiButtonOne,
        dtkDeviceWiiButtonTwo,
        dtkDeviceWiiButtonMinus,
        dtkDeviceWiiButtonHome,
        dtkDeviceWiiButtonPlus,
        dtkDeviceWiiButtonUp,
        dtkDeviceWiiButtonDown,
        dtkDeviceWiiButtonLeft,
        dtkDeviceWiiButtonRight
    };

    QString description(void) const;

signals:
    void discovered(void);

    void buttonPressed(dtkDeviceWii::dtkDeviceWiiButton);
    void buttonReleased(dtkDeviceWii::dtkDeviceWiiButton);

public slots:
    void startDiscovery(void);
    void  stopDiscovery(void);

    void startConnection(void);
    void  stopConnection(void);

    void toggleLed1(bool on);
    void toggleLed2(bool on);
    void toggleLed3(bool on);
    void toggleLed4(bool on);
    void toggleInfraredSensor(bool);
    void toggleForceFeedBack(bool);
    void toggleMotionSensor(bool);
    void toggleExpansionPort(bool);

protected:
    QList<dtkDeviceWii::dtkDeviceWiiJoystickMotionHandler> joystickMotionHandlers;
    QList<dtkDeviceWii::dtkDeviceWiiAccelerationHandler> remoteAccelerationHandlers;
    QList<dtkDeviceWii::dtkDeviceWiiAccelerationHandler> nunchukAccelerationHandlers;
    QList<dtkDeviceWii::dtkDeviceWiiInfraredCursorMotionHandler> infraredCursorMotionHandlers;
    QList<dtkDeviceWii::dtkDeviceWiiInfraredSingleMotionHandler> infraredSingleMotionHandlers;

    void runJoystickMotionHandlers(int x, int y);
    void runRemoteAccelerationHandlers(int x, int y, int z);
    void runNunchukAccelerationHandlers(int x, int y, int z);
    void runInfraredCursorMotionHandlers(float x, float y);
    void runInfraredSingleMotionHandlers(float x, float y, float s, int n);

private:
    friend class dtkDeviceWiiPrivate; dtkDeviceWiiPrivate *d;
};

#endif
