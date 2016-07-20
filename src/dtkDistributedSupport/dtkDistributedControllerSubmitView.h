/* dtkDistributedControllerSubmitView.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:52:03 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mer. mai 23 17:46:37 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 13
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSUBMITVIEW_H
#define DTKDISTRIBUTEDCONTROLLERSUBMITVIEW_H

#include "dtkDistributedSupportExport.h"

#include <QtWidgets>

class dtkDistributedController;
class dtkDistributedControllerSubmitViewPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedControllerSubmitView : public QFrame
{
    Q_OBJECT

public:
    dtkDistributedControllerSubmitView(QWidget *parent = 0);
    ~dtkDistributedControllerSubmitView(void);

public slots:
    void setController(dtkDistributedController *controller);
    void setCluster(const QString& cluster);

public:
    void setApplication(const QString& application);

protected slots:
    void onSubmit(void);

private:
    dtkDistributedControllerSubmitViewPrivate *d;
};

#endif
