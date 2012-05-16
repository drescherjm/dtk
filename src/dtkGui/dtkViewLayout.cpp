/* dtkViewLayout.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:38:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:38:25 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
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
};

dtkViewLayout::dtkViewLayout(QWidget *parent) : QFrame(parent), d(new dtkViewLayoutPrivate)
{
    d->root = new dtkViewLayoutItem;
    d->root->setParent(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->root);
}

dtkViewLayout::~dtkViewLayout(void)
{
    delete d;

    d = NULL;
}
