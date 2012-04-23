/* dtkNotificationDisplay.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:06:30 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 23 16:11:44 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 37
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

class DTKNOTIFICATION_EXPORT dtkNotificationDisplay : public QFrame, public dtkNotifiable
{
    Q_OBJECT    

public:
     dtkNotificationDisplay(QWidget *parent = 0);
    ~dtkNotificationDisplay(void);

public slots:
    void clear(void);
    void dismiss(void);
    void dismissible(bool dismissible);
    void display(const QString& message);
    void setPersistentCount(int count);
    void setNonPersistentCount(int count);

public:
    QSize sizeHint(void) const;

private:
    dtkNotificationDisplayPrivate *d;
};

#endif
