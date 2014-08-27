/* dtkDistributedServiceWin_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu May 26 10:45:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 10:47:13 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVICEWIN_P_H
#define DTKDISTRIBUTEDSERVICEWIN_P_H

#include <QtCore>

typedef bool (*EventFilter)(void *message, long *result);

class dtkDistributedServiceSysPrivate;

class dtkDistributedServiceControllerHandler : public QObject
{
    Q_OBJECT

public:
    dtkDistributedServiceControllerHandler(dtkDistributedServiceSysPrivate *sys);

protected:
    void customEvent(QEvent *e);

private:
    dtkDistributedServiceSysPrivate *d_sys;
};

#endif
