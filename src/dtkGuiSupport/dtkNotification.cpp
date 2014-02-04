/* dtkNotification.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 19 21:48:39 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:55:09 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkNotification.h"
#include "dtkNotificationQueue.h"

#include <QtWidgets>

void dtkNotify(const QString& message)
{
    dtkNotificationEvent *event = new dtkNotificationEvent;
    event->setType(dtkNotificationEvent::Persistent);
    event->setMessage(message);

    dtkNotify(event);
}

void dtkNotify(const QString& message, int duration)
{
    dtkNotificationEvent *event = new dtkNotificationEvent;
    event->setType(dtkNotificationEvent::NonPersistent);
    event->setMessage(message);
    event->setDuration(duration);

    dtkNotify(event);
}

void dtkNotify(dtkNotificationEvent *event)
{
    QApplication::postEvent(dtkNotificationQueue::instance(), event);
}

void dtkClearNotifications(void)
{
    dtkNotificationQueue::instance()->clear();
}
