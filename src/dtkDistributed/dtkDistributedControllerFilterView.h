/* dtkDistributedControllerFilterView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 10 10:10:19 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 10 10:15:20 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERFILTERVIEW_H
#define DTKDISTRIBUTEDCONTROLLERFILTERVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedControllerFilterViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerFilterView : public QFrame
{
    Q_OBJECT

public:
     dtkDistributedControllerFilterView(QWidget *parent = 0);
    ~dtkDistributedControllerFilterView(void);

private:
    dtkDistributedControllerFilterViewPrivate *d;
};

#endif
