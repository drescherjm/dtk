/* dtkNotification.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 19 21:48:39 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 16:30:15 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkNotification.h"
#include "dtkNotificationStack.h"

#include <QtGui>

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
    // foreach (QWidget *widget, QApplication::topLevelWidgets())
    // QApplication::postEvent(widget, event);

    QApplication::postEvent(dtkNotificationStack::instance(), event);
}
