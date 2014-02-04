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

#include <dtkComposerSupportExport.h>
#include <dtkCoreSupport/dtkGlobal.h>

#include <dtkComposerControlsListItemReal.h>
#include <dtkComposerNodeReal.h>


class dtkComposerControlsListItemRealPrivate
{
public:
    QListWidget *parent;

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeReal *r_node;

public:
    QDoubleSpinBox *spin_d;
};

dtkComposerControlsListItemReal::dtkComposerControlsListItemReal(QListWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent,node), d(new dtkComposerControlsListItemRealPrivate)
{
    d->node = node;

    if (dtkComposerNodeReal *r_node = dynamic_cast<dtkComposerNodeReal *>(d->node->wrapee()))
        d->r_node = r_node;
    else
        dtkError() << "Not a real node, can't create control list item";

    d->parent = parent;
}


dtkComposerControlsListItemReal::~dtkComposerControlsListItemReal(void )
{
    delete d;
    d = NULL;
}

QWidget *dtkComposerControlsListItemReal::widget(void)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    QFrame *frame = new QFrame(d->parent);
    frame->setLayout(layout);
    layout->addWidget(new QLabel(d->node->title(), frame));

    d->spin_d  = new QDoubleSpinBox(frame);
    d->spin_d->setMinimum(-9999999);
    d->spin_d->setMaximum(+9999999);
    d->spin_d->setSingleStep(1);
    d->spin_d->setEnabled(true);
    d->spin_d->setValue(d->r_node->value());
    QObject::connect(d->spin_d, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));

    layout->addWidget(d->spin_d);
    return frame;
}

void dtkComposerControlsListItemReal::onValueChanged(double value)
{
    d->r_node->setValue(value);
}


