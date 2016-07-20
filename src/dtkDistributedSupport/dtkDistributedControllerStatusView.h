/* dtkDistributedControllerStatusView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon May 30 13:19:21 2011 (+0200)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 16:13:53 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 22
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSTATUSVIEW_H
#define DTKDISTRIBUTEDCONTROLLERSTATUSVIEW_H

#include "dtkDistributedSupportExport.h"

#include <QtWidgets>

class dtkDistributedController;
class dtkDistributedControllerStatusModel;
class dtkDistributedControllerStatusViewPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedControllerStatusView : public QTreeView
{
    Q_OBJECT

public:
    dtkDistributedControllerStatusView(QWidget *parent = 0);
    ~dtkDistributedControllerStatusView(void);

private:
    dtkDistributedControllerStatusViewPrivate *d;
};

#endif
