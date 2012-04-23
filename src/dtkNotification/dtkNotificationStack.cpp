/* dtkNotificationStack.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Apr 22 15:13:24 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 22:03:56 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 129
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkNotifiable.h"
#include "dtkNotification.h"
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

public:
    QTimer     persistent_timer;
    QTimer non_persistent_timer;
};

dtkNotificationStack *dtkNotificationStack::instance(void)
{
    if(!s_instance)
        s_instance = new dtkNotificationStack;

    return s_instance;
}

dtkNotificationStack::dtkNotificationStack(QObject *parent) : QObject(parent), d(new dtkNotificationStackPrivate)
{
        d->persistent_timer.setSingleShot(true);
    d->non_persistent_timer.setSingleShot(true);

    connect(    &(d->persistent_timer), SIGNAL(timeout()), this, SLOT(idle()));
    connect(&(d->non_persistent_timer), SIGNAL(timeout()), this, SLOT(idle()));
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

void dtkNotificationStack::dismiss(void)
{
    d->non_persistent_timer.stop();

    this->idle();
}

void dtkNotificationStack::push(dtkNotificationEvent *event)
{
    dtkNotificationEvent e = (*event);

    switch(event->type()) {
    case dtkNotificationEvent::Persistent:
        d->persistent.push_front(dtkNotificationEvent(e));
        this->idle();
        break;
    case dtkNotificationEvent::NonPersistent:
        d->non_persistent.push_front(dtkNotificationEvent(e));
        d->persistent_timer.stop();
        this->idle();
        break;
    }
}

void dtkNotificationStack::idle(void)
{
   foreach(dtkNotifiable *notifiable, d->notifiables) {
       notifiable->setPersistentCount(d->persistent.count());
       notifiable->setNonPersistentCount(d->non_persistent.count());
   }

    if(d->non_persistent_timer.isActive())
        return;
    
    foreach(dtkNotifiable *notifiable, d->notifiables) {
        notifiable->clear();
        notifiable->dismissible(false);
    }

    if(!d->non_persistent.isEmpty()) {
        
        dtkNotificationEvent event = d->non_persistent.pop();
        
        foreach(dtkNotifiable *notifiable, d->notifiables) {

            notifiable->display(event.message());
            notifiable->setNonPersistentCount(d->non_persistent.count());
            notifiable->dismissible(true);
        }

        d->non_persistent_timer.start(event.duration());

        return;
    }

    if(!d->persistent.isEmpty()) {

        dtkNotificationEvent event = d->persistent.pop();
        
        foreach(dtkNotifiable *notifiable, d->notifiables)
            notifiable->display(event.message());

        d->persistent.push_front(event);

        d->persistent_timer.start(DTK_NOTIFICATION_PERSISTENT_DURATION);

        return;
    }
}

bool dtkNotificationStack::event(QEvent *event)
{
    if(event->type() != dtkNotificationEventType)
        return QObject::event(event);

    this->push(static_cast<dtkNotificationEvent *>(event));

    return true;
}

dtkNotificationStack *dtkNotificationStack::s_instance = NULL;
