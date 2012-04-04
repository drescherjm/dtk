/* dtkDistributedControllerHeaderView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 12:24:15 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerHeaderView.h"

class dtkDistributedControllerHeaderViewPrivate
{
public:

};

dtkDistributedControllerHeaderView::dtkDistributedControllerHeaderView(QWidget *parent) : QFrame(parent), d(new dtkDistributedControllerHeaderViewPrivate)
{

}

dtkDistributedControllerHeaderView::~dtkDistributedControllerHeaderView(void)
{
    delete d;

    d = NULL;
}
