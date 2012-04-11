/* dtkDistributedControllerQueueView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 11 16:18:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 11 17:09:12 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERQUEUEVIEW_H
#define DTKDISTRIBUTEDCONTROLLERQUEUEVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerQueueViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerQueueView : public QListWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerQueueView(QWidget *parent = 0);
    ~dtkDistributedControllerQueueView(void);

public:
    void setController(dtkDistributedController *controller);

private:
    dtkDistributedControllerQueueViewPrivate *d;
};

#endif
