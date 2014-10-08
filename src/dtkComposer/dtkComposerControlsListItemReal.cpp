/* @(#)dtkComposerControlsListItemReal.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/06/03 12:35:31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkComposerExport.h>

#include <dtkComposerControlsListItemReal.h>
#include <dtkComposerNodeReal.h>

#include "dtkComposerSceneNode.h"

#include <dtkLog>

class dtkComposerControlsListItemRealPrivate
{

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeReal *r_node;

public:
    QDoubleSpinBox *spin_d;
};

dtkComposerControlsListItemReal::dtkComposerControlsListItemReal(QWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent,node), d(new dtkComposerControlsListItemRealPrivate)
{
    d->node = node;

    if (dtkComposerNodeReal *r_node = dynamic_cast<dtkComposerNodeReal *>(d->node->wrapee()))
        d->r_node = r_node;
    else
        dtkError() << "Not a real node, can't create control list item";

    QFrame *frame = new QFrame;

    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(new QLabel(d->node->title(), frame));

    d->spin_d  = new QDoubleSpinBox(frame);
    d->spin_d->setMinimum(-9999999);
    d->spin_d->setMaximum(+9999999);
    d->spin_d->setDecimals(14);
    d->spin_d->setSingleStep(1);
    d->spin_d->setEnabled(true);
    d->spin_d->setValue(d->r_node->value());
    QObject::connect(d->spin_d, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));

    layout->addWidget(d->spin_d);
    this->setWidget(frame, qPrintable(d->node->title()));
}


dtkComposerControlsListItemReal::~dtkComposerControlsListItemReal(void )
{
    delete d;
    d = NULL;
}

void dtkComposerControlsListItemReal::onValueChanged(double value)
{
    d->r_node->setValue(value);
}

