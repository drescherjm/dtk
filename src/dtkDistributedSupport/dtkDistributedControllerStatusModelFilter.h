/* dtkDistributedControllerStatusModelFilter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 15:20:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 16:18:28 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSTATUSMODELFILTER_H
#define DTKDISTRIBUTEDCONTROLLERSTATUSMODELFILTER_H

#include "dtkDistributedSupportExport.h"
#include "dtkDistributedNode.h"

#include <QSortFilterProxyModel>

class dtkDistributedControllerStatusModelFilterPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedControllerStatusModelFilter : public QSortFilterProxyModel
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
