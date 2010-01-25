#ifndef DTKDEVICEWIIPRIVATE_H
#define DTKDEVICEWIIPRIVATE_H

 class dtkDeviceWii;
@class dtkDeviceWiiDelegate;

#undef slots

#import "dtkDeviceWiiRemoteDiscovery.h"
#import "dtkDeviceWiiRemote.h"

#include "dtkDeviceWii.h"

#include <QtCore>

class dtkDeviceWiiPrivate
{
public:
    dtkDeviceWii *q;
    dtkDeviceWiiDelegate *delegate;

    WiiRemoteDiscovery* remoteDiscovery;
    WiiRemote* remote;

public:
    void discovered(void);

    void buttonPressed(WiiButtonType type);
    void buttonReleased(WiiButtonType type);

    void runJoystickMotionHandlers(int x, int y);
    void runRemoteAccelerationHandlers(int x, int y, int z);
    void runNunchukAccelerationHandlers(int x, int y, int z);
    void runInfraredCursorMotionHandlers(float x, float y);
    void runInfraredSingleMotionHandlers(float x, float y, float s, int n);
};

#endif
