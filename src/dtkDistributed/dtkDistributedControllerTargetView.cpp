/* dtkDistributedControllerTargetView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:23:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 12:26:29 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerTargetView.h"

class dtkDistributedControllerTargetViewPrivate
{
public:

};

dtkDistributedControllerTargetView::dtkDistributedControllerTargetView(QWidget *parent) : QFrame(parent), d(new dtkDistributedControllerTargetViewPrivate)
{

}

dtkDistributedControllerTargetView::~dtkDistributedControllerTargetView(void)
{
    delete d;

    d = NULL;
}
