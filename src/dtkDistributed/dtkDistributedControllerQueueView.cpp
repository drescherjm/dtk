/* dtkDistributedControllerQueueView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 11 17:02:06 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 11 17:06:06 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerQueueView.h"

class dtkDistributedControllerQueueViewPrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedControllerQueueView::dtkDistributedControllerQueueView(QWidget *parent) : QListWidget(parent), d(new dtkDistributedControllerQueueViewPrivate)
{
    d->controller = NULL;
}

dtkDistributedControllerQueueView::~dtkDistributedControllerQueueView(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerQueueView::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}
