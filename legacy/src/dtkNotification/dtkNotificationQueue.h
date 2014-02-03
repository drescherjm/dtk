/* dtkNotificationQueue.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Apr 22 15:11:20 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 01:07:22 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 36
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKNOTIFICATIONQUEUE_H
#define DTKNOTIFICATIONQUEUE_H

#include "dtkNotificationExport.h"

#include <QtCore>

class dtkNotifiable;
class dtkNotificationEvent;
class dtkNotificationQueuePrivate;

class DTKNOTIFICATION_EXPORT dtkNotificationQueue : public QObject
{
    Q_OBJECT

public:
    static dtkNotificationQueue *instance(void);

public:
    void registerNotifiable(dtkNotifiable *notifiable);

public:
    void clear(void);

public:
    void next(void);
    void previous(void);

public:
    void dismiss(void);

public:
    void push(dtkNotificationEvent *event);

protected slots:
    void idle(void);

public:
    bool event(QEvent *event);

private:
    static dtkNotificationQueue *s_instance;

private:
     dtkNotificationQueue(QObject *parent = 0);
    ~dtkNotificationQueue(void);

private:
    dtkNotificationQueuePrivate *d;
};

#endif
