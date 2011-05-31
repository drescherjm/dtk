/* dtkDistributedControllerViewDetailed.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:19:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 30 16:36:16 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
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

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerViewDetailed : public QListWidget
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
