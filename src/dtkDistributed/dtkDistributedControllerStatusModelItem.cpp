/* dtkDistributedControllerStatusModelItem.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jul  1 16:46:29 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 16:50:50 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 45
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedControllerStatusModelItem.h"

class dtkDistributedControllerStatusModelItemPrivate
{
public:
    QList<dtkDistributedControllerStatusModelItem *> childItems;
    QList<QVariant> itemData;

public:
    dtkDistributedControllerStatusModelItem *parentItem;
};

dtkDistributedControllerStatusModelItem::dtkDistributedControllerStatusModelItem(const QList<QVariant> &data, dtkDistributedControllerStatusModelItem *parent) : d(new dtkDistributedControllerStatusModelItemPrivate)
{
    d->parentItem = parent;
    d->itemData = data;
}

dtkDistributedControllerStatusModelItem::~dtkDistributedControllerStatusModelItem(void)
{
    qDeleteAll(d->childItems);
}

void dtkDistributedControllerStatusModelItem::appendChild(dtkDistributedControllerStatusModelItem *item)
{
    d->childItems.append(item);
}

void dtkDistributedControllerStatusModelItem::removeChild(dtkDistributedControllerStatusModelItem *item)
{
    d->childItems.removeAll(item);
}

void dtkDistributedControllerStatusModelItem::clear(void)
{
    qDeleteAll(d->childItems);

    d->childItems.clear();
}

dtkDistributedControllerStatusModelItem *dtkDistributedControllerStatusModelItem::child(int row)
{
    return d->childItems.value(row);
}

int dtkDistributedControllerStatusModelItem::childCount(void) const
{
    return d->childItems.count();
}

int dtkDistributedControllerStatusModelItem::columnCount(void) const
{
    return d->itemData.count();
}

QVariant dtkDistributedControllerStatusModelItem::data(int column) const
{
    return d->itemData.value(column);
}

dtkDistributedControllerStatusModelItem *dtkDistributedControllerStatusModelItem::parent(void)
{
    return d->parentItem;
}

int dtkDistributedControllerStatusModelItem::row(void) const
{
    if (d->parentItem)
        return d->parentItem->d->childItems.indexOf(const_cast<dtkDistributedControllerStatusModelItem*>(this));

    return 0;
}
