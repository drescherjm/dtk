/* dtkDistributedControllerStatusModelItem.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jul  1 16:44:27 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 17:10:53 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERSTATUSMODELITEM_H
#define DTKDISTRIBUTEDCONTROLLERSTATUSMODELITEM_H

#include <QtCore>

class dtkDistributedControllerStatusModelItemPrivate;

class dtkDistributedControllerStatusModelItem
{
public:
     dtkDistributedControllerStatusModelItem(const QList<QVariant> &data, dtkDistributedControllerStatusModelItem *parent = 0);
    ~dtkDistributedControllerStatusModelItem(void);

    void appendChild(dtkDistributedControllerStatusModelItem *child);
    
    dtkDistributedControllerStatusModelItem *child(int row);
    dtkDistributedControllerStatusModelItem *parent(void);
    
    int childCount(void) const;
    int columnCount(void) const;
    
    QVariant data(int column) const;
    
    int row(void) const;
    
private:
    friend class dtkDistributedControllerStatusModelItemPrivate; dtkDistributedControllerStatusModelItemPrivate *d;
};

#endif
