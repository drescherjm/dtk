/* dtkDistributedControllerSubmitView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:53:43 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:54:42 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerSubmitView.h"

class dtkDistributedControllerSubmitViewPrivate
{
public:
    
};

dtkDistributedControllerSubmitView::dtkDistributedControllerSubmitView(QWidget *parent) : QFrame(parent), d(new dtkDistributedControllerSubmitViewPrivate)
{

}

dtkDistributedControllerSubmitView::~dtkDistributedControllerSubmitView(void)
{
    delete d;

    d = NULL;
}
