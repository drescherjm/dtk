/* dtkDistributedControllerViewOverall.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 13:25:26 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerViewOverall.h"

class dtkDistributedControllerViewOverallPrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedControllerViewOverall::dtkDistributedControllerViewOverall(QWidget *parent) : QWidget(parent), d(new dtkDistributedControllerViewOverallPrivate)
{
    d->controller = NULL;
}

dtkDistributedControllerViewOverall::~dtkDistributedControllerViewOverall(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerViewOverall::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}
