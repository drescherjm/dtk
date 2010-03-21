/* dtkDistributedNode.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:05:14 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 23:23:18 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
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

    dtkDistributedNode::State state;
};

dtkDistributedNode::dtkDistributedNode(void) : QObject(), d(new dtkDistributedNodePrivate)
{

}

dtkDistributedNode::~dtkDistributedNode(void)
{
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

dtkDistributedNode::State dtkDistributedNode::state(void)
{
    return d->state;
}

void dtkDistributedNode::setName(const QString& name)
{
    d->name = name;
}

void dtkDistributedNode::setState(dtkDistributedNode::State state)
{
    d->state = state;
}
