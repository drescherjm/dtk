/* @(#)dtkComposerControlsListItem.cpp ---
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

#include <dtkComposerControlsListItem.h>

#include <dtkComposerNodeInteger.h>

class dtkComposerControlsListItemPrivate
{
public:
    QListWidget *parent;

public:
    dtkComposerSceneNode *node;

public:
    QSpinBox *spin_d;
};

dtkComposerControlsListItem::dtkComposerControlsListItem(QListWidget *parent, dtkComposerSceneNode *node) : QListWidgetItem(parent, 1000), d(new dtkComposerControlsListItemPrivate)
{
    d->node   = node;
    d->parent = parent;
    d->spin_d = NULL;
}

dtkComposerControlsListItem::~dtkComposerControlsListItem(void)
{
    delete d;
    d = NULL;
}

QWidget *dtkComposerControlsListItem::widget(void)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    QFrame *frame = new QFrame(d->parent);
    frame->setLayout(layout);
    layout->addWidget(new QLabel(d->node->title(), frame));
    layout->addWidget(new QLabel("NOT EDITABLE !", frame));

    return frame;
}

dtkComposerSceneNode *dtkComposerControlsListItem::node(void)
{
    return d->node;
}




