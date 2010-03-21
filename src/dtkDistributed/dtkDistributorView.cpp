/* dtkDistributorView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Mar 21 18:26:28 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar 21 22:23:39 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
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
}

dtkDistributorView::~dtkDistributorView(void)
{
    delete d;

    d = NULL;
}
