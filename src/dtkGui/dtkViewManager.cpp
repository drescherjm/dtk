/* dtkViewManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:37:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:37:57 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
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

#include <QtGui>

class dtkViewManagerPrivate
{
public:
    dtkViewList *list;
    dtkViewLayout *layout;
};

dtkViewManager::dtkViewManager(QWidget *parent) : QFrame(parent), d(new dtkViewManagerPrivate)
{
    d->list = new dtkViewList(this);
    d->layout = new dtkViewLayout(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->list);
    layout->addWidget(d->layout);
}

dtkViewManager::~dtkViewManager(void)
{
    delete d;

    d = NULL;
}
