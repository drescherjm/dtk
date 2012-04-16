/* dtkDistributedControllerStatusModelFilter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 15:53:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 11 12:12:24 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 138
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerStatusModelFilter.h"

class dtkDistributedControllerStatusModelFilterPrivate
{
public:
    QFlags<dtkDistributedNode::Network> network_flags;
    QFlags<dtkDistributedNode::State> state_flags;
    QFlags<dtkDistributedNode::Brand> brand_flags;
    QFlags<dtkDistributedCpu::Architecture> arch_flags;
    QFlags<dtkDistributedCpu::Model> model_flags;
};

dtkDistributedControllerStatusModelFilter::dtkDistributedControllerStatusModelFilter(QObject *parent) : QSortFilterProxyModel(parent), d(new dtkDistributedControllerStatusModelFilterPrivate)
{
    this->setDynamicSortFilter(true);
}

dtkDistributedControllerStatusModelFilter::~dtkDistributedControllerStatusModelFilter(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerStatusModelFilter::setNetworkFlags(QFlags<dtkDistributedNode::Network> flags)
{
    d->network_flags = flags;

    this->invalidateFilter();
}

void dtkDistributedControllerStatusModelFilter::setStateFlags(QFlags<dtkDistributedNode::State> flags)
{
    d->state_flags = flags;

    this->invalidateFilter();
}

void dtkDistributedControllerStatusModelFilter::setBrandFlags(QFlags<dtkDistributedNode::Brand> flags)
{
    d->brand_flags = flags;

    this->invalidateFilter();
}

void dtkDistributedControllerStatusModelFilter::setArchFlags(QFlags<dtkDistributedCpu::Architecture> flags)
{
    d->arch_flags = flags;

    this->invalidateFilter();
}

void dtkDistributedControllerStatusModelFilter::setModelFlags(QFlags<dtkDistributedCpu::Model> flags)
{
    d->model_flags = flags;

    this->invalidateFilter();
}

bool dtkDistributedControllerStatusModelFilter::filterAcceptsRow(int row, const QModelIndex& parent) const
{   
    QModelIndex n_index = sourceModel()->index(row, 1, parent);
    QModelIndex s_index = sourceModel()->index(row, 2, parent);
    QModelIndex b_index = sourceModel()->index(row, 3, parent);
    QModelIndex a_index = sourceModel()->index(row, 4, parent);
    QModelIndex m_index = sourceModel()->index(row, 5, parent);

    if((int)(d->network_flags)) {

        if(sourceModel()->data(n_index).toString() == "Ethernet1G" && !d->network_flags.testFlag(dtkDistributedNode::Ethernet1G))
            return false;

       if(sourceModel()->data(n_index).toString() == "Ethernet10G" && !d->network_flags.testFlag(dtkDistributedNode::Ethernet10G))
            return false;

       if(sourceModel()->data(n_index).toString() == "Myrinet2G" && !d->network_flags.testFlag(dtkDistributedNode::Myrinet2G))
            return false;

       if(sourceModel()->data(n_index).toString() == "Myrinet10G" && !d->network_flags.testFlag(dtkDistributedNode::Myrinet10G))
            return false;

       if(sourceModel()->data(n_index).toString() == "Infiniband10G" && !d->network_flags.testFlag(dtkDistributedNode::Infiniband10G))
            return false;

       if(sourceModel()->data(n_index).toString() == "Infiniband20G" && !d->network_flags.testFlag(dtkDistributedNode::Infiniband20G))
            return false;

        if(sourceModel()->data(n_index).toString() == "Infiniband40G" && !d->network_flags.testFlag(dtkDistributedNode::Infiniband40G))
            return false;
    }

    if((int)(d->state_flags)) {

        if(sourceModel()->data(s_index).toString() == "Free" && !d->state_flags.testFlag(dtkDistributedNode::Free))
            return false;

        if(sourceModel()->data(s_index).toString() == "Busy" && !d->state_flags.testFlag(dtkDistributedNode::Busy))
            return false;

        if(sourceModel()->data(s_index).toString() == "Down" && !d->state_flags.testFlag(dtkDistributedNode::Down))
            return false;
    }

    if((int)(d->brand_flags)) {

        if(sourceModel()->data(b_index).toString() == "Hp" && !d->brand_flags.testFlag(dtkDistributedNode::Hp))
            return false;

        if(sourceModel()->data(b_index).toString() == "Ibm" && !d->brand_flags.testFlag(dtkDistributedNode::Ibm))
            return false;

        if(sourceModel()->data(b_index).toString() == "Dell" && !d->brand_flags.testFlag(dtkDistributedNode::Dell))
            return false;

        if(sourceModel()->data(b_index).toString() == "Carri" && !d->brand_flags.testFlag(dtkDistributedNode::Carri))
            return false;
    }

    if((int)(d->arch_flags)) {

        if(sourceModel()->data(a_index).toString() == "x86" && !d->arch_flags.testFlag(dtkDistributedCpu::x86))
            return false;

        if(sourceModel()->data(a_index).toString() == "x86_64" && !d->arch_flags.testFlag(dtkDistributedCpu::x86_64))
            return false;
    }

    if((int)(d->model_flags)) {

        if(sourceModel()->data(m_index).toString() == "Xeon" && !d->model_flags.testFlag(dtkDistributedCpu::Xeon))
            return false;

        if(sourceModel()->data(m_index).toString() == "Opteron" && !d->model_flags.testFlag(dtkDistributedCpu::Opteron))
            return false;
    }

    return true;
}
