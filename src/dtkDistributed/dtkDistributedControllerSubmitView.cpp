/* dtkDistributedControllerSubmitView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:53:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 11 12:39:22 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerSubmitView.h"

class dtkDistributedControllerSubmitViewPrivate
{
public:
    QSpinBox *node_spin;
    QSpinBox *ppn_spin;
    QPushButton *submit_button;
};

dtkDistributedControllerSubmitView::dtkDistributedControllerSubmitView(QWidget *parent) : QFrame(parent), d(new dtkDistributedControllerSubmitViewPrivate)
{
    d->node_spin = new QSpinBox(this);
    d->node_spin->setMinimum(1);
    d->node_spin->setMaximum(500);
    d->node_spin->setSingleStep(1);
    d->node_spin->setValue(1);
    d->node_spin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    d->ppn_spin = new QSpinBox(this);
    d->ppn_spin->setMinimum(1);
    d->ppn_spin->setMaximum(500);
    d->ppn_spin->setSingleStep(1);
    d->ppn_spin->setValue(1);
    d->ppn_spin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    d->submit_button = new QPushButton("Submit", this);
    
    QFormLayout *layout = new QFormLayout(this);
    layout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    layout->addRow("Nodes", d->node_spin);
    layout->addRow("Process per node", d->ppn_spin);
    layout->addRow(d->submit_button);
    
    connect(d->submit_button, SIGNAL(clicked()), this, SLOT(onSubmit()));
}

dtkDistributedControllerSubmitView::~dtkDistributedControllerSubmitView(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedControllerSubmitView::onSubmit(void)
{
    qDebug() << __func__;
}
