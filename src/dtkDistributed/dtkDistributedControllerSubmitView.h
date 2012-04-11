/* dtkDistributedControllerSubmitView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:52:03 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 11 12:36:15 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSUBMITVIEW_H
#define DTKDISTRIBUTEDCONTROLLERSUBMITVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedControllerSubmitViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerSubmitView : public QFrame
{
    Q_OBJECT

public:
     dtkDistributedControllerSubmitView(QWidget *parent = 0);
    ~dtkDistributedControllerSubmitView(void);

protected slots:
    void onSubmit(void);

private:
    dtkDistributedControllerSubmitViewPrivate *d;
};

#endif
