/* dtkDistributedControllerViewDetailed.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 09:50:20 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
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

dtkDistributedControllerViewDetailed::dtkDistributedControllerViewDetailed(QWidget *parent) : QListWidget(parent), d(new dtkDistributedControllerViewDetailedPrivate)
{
    d->controller = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
