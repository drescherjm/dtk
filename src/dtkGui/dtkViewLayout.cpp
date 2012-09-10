/* dtkViewLayout.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 23 17:55:16 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkViewLayout.h"
#include "dtkViewLayoutItem.h"

class dtkViewLayoutPrivate
{
public:
    dtkViewLayoutItem *root;
    dtkViewLayoutItem *current;
};

dtkViewLayout::dtkViewLayout(QWidget *parent) : QFrame(parent), d(new dtkViewLayoutPrivate)
{
    d->root = new dtkViewLayoutItem(0);
    d->root->setParent(this);
    d->root->setLayout(this);

    d->current = d->root;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->root);

    connect(d->root, SIGNAL(focused(dtkAbstractView *)), this, SIGNAL(focused(dtkAbstractView *)));
}

dtkViewLayout::~dtkViewLayout(void)
{
    delete d;

    d = NULL;
}

dtkViewLayoutItem *dtkViewLayout::root(void)
{
    return d->root;
}

dtkViewLayoutItem *dtkViewLayout::current(void)
{
    return d->current;
}

void dtkViewLayout::setCurrent(dtkViewLayoutItem *item)
{
    d->current = item;
}

void dtkViewLayout::clear(void)
{
    while(this->layout()->count())
        Q_UNUSED(this->layout()->takeAt(0));
    
    delete d->root;
    
    d->root = new dtkViewLayoutItem(0);
    d->root->setParent(this);
    d->root->setLayout(this);
    
    d->current = d->root;
}
