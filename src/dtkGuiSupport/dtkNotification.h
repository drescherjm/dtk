/* dtkNotification.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 19 21:39:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:28:15 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKNOTIFICATION_H
#define DTKNOTIFICATION_H

#include "dtkGuiSupportExport.h"
#include "dtkNotificationEvent.h"

// /////////////////////////////////////////////////////////////////
// Helper enumerations
// /////////////////////////////////////////////////////////////////

static const int dtkNotificationEventType = QEvent::User + 1003;

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

DTKGUISUPPORT_EXPORT void dtkNotify(const QString& message);
DTKGUISUPPORT_EXPORT void dtkNotify(const QString& message, int duration);
DTKGUISUPPORT_EXPORT void dtkNotify(dtkNotificationEvent *event);
DTKGUISUPPORT_EXPORT void dtkClearNotifications(void);

#endif
