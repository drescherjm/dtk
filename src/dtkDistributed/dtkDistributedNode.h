/* dtkDistributedNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:22:24 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 15:11:04 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 40
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
           Ethernet1G = 0x1,
          Ethernet10G = 0x2,
            Myrinet2G = 0x4,
           Myrinet10G = 0x8,
        Infiniband10G = 0x16,
        Infiniband20G = 0x32,
        Infiniband40G = 0x64
    };

    enum State {
        Free = 0x1,
        Busy = 0x2,
        Down = 0x4
    };

    enum Brand {
          Hp = 0x1,
         Ibm = 0x2,
        Dell = 0x4,
       Carri = 0x8
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
