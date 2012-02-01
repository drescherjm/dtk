/* dtkCreatorMainWindow.mm --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  1 12:29:47 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 14:41:27 2012 (+0100)
 *           By: David Rey
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorMainWindow.h"
#include "dtkCreatorMainWindow_p.h"

#import <Cocoa/Cocoa.h>

#if defined(Q_WS_MAC) && (MAC_OS_X_VERSION_MAX_ALLOWED > MAC_OS_X_VERSION_10_6)

void dtkCreatorMainWindowPrivate::enableFullScreenSupport(void)
{
    NSView *nsview = (NSView *) q->winId();	
    NSWindow *nswindow = [nsview window];
    [nswindow setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];
}

#endif
