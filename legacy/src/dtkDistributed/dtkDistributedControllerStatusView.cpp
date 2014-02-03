/* dtkDistributedControllerStatusView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 10 18:23:18 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerStatusModel.h"
#include "dtkDistributedControllerStatusView.h"

class dtkDistributedControllerStatusViewPrivate
{
public:
};

dtkDistributedControllerStatusView::dtkDistributedControllerStatusView(QWidget *parent) : QTreeView(parent), d(new dtkDistributedControllerStatusViewPrivate)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
}

dtkDistributedControllerStatusView::~dtkDistributedControllerStatusView(void)
{
    delete d;

    d = NULL;
}
