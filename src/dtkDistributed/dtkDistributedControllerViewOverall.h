/* dtkDistributedControllerViewOverall.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:19:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 13:24:47 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERVIEWOVERALL_H
#define DTKDISTRIBUTEDCONTROLLERVIEWOVERALL_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerViewOverallPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerViewOverall : QWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerViewOverall(QWidget *parent = 0);
    ~dtkDistributedControllerViewOverall(void);

    void setController(dtkDistributedController *controller);

private:
    dtkDistributedControllerViewOverallPrivate *d;
};

#endif
