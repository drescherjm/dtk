/* dtkNotificationStack.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Apr 22 15:13:24 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 11:59:23 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 58
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkNotifiable.h"
#include "dtkNotificationEvent.h"
#include "dtkNotificationStack.h"

#define DTK_NOTIFICATION_PERSISTENT_DURATION 10000

class dtkNotificationStackPrivate
{
public:
    QStack<dtkNotificationEvent>     persistent;
    QStack<dtkNotificationEvent> non_persistent;

public:
    QList<dtkNotifiable *> notifiables;
};

dtkNotificationStack::dtkNotificationStack(QObject *parent) : QObject(parent), d(new dtkNotificationStackPrivate)
{
    
}

dtkNotificationStack::~dtkNotificationStack(void)
{
    d->persistent.clear();
    d->non_persistent.clear();

    delete d;

    d = NULL;
}

void dtkNotificationStack::registerNotifiable(dtkNotifiable *notifiable)
{
    d->notifiables << notifiable;
}

void dtkNotificationStack::push(dtkNotificationEvent *event)
{
    dtkNotificationEvent e = (*event);

    switch(event->type()) {
    case dtkNotificationEvent::Persistent:
        d->persistent.push(dtkNotificationEvent(e));
        this->idle();
        break;
    case dtkNotificationEvent::NonPersistent:
        d->non_persistent.push(dtkNotificationEvent(e));
        this->idle();
        break;
    }
}

void dtkNotificationStack::idle(void)
{
    foreach(dtkNotifiable *notifiable, d->notifiables)
        notifiable->clear();

    if(!d->non_persistent.isEmpty()) {

        dtkNotificationEvent event = d->non_persistent.pop();
        
        foreach(dtkNotifiable *notifiable, d->notifiables)
            notifiable->display(event.message());
        
        QTimer::singleShot(event.duration(), this, SLOT(idle()));

        return;
    }

    if(!d->persistent.isEmpty()) {

        dtkNotificationEvent event = d->persistent.pop();
        
        foreach(dtkNotifiable *notifiable, d->notifiables)
            notifiable->display(event.message());

        d->persistent.push_front(event);

        QTimer::singleShot(DTK_NOTIFICATION_PERSISTENT_DURATION, this, SLOT(idle()));

        return;
    }
}
