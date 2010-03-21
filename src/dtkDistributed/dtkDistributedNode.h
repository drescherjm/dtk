/* dtkDistributedNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:22:24 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 23:24:28 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDNODE_H
#define DTKDISTRIBUTEDNODE_H

#include <QtCore>

#include "dtkDistributedExport.h"

class dtkDistributedCpu;
class dtkDistributedGpu;
class dtkDistributedNodePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedNode : public QObject
{
    Q_OBJECT

public:
     dtkDistributedNode(void);
    ~dtkDistributedNode(void);

    enum Network {
        Ethernet1G,
        Ethernet10G,
        Myrinet2G,
        Myrinet10G,
        Infiniband10G,
        Infiniband20G,
        Infiniband40G
    };

    enum State {
        Free,
        JobExclusive,
        Down,
        Offline
    };

    QList<Network> networks(void);

    QList<dtkDistributedCpu *> cpus(void);
    QList<dtkDistributedGpu *> gpus(void);

    QString name(void) const;
    State state(void);

    void setName(const QString& name);
    void setState(State state);

private:
    dtkDistributedNodePrivate *d;
};

#endif
