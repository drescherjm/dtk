/* dtkNotificationStack.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Apr 22 15:11:20 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 14:07:01 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKNOTIFICATIONSTACK_H
#define DTKNOTIFICATIONSTACK_H

#include "dtkNotificationExport.h"

#include <QtCore>

class dtkNotifiable;
class dtkNotificationEvent;
class dtkNotificationStackPrivate;

class DTKNOTIFICATION_EXPORT dtkNotificationStack : public QObject
{
    Q_OBJECT

public:
     dtkNotificationStack(QObject *parent = 0);
    ~dtkNotificationStack(void);

public:
    void registerNotifiable(dtkNotifiable *notifiable);

public:
    void dismiss(void);

public:
    void push(dtkNotificationEvent *event);

protected slots:
    void idle(void);

private:
    dtkNotificationStackPrivate *d;
};

#endif
