/* dtkNotification.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 19 21:39:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 12:35:33 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKNOTIFICATION_H
#define DTKNOTIFICATION_H

#include "dtkNotificationExport.h"
#include "dtkNotificationEvent.h"

// /////////////////////////////////////////////////////////////////
// Helper enumerations
// /////////////////////////////////////////////////////////////////

static const int dtkNotificationEventType = QEvent::User + 1003;

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

DTKNOTIFICATION_EXPORT void dtkNotify(const QString& message);
DTKNOTIFICATION_EXPORT void dtkNotify(const QString& message, int duration);
DTKNOTIFICATION_EXPORT void dtkNotify(dtkNotificationEvent *event);
DTKNOTIFICATION_EXPORT void dtkClearNotifications(void);

#endif
