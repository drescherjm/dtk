/* dtkDistributorController.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Mar 31 18:26:44 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Mar 31 20:33:24 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributorController.h"

class dtkDistributorControllerPrivate
{
public:
    dtkDistributorController::Networks networks;
    dtkDistributorController::States states;
    dtkDistributorController::Brands brands;

    dtkDistributorController::Architectures architectures;
    dtkDistributorController::Models models;
    dtkDistributorController::Cardinalities cardinalities;
};

dtkDistributorController *dtkDistributorController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkDistributorController;

    return s_instance;
}

dtkDistributorController::dtkDistributorController(void) : QObject(), d(new dtkDistributorControllerPrivate)
{

}

dtkDistributorController::~dtkDistributorController(void)
{
    delete d;

    d = NULL;
}

dtkDistributorController::Networks dtkDistributorController::networks(void)
{
    return d->networks;
}

dtkDistributorController::States dtkDistributorController::states(void)
{
    return d->states;
}

dtkDistributorController::Brands dtkDistributorController::brands(void)
{
    return d->brands;
}

dtkDistributorController::Architectures dtkDistributorController::architectures(void)
{
    return d->architectures;
}

dtkDistributorController::Models dtkDistributorController::models(void)
{
    return d->models;
}

dtkDistributorController::Cardinalities dtkDistributorController::cardinalities(void)
{
    return d->cardinalities;
}

void dtkDistributorController::toggle(int index, int flag, bool checked)
{
    if(index == 0)
        checked ? d->states |= (dtkDistributedNode::State)flag : d->states &= ~States((dtkDistributedNode::State)flag);

    if(index == 1)
        checked ? d->brands |= (dtkDistributedNode::Brand)flag : d->brands &= ~Brands((dtkDistributedNode::Brand)flag);

    if(index == 2)
        checked ? d->networks |= (dtkDistributedNode::Network)flag : d->networks &= ~Networks((dtkDistributedNode::Network)flag);

    if(index == 3)
        checked ? d->cardinalities |= (dtkDistributedCpu::Cardinality)flag : d->cardinalities &= ~Cardinalities((dtkDistributedCpu::Cardinality)flag);

    if(index == 4)
        checked ? d->architectures |= (dtkDistributedCpu::Architecture)flag : d->architectures &= ~Architectures((dtkDistributedCpu::Architecture)flag);

    if(index == 5)
        checked ? d->models |= (dtkDistributedCpu::Model)flag : d->models &= ~Models((dtkDistributedCpu::Model)flag);

    emit updated();
}

dtkDistributorController *dtkDistributorController::s_instance = NULL;
