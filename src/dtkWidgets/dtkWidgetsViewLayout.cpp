// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkWidgetsViewLayout.h"
#include "dtkWidgetsViewLayoutItem.h"

class dtkWidgetsViewLayoutPrivate
{
public:
    dtkWidgetsViewLayoutItem *root;
    dtkWidgetsViewLayoutItem *current;
};

dtkWidgetsViewLayout::dtkWidgetsViewLayout(QWidget *parent) : QFrame(parent), d(new dtkWidgetsViewLayoutPrivate)
{
    d->root = new dtkWidgetsViewLayoutItem(0);
    d->root->setParent(this);
    d->root->setLayout(this);

    d->current = d->root;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->root);

    connect(d->root, SIGNAL(focused(QWidget *)), this, SIGNAL(focused(QWidget *)));
    connect(d->root, SIGNAL(unfocused(QWidget *)), this, SIGNAL(unfocused(QWidget *)));
}

dtkWidgetsViewLayout::~dtkWidgetsViewLayout(void)
{
    delete d;

    d = NULL;
}

dtkWidgetsViewLayoutItem *dtkWidgetsViewLayout::root(void)
{
    return d->root;
}

dtkWidgetsViewLayoutItem *dtkWidgetsViewLayout::current(void)
{
    return d->current;
}

void dtkWidgetsViewLayout::setCurrent(dtkWidgetsViewLayoutItem *item)
{
    d->current = item;
}

void dtkWidgetsViewLayout::clear(void)
{
    d->root->clear();
}

//
// dtkWidgetsViewLayout.cpp ends here
