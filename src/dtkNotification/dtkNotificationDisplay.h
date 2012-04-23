/* dtkNotificationDisplay.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:06:30 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 11:54:12 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKNOTIFICATIONDISPLAY_H
#define DTKNOTIFICATIONDISPLAY_H

#include "dtkNotifiable.h"
#include "dtkNotificationExport.h"

#include <QtGui>

class dtkNotificationDisplayPrivate;

class DTKNOTIFICATION_EXPORT dtkNotificationDisplay : public QLabel, public dtkNotifiable
{
    Q_OBJECT

public:
     dtkNotificationDisplay(QWidget *parent = 0);
    ~dtkNotificationDisplay(void);

public:
    void clear(void);

public:
    void display(const QString& message);

public:
    QSize sizeHint(void) const;

public:
    bool event(QEvent *event);

private:
    dtkNotificationDisplayPrivate *d;
};

#endif
