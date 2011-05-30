/* dtkDistributedControllerViewFiltering.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 13:47:14 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
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

    QComboBox *filter_a = new QComboBox(this);
    QComboBox *filter_b = new QComboBox(this);
    QComboBox *filter_c = new QComboBox(this);
    QComboBox *filter_d = new QComboBox(this);

    QHBoxLayout *filter_layout = new QHBoxLayout(this);
    filter_layout->setContentsMargins(0, 0, 0, 0);
    filter_layout->setSpacing(0);
    filter_layout->addWidget(filter_a);
    filter_layout->addWidget(filter_b);
    filter_layout->addWidget(filter_c);
    filter_layout->addWidget(filter_d);
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
