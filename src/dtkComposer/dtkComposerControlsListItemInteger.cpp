/* @(#)dtkComposerControlsListItemInteger.cpp ---
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

#include "dtkComposerControlsListItemInteger.h"

#include "dtkComposerNodeInteger.h"

#include "dtkComposerExport.h"
#include <dtkCore/dtkGlobal.h>

class dtkComposerControlsListItemIntegerPrivate
{
public:
    QListWidget *parent;

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeInteger *i_node;

public:
    QSpinBox *spin_d;
};

dtkComposerControlsListItemInteger::dtkComposerControlsListItemInteger(QListWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent,node), d(new dtkComposerControlsListItemIntegerPrivate)
{
    d->node = node;

    if (dtkComposerNodeInteger *i_node = dynamic_cast<dtkComposerNodeInteger *>(d->node->wrapee()))
        d->i_node = i_node;
    else
        qDebug() << DTK_PRETTY_FUNCTION <<"Not an integer node, error";

    d->parent = parent;
}


dtkComposerControlsListItemInteger::~dtkComposerControlsListItemInteger(void )
{
    delete d;
    d= NULL;
}

QWidget *dtkComposerControlsListItemInteger::widget(void)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    QFrame *frame = new QFrame(d->parent);
    frame->setLayout(layout);
    layout->addWidget(new QLabel(d->node->title(), frame));

    d->spin_d  = new QSpinBox(frame);
    d->spin_d->setMinimum(-9999999);
    d->spin_d->setMaximum(+9999999);
    d->spin_d->setSingleStep(1);
    d->spin_d->setEnabled(true);
    d->spin_d->setValue(d->i_node->value());
    QObject::connect(d->spin_d, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));

    layout->addWidget(d->spin_d);
    return frame;
}

void dtkComposerControlsListItemInteger::onValueChanged(int value)
{
    d->i_node->setValue(value);
}


