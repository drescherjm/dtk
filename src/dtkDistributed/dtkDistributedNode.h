/* dtkDistributedNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:22:24 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 22 10:52:44 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 30
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

    enum Brand {
        Hp,
        Ibm,
        Dell
    };

    QList<Network> networks(void);

    QList<dtkDistributedCpu *> cpus(void);
    QList<dtkDistributedGpu *> gpus(void);

    QString name(void) const;
    Network network(void);
    State state(void);
    Brand brand(void);
    void setName(const QString& name);
    void setNetwork(Network network);
    void setState(State state);
    void setBrand(Brand brand);

    void operator << (dtkDistributedCpu *cpu);
    void operator << (dtkDistributedGpu *gpu);

private:
    dtkDistributedNodePrivate *d;
};

#endif
