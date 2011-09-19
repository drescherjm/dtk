/* dtkDistributedServerDaemon.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun  1 11:27:42 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. sept. 15 17:52:32 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVERDAEMON_H
#define DTKDISTRIBUTEDSERVERDAEMON_H

#include "dtkDistributedExport.h"
#include "dtkDistributedServerManager.h"

#include <QtCore>
#include <QtNetwork>

class dtkDistributedServerDaemonPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServerDaemon : public QTcpServer
{
    Q_OBJECT

public:
     dtkDistributedServerDaemon(quint16 port, QObject *parent = 0);
    ~dtkDistributedServerDaemon(void);

    void setManager(dtkDistributedServerManager::Type type);

    dtkDistributedServerManager *  manager(void);
    QByteArray wait(int rank);

protected:
    void incomingConnection(int descriptor);

private slots:
    void read(void);
    void discard(void);

private:
    dtkDistributedServerDaemonPrivate *d;
};

#endif
