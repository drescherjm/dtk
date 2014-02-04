/* dtkNotificationDisplay.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr 20 21:06:30 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:54:36 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 40
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
#include "dtkGuiSupportExport.h"

#include <QtWidgets>

class dtkNotificationDisplayPrivate;

class DTKGUISUPPORT_EXPORT dtkNotificationDisplay : public QFrame, public dtkNotifiable
{
    Q_OBJECT    

public:
     dtkNotificationDisplay(QWidget *parent = 0);
    ~dtkNotificationDisplay(void);

public slots:
    void clear(void);
    void next(void);
    void previous(void);
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
