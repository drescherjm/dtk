/* dtkDistributorView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:26:28 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 25 12:57:23 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributorView.h"

class dtkDistributorViewPrivate
{
public:
};

dtkDistributorView::dtkDistributorView(QWidget *parent) : QGraphicsView(parent), d(new dtkDistributorViewPrivate)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

dtkDistributorView::~dtkDistributorView(void)
{
    delete d;

    d = NULL;
}
