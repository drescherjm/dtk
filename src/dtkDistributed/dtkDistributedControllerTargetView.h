/* dtkDistributedControllerTargetView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:25:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 12:26:15 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERTARGETVIEW_H
#define DTKDISTRIBUTEDCONTROLLERTARGETVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedControllerTargetViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerTargetView : public QFrame
{
    Q_OBJECT

public:
     dtkDistributedControllerTargetView(QWidget *parent = 0);
    ~dtkDistributedControllerTargetView(void);

private:
    dtkDistributedControllerTargetViewPrivate *d;
};

#endif
