/* dtkDistributedControllerHeaderView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:22:09 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 16:58:56 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
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
    void setCluster(const QString& cluster);

public slots:
    void onStatus(const QUrl& cluster);

protected:
    void update(void);

private:
    dtkDistributedControllerHeaderViewPrivate *d;
};

#endif
