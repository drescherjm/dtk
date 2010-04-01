/* dtkDistributorView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:26:28 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  1 09:52:53 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
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
