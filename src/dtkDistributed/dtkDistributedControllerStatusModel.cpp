/* dtkDistributedControllerStatusModel.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jul  1 13:48:10 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jul  1 17:15:25 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 154
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedController.h"
#include "dtkDistributedControllerStatusModel.h"
#include "dtkDistributedControllerStatusModelItem.h"
#include "dtkDistributedNode.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerStatusModelPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerStatusModelPrivate
{
public:
    dtkDistributedController *controller;
    dtkDistributedControllerStatusModelItem *rootItem;

public:
    void update(void);

public:
    dtkDistributedControllerStatusModel *q;
};

void dtkDistributedControllerStatusModelPrivate::update(void)
{
    qDebug() << __func__;

    foreach(dtkDistributedNode *node, this->controller->nodes()) {
        
        this->rootItem->appendChild(new dtkDistributedControllerStatusModelItem(QList<QVariant>() << node->name() << node->cpus().count() << node->gpus().count(), this->rootItem));
    }
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerStatusModel
// /////////////////////////////////////////////////////////////////

dtkDistributedControllerStatusModel::dtkDistributedControllerStatusModel(QObject *parent) : QAbstractItemModel(parent), d(new dtkDistributedControllerStatusModelPrivate)
{
    d->q = this;
    d->controller = NULL;
    d->rootItem = new dtkDistributedControllerStatusModelItem(QList<QVariant>() << "Node" << "#CPU" << "#GPU");
}

dtkDistributedControllerStatusModel::~dtkDistributedControllerStatusModel(void)
{
    delete d->rootItem;
    delete d;

    d = NULL;
}

void dtkDistributedControllerStatusModel::setController(dtkDistributedController *controller)
{
    d->controller = controller;
    d->update();

    connect(d->controller, SIGNAL(updated()), this, SLOT(update()));
}

void dtkDistributedControllerStatusModel::update(void)
{
    if (d->controller)
        d->update();
}

int dtkDistributedControllerStatusModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return static_cast<dtkDistributedControllerStatusModelItem *>(parent.internalPointer())->columnCount();
     else
         return d->rootItem->columnCount();
}

int dtkDistributedControllerStatusModel::rowCount(const QModelIndex& parent) const
{
    dtkDistributedControllerStatusModelItem *parentItem;

    if (parent.column() > 0)
        return 0;
    
    if (!parent.isValid())
        parentItem = d->rootItem;
    else
        parentItem = static_cast<dtkDistributedControllerStatusModelItem *>(parent.internalPointer());
    
    return parentItem->childCount();
}

QVariant dtkDistributedControllerStatusModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role != Qt::DisplayRole)
        return QVariant();
    
    dtkDistributedControllerStatusModelItem *item = static_cast<dtkDistributedControllerStatusModelItem *>(index.internalPointer());
    
    return item->data(index.column());
}

QModelIndex dtkDistributedControllerStatusModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    
    dtkDistributedControllerStatusModelItem *parentItem;
    
    if (!parent.isValid())
        parentItem = d->rootItem;
    else
        parentItem = static_cast<dtkDistributedControllerStatusModelItem *>(parent.internalPointer());
    
    dtkDistributedControllerStatusModelItem *childItem = parentItem->child(row);

    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex dtkDistributedControllerStatusModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();
    
    dtkDistributedControllerStatusModelItem *childItem = static_cast<dtkDistributedControllerStatusModelItem *>(index.internalPointer());
    dtkDistributedControllerStatusModelItem *parentItem = childItem->parent();
    
    if (parentItem == d->rootItem)
        return QModelIndex();
    
    return createIndex(parentItem->row(), 0, parentItem);
}

Qt::ItemFlags dtkDistributedControllerStatusModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant dtkDistributedControllerStatusModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return d->rootItem->data(section);
    
    return QVariant();
}
