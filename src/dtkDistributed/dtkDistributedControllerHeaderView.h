/* dtkDistributedControllerHeaderView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:22:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 16:03:37 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERHEADERVIEW_H
#define DTKDISTRIBUTEDCONTROLLERHEADERVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerHeaderViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerHeaderView : public QFrame
{
    Q_OBJECT

public:
     dtkDistributedControllerHeaderView(QWidget *parent = 0);
    ~dtkDistributedControllerHeaderView(void);

public:
    void setController(dtkDistributedController *controller);

public slots:
    void onConnected(const QUrl& server);

private:
    dtkDistributedControllerHeaderViewPrivate *d;
};

#endif
