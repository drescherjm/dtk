/* dtkDistributedControllerViewFiltering.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:19:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 16:45:11 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERVIEWFILTERING_H
#define DTKDISTRIBUTEDCONTROLLERVIEWFILTERING_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerViewFilteringPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerViewFiltering : public QFrame
{
    Q_OBJECT

public:
     dtkDistributedControllerViewFiltering(QWidget *parent = 0);
    ~dtkDistributedControllerViewFiltering(void);

    void setController(dtkDistributedController *controller);

private:
    dtkDistributedControllerViewFilteringPrivate *d;
};

#endif
