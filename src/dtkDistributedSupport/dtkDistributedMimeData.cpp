/* dtkDistributedMimeData.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 12 11:36:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 12 11:46:50 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedController.h"
#include "dtkDistributedMimeData.h"

class dtkDistributedMimeDataPrivate
{
public:
    dtkDistributedController *controller;
};

dtkDistributedMimeData::dtkDistributedMimeData(void) : QMimeData(), d(new dtkDistributedMimeDataPrivate)
{
    d->controller = NULL;
}

dtkDistributedMimeData::~dtkDistributedMimeData(void)
{
    delete d;

    d = NULL;
}

dtkDistributedController *dtkDistributedMimeData::controller(void)
{
    return d->controller;
}

void dtkDistributedMimeData::setController(dtkDistributedController *controller)
{
    d->controller = controller;
}
