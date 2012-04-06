/* dtkDistributedControllerStatusModelFilter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 15:20:56 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  6 15:52:52 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSTATUSMODELFILTER_H
#define DTKDISTRIBUTEDCONTROLLERSTATUSMODELFILTER_H

#include <QtGui/QSortFilterProxyModel>

class dtkDistributedControllerStatusModelFilterPrivate;

class dtkDistributedControllerStatusModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
     dtkDistributedControllerStatusModelFilter(QObject *parent = 0);
    ~dtkDistributedControllerStatusModelFilter(void);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    dtkDistributedControllerStatusModelFilterPrivate *d;
};

#endif
