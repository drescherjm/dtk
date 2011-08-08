/* dtkDistributedControllerStatusView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:19:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 14:18:43 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
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

    void setModel(dtkDistributedControllerStatusModel *model);

private:
    dtkDistributedControllerStatusViewPrivate *d;
};

#endif
