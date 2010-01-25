#import "dtkDeviceWiiDelegate.h"

// #define NSLOG

@implementation dtkDeviceWiiDelegate

// /////////////////////////////////////////////////////////////////
// WiiRemoteDiscovery delegation
// /////////////////////////////////////////////////////////////////

- (void) WiiRemoteDiscovered:(WiiRemote*)wiimote
{
     self->parent->remote = wiimote;    
    [self->parent->remote setDelegate:self];

    [self->parent->remote setIRSensorEnabled:NO];
    [self->parent->remote setForceFeedbackEnabled:NO];
    [self->parent->remote setMotionSensorEnabled:NO];
    [self->parent->remote setExpansionPortEnabled:NO];
    [self->parent->remote setLEDEnabled1:NO enabled2:NO enabled3:NO enabled4:NO];

     self->parent->discovered();

#if defined(NSLOG)
    NSLog(@"Discovered, battery level is %d", [self->parent->remote batteryLevel]);
#endif
}

- (void) WiiRemoteDiscoveryError:(int)code
{
    (void)code;

#if defined(NSLOG)
    switch(code) {
    case 56:
        NSLog(@"Make sure to turn bluetooth on.");
        break;
    default:
        NSLog(@"Discovery error: %d", code);
        break;
    }
#endif
}

// /////////////////////////////////////////////////////////////////
// WiiRemote delegation
// /////////////////////////////////////////////////////////////////

- (void) irPointMovedX:(float)px Y:(float)py wiiRemote:(WiiRemote*)wiiRemote
{
    (void)px;
    (void)py;
    (void)wiiRemote;

    self->parent->runInfraredCursorMotionHandlers(px, py);

#if defined(NSLOG)
    NSLog(@"irPointMoved: (%d, %d)", px, py);
#endif
}

- (void) rawIRData: (IRData[4])irData wiiRemote:(WiiRemote*)wiiRemote
{
    (void)irData;
    (void)wiiRemote;

    self->parent->runInfraredSingleMotionHandlers(irData[0].x, irData[0].y, irData[0].s, 0);
    self->parent->runInfraredSingleMotionHandlers(irData[1].x, irData[1].y, irData[1].s, 1);
    self->parent->runInfraredSingleMotionHandlers(irData[2].x, irData[2].y, irData[2].s, 2);
    self->parent->runInfraredSingleMotionHandlers(irData[3].x, irData[3].y, irData[3].s, 3);

#if defined(NSLOG)
    NSLog(@"rawIRData: (%d, %d, %d, %d), (%d, %d, %d, %d), (%d, %d, %d, %d), (%d, %d, %d, %d)",
          irData[0].x, irData[0].y, irData[0].s,
          irData[1].x, irData[1].y, irData[1].s,
          irData[2].x, irData[2].y, irData[2].s,
          irData[3].x, irData[3].y, irData[3].s);
#endif
}

- (void) buttonChanged:(WiiButtonType)type isPressed:(BOOL)isPressed wiiRemote:(WiiRemote*)wiiRemote
{
    (void)type;
    (void)isPressed;
    (void)wiiRemote;

#if defined(NSLOG)
    if(isPressed)
        NSLog(@"button %d pressed", type);
    else
        NSLog(@"button %d released", type);
#endif

    if (isPressed)
        self->parent->buttonPressed(type);
    else
        self->parent->buttonReleased(type);
}

- (void) accelerationChanged:(WiiAccelerationSensorType)type accX:(unsigned char)accX accY:(unsigned char)accY accZ:(unsigned char)accZ wiiRemote:(WiiRemote*)wiiRemote
{
    (void)type;
    (void)accX;
    (void)accY;
    (void)accZ;
    (void)wiiRemote;

    if (type == WiiRemoteAccelerationSensor)
        self->parent->runRemoteAccelerationHandlers(accX, accY, accZ);
    else
        self->parent->runNunchukAccelerationHandlers(accX, accY, accZ);

#if defined(NSLOG)
    NSLog(@"accelerationChanged: %d, %d, %d, %d", type, accX, accY, accZ);
#endif
}

- (void) joyStickChanged:(WiiJoyStickType)type tiltX:(unsigned char)tiltX tiltY:(unsigned char)tiltY wiiRemote:(WiiRemote*)wiiRemote
{
    (void)type;
    (void)tiltX;
    (void)tiltY;
    (void)wiiRemote;

    self->parent->runJoystickMotionHandlers(tiltX, tiltY);

#if defined(NSLOG)
    NSLog(@"Joystickchanged: %d, %d, %d", type, tiltX, tiltY);
#endif
}

- (void) analogButtonChanged:(WiiButtonType)type amount:(unsigned)press wiiRemote:(WiiRemote*)wiiRemote
{
    (void)type;
    (void)press;
    (void)wiiRemote;

#if defined(NSLOG)
    NSLog(@"analogButtonChanged: %d, %d", type, press);
#endif
}

- (void) wiiRemoteDisconnected:(IOBluetoothDevice*)device
{
    (void)device;

#if defined(NSLOG)
    NSLog(@"wiiRemoteDisconnected");
#endif
}

// /////////////////////////////////////////////////////////////////
// dtkDeviceWii delegation
// /////////////////////////////////////////////////////////////////

- (void) setParent:(dtkDeviceWiiPrivate *)device
{
    self->parent = device;
}

@end
