/* dtkDistributedNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:22:24 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mer. avril 25 16:18:30 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 75
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

#include "dtkDistributedSupportExport.h"
#include "dtkDistributedCpu"
#include "dtkDistributedGpu"

class dtkDistributedNodePrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedNode : public QObject
{
    Q_OBJECT

public:
     dtkDistributedNode(void);
    ~dtkDistributedNode(void);

    enum Network {
           Ethernet1G = 0x01,
          Ethernet10G = 0x02,
            Myrinet2G = 0x04,
           Myrinet10G = 0x08,
        Infiniband10G = 0x10,
        Infiniband20G = 0x20,
        Infiniband40G = 0x40
    };

    Q_DECLARE_FLAGS(Networks, Network)

    enum State {
        Free    = 0x1,
        Busy    = 0x2,
        Down    = 0x4,
        StandBy = 0x8,
        Absent  = 0x16
    };

    Q_DECLARE_FLAGS(States, State)

    enum Brand {
          Hp = 0x1,
         Ibm = 0x2,
        Dell = 0x4,
       Carri = 0x8,
         Sun = 0x16,
       Apple = 0x32
    };

    Q_DECLARE_FLAGS(Brands, Brand)

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

Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributedNode::Networks)
Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributedNode::States)
Q_DECLARE_OPERATORS_FOR_FLAGS(dtkDistributedNode::Brands)

#endif
