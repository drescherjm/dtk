/* dtkDeviceWii.mm --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 13:01:05 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 26 21:09:01 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDeviceWii.h"
#include "dtkDeviceWii_p.h"
#include "dtkDeviceWiiDelegate.h"

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

void setBufferFromCFString(QString& qs, CFStringRef cfs)
{
    if (!cfs)
        return;

    CFIndex size = CFStringGetLength(cfs);
    UniChar fixedSizeBuffer[1024];
    UniChar *buffer;

    if (size > (CFIndex)(sizeof(fixedSizeBuffer) / sizeof(UniChar))) {
        buffer = (UniChar *)malloc(size * sizeof(UniChar));
    } else {
        buffer = fixedSizeBuffer;
    }

    CFStringGetCharacters(cfs, CFRangeMake (0, size), buffer);

    qs.setUnicode((const QChar *)buffer, (uint)size);

    if (buffer != fixedSizeBuffer)
        free(buffer);
}

QString qStringfromCFString(CFStringRef cfs)
{
    QString qs;
    setBufferFromCFString(qs, cfs);
    return qs;
}

QString qStringfromNSString(NSString *nss)
{
    QString qs;
    setBufferFromCFString(qs, (CFStringRef)nss);
    return qs;
}

// /////////////////////////////////////////////////////////////////
// dtkDeviceWiiPrivate
// /////////////////////////////////////////////////////////////////

void dtkDeviceWiiPrivate::discovered(void)
{
    emit q->discovered();
}

void dtkDeviceWiiPrivate::buttonPressed(WiiButtonType type)
{
    switch(type) {
    case WiiRemoteAButton:
        emit q->buttonPressed(dtkDeviceWii::dtkDeviceWiiButtonA);
        break;
    case WiiRemoteBButton:
        emit q->buttonPressed(dtkDeviceWii::dtkDeviceWiiButtonB);
        break;
    default:
        break;
    }
}

void dtkDeviceWiiPrivate::buttonReleased(WiiButtonType type)
{
    switch(type) {
    case WiiRemoteAButton:
        emit q->buttonReleased(dtkDeviceWii::dtkDeviceWiiButtonA);
        break;
    case WiiRemoteBButton:
        emit q->buttonReleased(dtkDeviceWii::dtkDeviceWiiButtonB);
        break;
    default:
        break;
    }
}

void dtkDeviceWiiPrivate::runJoystickMotionHandlers(int x, int y)
{
    q->runJoystickMotionHandlers(x, y);
}

void dtkDeviceWiiPrivate::runRemoteAccelerationHandlers(int x, int y, int z)
{
    q->runRemoteAccelerationHandlers(x, y, z);
}

void dtkDeviceWiiPrivate::runNunchukAccelerationHandlers(int x, int y, int z)
{
    q->runNunchukAccelerationHandlers(x, y, z);
}

void dtkDeviceWiiPrivate::runInfraredCursorMotionHandlers(float x, float y)
{
    q->runInfraredCursorMotionHandlers(x, y);
}

void dtkDeviceWiiPrivate::runInfraredSingleMotionHandlers(float x, float y, float s, int n)
{
    q->runInfraredSingleMotionHandlers(x, y, s, n);
}

// /////////////////////////////////////////////////////////////////
// dtkDeviceWii
// /////////////////////////////////////////////////////////////////

dtkDeviceWii::dtkDeviceWii(void) : dtkAbstractDevice(), d(new dtkDeviceWiiPrivate)
{
     d->delegate = [[dtkDeviceWiiDelegate alloc] init];
    [d->delegate setParent:d];

     d->remoteDiscovery = [[WiiRemoteDiscovery alloc] init];
    [d->remoteDiscovery setDelegate:d->delegate];

    d->remote = nil;
    d->q = this;
}

dtkDeviceWii::~dtkDeviceWii(void)
{
    if  (d->remote != nil) {
        [d->remote closeConnection];
        [d->remote release];
    }

    if  (d->remoteDiscovery != nil) {
        [d->remoteDiscovery stop];
        [d->remoteDiscovery release];
    }

    delete d;

    d = NULL;
}

void dtkDeviceWii::registerJoystickMotionHandler(dtkDeviceWii::dtkDeviceWiiJoystickMotionHandler handler)
{
    this->joystickMotionHandlers << handler;
}

void dtkDeviceWii::registerInfraredCursorMotionHandler(dtkDeviceWii::dtkDeviceWiiInfraredCursorMotionHandler handler)
{
    this->infraredCursorMotionHandlers << handler;
}

void dtkDeviceWii::registerRemoteAccelerationHandler(dtkDeviceWii::dtkDeviceWiiAccelerationHandler handler)
{
    this->remoteAccelerationHandlers << handler;
}

void dtkDeviceWii::registerNunchukAccelerationHandler(dtkDeviceWii::dtkDeviceWiiAccelerationHandler handler)
{
    this->nunchukAccelerationHandlers << handler;
}

void dtkDeviceWii::registerInfraredSingleMotionHandler(dtkDeviceWii::dtkDeviceWiiInfraredSingleMotionHandler handler)
{
    this->infraredSingleMotionHandlers << handler;
}

QString dtkDeviceWii::description(void) const
{
    if(d->remote != nil)
        return "dtkDeviceWii - " + qStringfromNSString([d->remote address]);
    else
        return "dtkDeviceWii - Non addressed wiimote.";
}

void dtkDeviceWii::startDiscovery(void)
{
    [d->remoteDiscovery start];
}

void dtkDeviceWii::stopDiscovery(void)
{
    [d->remoteDiscovery stop];
}

void dtkDeviceWii::startConnection(void)
{
    if (d->remote == nil)
        startDiscovery();
}

void dtkDeviceWii::stopConnection(void)
{
    if  (d->remote != nil) {
        [d->remote closeConnection];
        [d->remote release];
    }
}

void dtkDeviceWii::toggleLed1(bool on)
{
    [d->remote setLEDEnabled1: on enabled2:[d->remote isLED2Illuminated] enabled3:[d->remote isLED3Illuminated] enabled4:[d->remote isLED4Illuminated]];
}

void dtkDeviceWii::toggleLed2(bool on)
{
    [d->remote setLEDEnabled1: [d->remote isLED1Illuminated] enabled2:on enabled3:[d->remote isLED3Illuminated] enabled4:[d->remote isLED4Illuminated]];
}

void dtkDeviceWii::toggleLed3(bool on)
{
    [d->remote setLEDEnabled1: [d->remote isLED1Illuminated] enabled2:[d->remote isLED2Illuminated] enabled3:on enabled4:[d->remote isLED4Illuminated]];
}

void dtkDeviceWii::toggleLed4(bool on)
{
    [d->remote setLEDEnabled1: [d->remote isLED1Illuminated] enabled2:[d->remote isLED2Illuminated] enabled3:[d->remote isLED3Illuminated] enabled4:on];
}

void dtkDeviceWii::toggleInfraredSensor(bool on)
{
    [d->remote setIRSensorEnabled:on];
}

void dtkDeviceWii::toggleForceFeedBack(bool on)
{
    [d->remote setForceFeedbackEnabled:on];
}

void dtkDeviceWii::toggleMotionSensor(bool on)
{
    [d->remote setMotionSensorEnabled:on];
}

void dtkDeviceWii::toggleExpansionPort(bool on)
{
    [d->remote setExpansionPortEnabled:on];
}

void dtkDeviceWii::runJoystickMotionHandlers(int x, int y)
{
    foreach(dtkDeviceWii::dtkDeviceWiiJoystickMotionHandler handler, this->joystickMotionHandlers)
        (handler)(x, y);
}

void dtkDeviceWii::runRemoteAccelerationHandlers(int x, int y, int z)
{
    foreach(dtkDeviceWii::dtkDeviceWiiAccelerationHandler handler, this->remoteAccelerationHandlers)
        (handler)(x, y, z);
}

void dtkDeviceWii::runNunchukAccelerationHandlers(int x, int y, int z)
{
    foreach(dtkDeviceWii::dtkDeviceWiiAccelerationHandler handler, this->nunchukAccelerationHandlers)
        (handler)(x, y, z);
}

void dtkDeviceWii::runInfraredCursorMotionHandlers(float x, float y)
{
    foreach(dtkDeviceWii::dtkDeviceWiiInfraredCursorMotionHandler handler, this->infraredCursorMotionHandlers)
        (handler)(x, y);
}

void dtkDeviceWii::runInfraredSingleMotionHandlers(float x, float y, float s, int n)
{
    foreach(dtkDeviceWii::dtkDeviceWiiInfraredSingleMotionHandler handler, this->infraredSingleMotionHandlers)
        (handler)(x, y, s, n);
}
