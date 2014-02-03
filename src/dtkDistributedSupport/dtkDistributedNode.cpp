/* dtkDistributedNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:05:14 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Apr  6 14:36:00 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedNode.h"

class dtkDistributedNodePrivate
{
public:
    QList<dtkDistributedNode::Network> networks;
    QList<dtkDistributedCpu *> cpus;
    QList<dtkDistributedGpu *> gpus;
    QString name;

    dtkDistributedNode::Network network;
    dtkDistributedNode::State state;
    dtkDistributedNode::Brand brand;
};

dtkDistributedNode::dtkDistributedNode(void) : QObject(), d(new dtkDistributedNodePrivate)
{

}

dtkDistributedNode::~dtkDistributedNode(void)
{
    qDeleteAll(d->cpus);
    qDeleteAll(d->gpus);

    delete d;

    d = NULL;
}

QList<dtkDistributedNode::Network> dtkDistributedNode::networks(void)
{
    return d->networks;
}

QList<dtkDistributedCpu *> dtkDistributedNode::cpus(void)
{
    return d->cpus;
}

QList<dtkDistributedGpu *> dtkDistributedNode::gpus(void)
{
    return d->gpus;
}

QString dtkDistributedNode::name(void) const
{
    return d->name;
}

dtkDistributedNode::Network dtkDistributedNode::network(void)
{
    return d->network;
}

dtkDistributedNode::State dtkDistributedNode::state(void)
{
    return d->state;
}

dtkDistributedNode::Brand dtkDistributedNode::brand(void)
{
    return d->brand;
}

void dtkDistributedNode::setName(const QString& name)
{
    d->name = name;
}

void dtkDistributedNode::setNetwork(dtkDistributedNode::Network network)
{
    d->network = network;
}

void dtkDistributedNode::setState(dtkDistributedNode::State state)
{
    d->state = state;
}

void dtkDistributedNode::setBrand(dtkDistributedNode::Brand brand)
{
    d->brand = brand;
}

void dtkDistributedNode::operator << (dtkDistributedCpu *cpu)
{
    d->cpus << cpu;
}

void dtkDistributedNode::operator << (dtkDistributedGpu *gpu)
{
    d->gpus << gpu;
}
