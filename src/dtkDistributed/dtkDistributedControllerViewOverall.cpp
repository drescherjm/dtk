/* dtkDistributedControllerViewOverall.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 14:47:08 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
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

dtkDistributedControllerViewOverall::dtkDistributedControllerViewOverall(QWidget *parent) : QTreeWidget(parent), d(new dtkDistributedControllerViewOverallPrivate)
{
    d->controller = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
    this->setHeaderLabels(QStringList() << "Core" << "Node" << "Status");
    this->viewport()->setStyleSheet("background-color: #dfe4ea; border-right: 1px solid lightGray;");
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
