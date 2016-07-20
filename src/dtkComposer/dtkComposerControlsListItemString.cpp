/* @(#)dtkComposerControlsListItemString.cpp ---
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

#include "dtkComposerControlsListItemString.h"

#include "dtkComposerSceneNode.h"
#include "dtkComposerNodeString.h"

#include <dtkLog>

class dtkComposerControlsListItemStringPrivate
{

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeString *s_node;

public:
    QLineEdit *edit;
};

dtkComposerControlsListItemString::dtkComposerControlsListItemString(QWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent, node), d(new dtkComposerControlsListItemStringPrivate)
{
    d->node = node;

    if (dtkComposerNodeString *s_node = dynamic_cast<dtkComposerNodeString *>(d->node->wrapee()))
        d->s_node = s_node;
    else
        dtkError() << "Not a string node, can't create control list item";

    QFrame *frame = new QFrame;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    frame->setLayout(layout);
    layout->addWidget(new QLabel(d->node->title(), frame));

    d->edit  = new QLineEdit(frame);
    d->edit->setText(d->s_node->value());
    d->edit->setEnabled(true);
    QObject::connect(d->edit, SIGNAL(textChanged(QString)), this, SLOT(onValueChanged(QString)));

    layout->addWidget(d->edit);
    this->setWidget(frame, qPrintable(d->node->title()));
}


dtkComposerControlsListItemString::~dtkComposerControlsListItemString(void )
{
    delete d;
    d = NULL;
}

void dtkComposerControlsListItemString::onValueChanged(QString value)
{
    d->s_node->setValue(value);
}


