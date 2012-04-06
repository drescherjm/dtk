/* dtkDistributedControllerStatusModelFilter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 15:53:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  6 15:55:34 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerStatusModelFilter.h"

class dtkDistributedControllerStatusModelFilterPrivate
{
public:
    
};

dtkDistributedControllerStatusModelFilter::dtkDistributedControllerStatusModelFilter(QObject *parent) : QSortFilterProxyModel(parent), d(new dtkDistributedControllerStatusModelFilterPrivate)
{

}

dtkDistributedControllerStatusModelFilter::~dtkDistributedControllerStatusModelFilter(void)
{
    delete d;

    d = NULL;
}

bool dtkDistributedControllerStatusModelFilter::filterAcceptsRow(int row, const QModelIndex& parent) const
{

}
