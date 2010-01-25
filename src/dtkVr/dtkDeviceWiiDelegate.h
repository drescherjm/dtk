/* dtkDeviceWiiDelegate.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 13:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 25 13:01:36 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDEVICEWIIDELEGATE_H
#define DTKDEVICEWIIDELEGATE_H

#import <Cocoa/Cocoa.h>

#import "dtkDeviceWiiRemoteDiscovery.h"
#import "dtkDeviceWiiRemote.h"

#include "dtkDeviceWii_p.h"

@interface dtkDeviceWiiDelegate : NSObject
{
    dtkDeviceWiiPrivate *parent;
}

// WiiRemoteDiscovery delegation

- (void) WiiRemoteDiscovered:(WiiRemote*)wiimote;
- (void) WiiRemoteDiscoveryError:(int)code;

// WiiRemote delegation

- (void) irPointMovedX:(float)px Y:(float)py wiiRemote:(WiiRemote*)wiiRemote;
- (void) rawIRData: (IRData[4])irData wiiRemote:(WiiRemote*)wiiRemote;
- (void) buttonChanged:(WiiButtonType)type isPressed:(BOOL)isPressed wiiRemote:(WiiRemote*)wiiRemote;
- (void) accelerationChanged:(WiiAccelerationSensorType)type accX:(unsigned char)accX accY:(unsigned char)accY accZ:(unsigned char)accZ wiiRemote:(WiiRemote*)wiiRemote;
- (void) joyStickChanged:(WiiJoyStickType)type tiltX:(unsigned char)tiltX tiltY:(unsigned char)tiltY wiiRemote:(WiiRemote*)wiiRemote;
- (void) analogButtonChanged:(WiiButtonType)type amount:(unsigned)press wiiRemote:(WiiRemote*)wiiRemote;
- (void) wiiRemoteDisconnected:(IOBluetoothDevice*)device;

// dtkDeviceWii delegation

- (void) setParent:(dtkDeviceWiiPrivate *)device;

@end

#endif
