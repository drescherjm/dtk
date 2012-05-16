/* dtkViewList.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:39:06 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:39:14 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkViewList.h"

class dtkViewListPrivate
{
public:
};

dtkViewList::dtkViewList(QWidget *parent) : QListWidget(parent), d(new dtkViewListPrivate)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setDragEnabled(true);
    this->setFrameStyle(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

    this->addItem("view 1");
    this->addItem("view 2");
    this->addItem("view 3");
    this->addItem("view 4");
}

dtkViewList::~dtkViewList(void)
{
    delete d;

    d = NULL;
};
