/* dtkViewManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:37:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jun 21 16:21:09 2013 (+0200)
 *           By: Selim Kraria
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkViewList.h"
#include "dtkViewLayout.h"
#include "dtkViewManager.h"
#include "dtkSplitter.h"

#include <QtGui>

class dtkViewManagerPrivate
{
public:
    dtkViewList *list;
    dtkViewLayout *layout;
};

dtkViewManager::dtkViewManager(QWidget *parent) : QFrame(parent), d(new dtkViewManagerPrivate)
{
    dtkSplitter *splitter = new dtkSplitter(this);

    d->list = new dtkViewList;
    d->layout = new dtkViewLayout;

    splitter->addWidget(d->list);
    splitter->addWidget(d->layout);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,3);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(splitter);
}

dtkViewManager::~dtkViewManager(void)
{
    delete d;

    d = NULL;
}

void dtkViewManager::clear(void)
{
    d->list->clear();
    d->layout->clear();
}
