/* dtkDistributedControllerViewFiltering.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 13:23:45 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerViewFiltering.h"

class dtkDistributedControllerViewFilteringPrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedControllerViewFiltering::dtkDistributedControllerViewFiltering(QWidget *parent) : QWidget(parent), d(new dtkDistributedControllerViewFilteringPrivate)
{
    d->controller = NULL;
}

dtkDistributedControllerViewFiltering::~dtkDistributedControllerViewFiltering(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerViewFiltering::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}
