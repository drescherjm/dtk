/* dtkDistributedControllerViewFiltering.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:21:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 16:47:10 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 25
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

dtkDistributedControllerViewFiltering::dtkDistributedControllerViewFiltering(QWidget *parent) : QFrame(parent), d(new dtkDistributedControllerViewFilteringPrivate)
{
    d->controller = NULL;

    QComboBox *filter_a = new QComboBox(this);
    QComboBox *filter_b = new QComboBox(this);
    QComboBox *filter_c = new QComboBox(this);
    QComboBox *filter_d = new QComboBox(this);

    QHBoxLayout *filter_layout = new QHBoxLayout(this);
    filter_layout->setContentsMargins(10, 0, 0, 1);
    filter_layout->setSpacing(0);
    filter_layout->addWidget(new QLabel("Filters:", this));
    filter_layout->addWidget(filter_a);
    filter_layout->addWidget(filter_b);
    filter_layout->addWidget(filter_c);
    filter_layout->addWidget(filter_d);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setStyleSheet("border-bottom: 1px solid darkGray;");
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
