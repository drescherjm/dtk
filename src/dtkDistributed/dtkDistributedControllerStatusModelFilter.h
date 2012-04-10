/* dtkDistributedControllerStatusModelFilter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 15:20:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 10 22:12:40 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSTATUSMODELFILTER_H
#define DTKDISTRIBUTEDCONTROLLERSTATUSMODELFILTER_H

#include "dtkDistributedExport.h"
#include "dtkDistributedNode.h"

#include <QtGui/QSortFilterProxyModel>

class dtkDistributedControllerStatusModelFilterPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerStatusModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
     dtkDistributedControllerStatusModelFilter(QObject *parent = 0);
    ~dtkDistributedControllerStatusModelFilter(void);

public:
    void setNetworkFlags(QFlags<dtkDistributedNode::Network> flags);
    void setStateFlags(QFlags<dtkDistributedNode::State> flags);
    void setBrandFlags(QFlags<dtkDistributedNode::Brand> flags);
    void setArchFlags(QFlags<dtkDistributedCpu::Architecture> flags);
    void setModelFlags(QFlags<dtkDistributedCpu::Model> flags);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    dtkDistributedControllerStatusModelFilterPrivate *d;
};

#endif
