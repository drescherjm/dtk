/* dtkDistributedControllerStatusView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul  4 13:58:48 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 30
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
    dtkDistributedControllerStatusModel *model;
};

dtkDistributedControllerStatusView::dtkDistributedControllerStatusView(QWidget *parent) : QTreeView(parent), d(new dtkDistributedControllerStatusViewPrivate)
{
    d->model = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
}

dtkDistributedControllerStatusView::~dtkDistributedControllerStatusView(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerStatusView::setModel(dtkDistributedControllerStatusModel *model)
{
    d->model = model;

    QTreeView::setModel(model);
}
