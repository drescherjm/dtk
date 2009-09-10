/* dtkUi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Sep  8 23:32:32 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep  9 09:47:05 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkUi.h"
#include "dtkUiItem.h"
#include "dtkUiView.h"

#include <QtGui>

class dtkUiPrivate
{
public:
    dtkUiView *view;
};

dtkUi::dtkUi(QWidget *parent) : QWidget(parent), d(new dtkUiPrivate)
{
    d->view = new dtkUiView(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->addWidget(d->view);
}

dtkUi::~dtkUi(void)
{
    delete d->view;
    delete d;

    d = NULL;
}

void dtkUi::append(dtkUiItem *item)
{
    d->view->append(item);
}
