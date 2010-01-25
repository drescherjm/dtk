/* dtkDeviceWii_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 13:01:16 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 25 13:01:19 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

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
