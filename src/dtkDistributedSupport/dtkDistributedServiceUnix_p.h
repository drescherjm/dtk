/* dtkDistributedServiceUnix_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu May 26 10:49:36 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 26 11:10:51 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVICEUNIX_P_H
#define DTKDISTRIBUTEDSERVICEUNIX_P_H

#include "dtkDistributedService.h"
#include "dtkDistributedUnixServerSocket.h"

#include <QtCore>

class dtkDistributedServiceSysPrivate : public dtkDistributedUnixServerSocket
{
    Q_OBJECT

public:
     dtkDistributedServiceSysPrivate(void);
    ~dtkDistributedServiceSysPrivate(void);

    char *ident;

    dtkDistributedServiceBase::ServiceFlags serviceFlags;

protected:
    void incomingConnection(int socketDescriptor);

private slots:
    void slotReady(void);
    void slotClosed(void);

private:
    QString getCommand(const QTcpSocket *socket);

private:
    QMap<const QTcpSocket *, QString> cache;
};

#endif
