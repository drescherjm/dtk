/* dtkCreatorMainWindow.mm --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  1 12:29:47 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 15 14:52:15 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 15
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
