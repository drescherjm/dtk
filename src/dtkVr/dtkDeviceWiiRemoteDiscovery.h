/* dtkDeviceWiiRemoteDiscovery.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 13:02:50 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 25 13:03:05 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * See credits at EOF.
 */

/* Change log:
 * 
 */

#import <Cocoa/Cocoa.h>
#import <IOBluetooth/objc/IOBluetoothDeviceInquiry.h> 
#import "dtkDeviceWiiRemote.h"

@interface WiiRemoteDiscovery : NSObject
{
    IOBluetoothDeviceInquiry* inquiry;
    id _delegate;
}

+ (WiiRemoteDiscovery*) discoveryWithDelegate:(id)delegate;
- (void) setDelegate:(id)delegate;
- (IOReturn)start;
- (IOReturn)stop;

@end

@interface NSObject(WiiRemoteDiscoveryDelegate)

- (void) WiiRemoteDiscovered:(WiiRemote*)wiimote;
- (void) WiiRemoteDiscoveryError:(int)code;

@end;

//
//  WiiRemoteDiscovery.h
//  DarwiinRemote
//
//  Created by Ian Rickard on 12/9/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//
