/* dtkDistributedControllerStatusView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:19:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 10 18:23:12 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSTATUSVIEW_H
#define DTKDISTRIBUTEDCONTROLLERSTATUSVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerStatusModel;
class dtkDistributedControllerStatusViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerStatusView : public QTreeView
{
    Q_OBJECT

public:
     dtkDistributedControllerStatusView(QWidget *parent = 0);
    ~dtkDistributedControllerStatusView(void);

private:
    dtkDistributedControllerStatusViewPrivate *d;
};

#endif
