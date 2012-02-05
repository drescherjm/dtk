/* dtkComposerSceneModel.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:30:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  5 16:05:05 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 74
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneModel.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneModel
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneModelPrivate
{
public:
    dtkComposerScene *scene;
};

dtkComposerSceneModel::dtkComposerSceneModel(QObject *parent) : QAbstractItemModel(parent), d(new dtkComposerSceneModelPrivate)
{
    d->scene = NULL;
}

dtkComposerSceneModel::~dtkComposerSceneModel(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneModel::setScene(dtkComposerScene *scene)
{
    d->scene = scene;
}

Qt::ItemFlags dtkComposerSceneModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return 0;
    
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant dtkComposerSceneModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    if (role != Qt::DisplayRole)
        return QVariant();
    
    // TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    
    // return item->data(index.column());

    return QVariant();
}

QVariant dtkComposerSceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->data(section);

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QVariant();
    
    return QVariant();
}

QModelIndex dtkComposerSceneModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    
    // TreeItem *parentItem;
    
    // if (!parent.isValid())
    //     parentItem = rootItem;
    // else
    //     parentItem = static_cast<TreeItem*>(parent.internalPointer());
    
    // TreeItem *childItem = parentItem->child(row);

    // if (childItem)
    //     return createIndex(row, column, childItem);
    // else
    //     return QModelIndex();

    return QModelIndex();
}

QModelIndex dtkComposerSceneModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();
    
    // TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    // TreeItem *parentItem = childItem->parent();
    
    // if (parentItem == rootItem)
    //     return QModelIndex();
    
    // return createIndex(parentItem->row(), 0, parentItem);

    return QModelIndex();
}

int dtkComposerSceneModel::rowCount(const QModelIndex& parent) const
{
    // TreeItem *parentItem;

    // if (parent.column() > 0)
    //     return 0;
    
    // if (!parent.isValid())
    //     parentItem = rootItem;
    // else
    //     parentItem = static_cast<TreeItem*>(parent.internalPointer());
    
    // return parentItem->childCount();

    if(!d->scene)
        return 0;

    return d->scene->root()->nodes().count();

    return 0;
}

int dtkComposerSceneModel::columnCount(const QModelIndex& parent) const
{
    // if (parent.isValid())
    //     return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    // else
    //     return rootItem->columnCount();

    if(!d->scene)
        return 0;

    return 0;
}
