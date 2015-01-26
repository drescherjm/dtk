/* @(#)dtkComposerControlsListItemBoolean.cpp ---
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

#include "dtkComposerControlsListItemBoolean.h"
#include "dtkComposerSceneNode.h"

#include "dtkComposerNodeBoolean.h"

#include "dtkComposerExport.h"

class dtkComposerControlsListItemBooleanPrivate
{
public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeBoolean *b_node;

public:
    QRadioButton *f_b;
    QRadioButton *t_b;
};

dtkComposerControlsListItemBoolean::dtkComposerControlsListItemBoolean(QWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent,node), d(new dtkComposerControlsListItemBooleanPrivate)
{
    d->node = node;

    if (dtkComposerNodeBoolean *b_node = dynamic_cast<dtkComposerNodeBoolean *>(d->node->wrapee()))
        d->b_node = b_node;
    else
        qDebug() << Q_FUNC_INFO <<"Not a boolean node, error";

    QFrame *frame = new QFrame;

    QHBoxLayout *layout = new QHBoxLayout(frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(2);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(new QLabel(d->node->title(), frame));

    QWidget *bool_widget = new QWidget(frame);

    d->f_b = new QRadioButton("false", bool_widget);
    d->t_b = new QRadioButton("true", bool_widget);

    d->f_b->setChecked(d->b_node->value() == false);
    d->t_b->setChecked(d->b_node->value() == true);

    QObject::connect(d->t_b, SIGNAL(toggled(bool)), this, SLOT(onValueChanged(bool)));

    QButtonGroup *g_b = new QButtonGroup(this);
    g_b->setExclusive(true);
    g_b->addButton(d->t_b);
    g_b->addButton(d->f_b);

    QHBoxLayout *bool_layout = new QHBoxLayout;
    bool_layout->setContentsMargins(0, 0, 0, 0);
    bool_layout->addWidget(d->t_b);
    bool_layout->addWidget(d->f_b);

    bool_widget->setLayout(bool_layout);

    layout->addWidget(bool_widget);
    this->setWidget(frame, qPrintable(d->node->title()));
}


dtkComposerControlsListItemBoolean::~dtkComposerControlsListItemBoolean(void )
{
    delete d;
    d= NULL;
}

void dtkComposerControlsListItemBoolean::onValueChanged(bool value)
{
    d->b_node->setValue(value);
}


