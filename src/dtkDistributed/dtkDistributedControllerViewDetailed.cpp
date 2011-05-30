/* dtkDistributedControllerViewDetailed.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 13:26:07 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerViewDetailed.h"

class dtkDistributedControllerViewDetailedPrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedControllerViewDetailed::dtkDistributedControllerViewDetailed(QWidget *parent) : QWidget(parent), d(new dtkDistributedControllerViewDetailedPrivate)
{
    d->controller = NULL;
}

dtkDistributedControllerViewDetailed::~dtkDistributedControllerViewDetailed(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerViewDetailed::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}
