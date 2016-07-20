/* dtkNotificationEvent.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 19 20:33:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:29:05 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 37
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKNOTIFICATIONEVENT_H
#define DTKNOTIFICATIONEVENT_H

#include "dtkWidgetsExport.h"

#include <QtCore>

class dtkNotificationEventPrivate;

class DTKWIDGETS_EXPORT dtkNotificationEvent : public QEvent
{
public:
    enum Type {
        Persistent,
        NonPersistent
    };

public:
    dtkNotificationEvent(void);
    dtkNotificationEvent(const dtkNotificationEvent& other);
    ~dtkNotificationEvent(void);

public:
    dtkNotificationEvent& operator=(const dtkNotificationEvent& other);

public:
    Type type(void);
    QString message(void) const;
    int duration(void) const;

public:
    void setType(Type type);
    void setMessage(const QString& messqge);
    void setDuration(int ms);

private:
    dtkNotificationEventPrivate *d;
};

#endif
