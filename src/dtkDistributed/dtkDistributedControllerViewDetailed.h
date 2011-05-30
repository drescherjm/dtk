/* dtkDistributedControllerViewDetailed.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:19:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 13:24:58 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERVIEWDETAILED_H
#define DTKDISTRIBUTEDCONTROLLERVIEWDETAILED_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerViewDetailedPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerViewDetailed : QWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerViewDetailed(QWidget *parent = 0);
    ~dtkDistributedControllerViewDetailed(void);

    void setController(dtkDistributedController *controller);

private:
    dtkDistributedControllerViewDetailedPrivate *d;
};

#endif
