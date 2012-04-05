/* dtkDistributedControllerStatusModelItem.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jul  1 16:44:27 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 12:03:42 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
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
    enum Kind {
        Node,
        Core
    };

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

public:
    Kind kind;
    
private:
    friend class dtkDistributedControllerStatusModelItemPrivate; dtkDistributedControllerStatusModelItemPrivate *d;
};

#endif
