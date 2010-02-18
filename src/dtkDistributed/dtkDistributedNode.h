/* dtkDistributedNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:22:24 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 14:10:30 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
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
        dtkDistributedNodeEthernet1G,
        dtkDistributedNodeEthernet10G,
        dtkDistributedNodeMyrinet2G,
        dtkDistributedNodeMyrinet10G,
        dtkDistributedNodeInfiniband10G,
        dtkDistributedNodeInfiniband20G,
        dtkDistributedNodeInfiniband40G
    };

    QList<Network> networks(void);

    QList<dtkDistributedCpu *> cpus(void);
    QList<dtkDistributedGpu *> gpus(void);

private:
    dtkDistributedNodePrivate *d;
};

#endif
