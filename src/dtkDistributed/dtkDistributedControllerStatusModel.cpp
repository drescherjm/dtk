/* dtkDistributedControllerStatusModel.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Jul  1 13:48:10 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 10 18:04:27 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 268
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
#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedJob.h"
#include "dtkDistributedNode.h"

#include <dtkCore/dtkGlobal.h>

QVariant toString(dtkDistributedNode::Network flag)
{
    if(flag == dtkDistributedNode::Ethernet1G)
        return "Ethernet1G";
    
    if(flag == dtkDistributedNode::Ethernet10G)
        return "Ethernet10G";

    if(flag == dtkDistributedNode::Myrinet2G)
        return "Myrinet2G";

    if(flag == dtkDistributedNode::Myrinet10G)
        return "Myrinet10G";

    if(flag == dtkDistributedNode::Infiniband10G)
        return "Infiniband10G";

    if(flag == dtkDistributedNode::Infiniband20G)
        return "Infiniband20G";

    if(flag == dtkDistributedNode::Infiniband40G)
        return "Infiniband40G";

    return QString();
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerStatusModelPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerStatusModelPrivate
{
public:
    dtkDistributedController *controller;
    dtkDistributedControllerStatusModelItem *rootItem;

public:
    QString cluster;

public:
    void clear(void);
    void update(void);

public:
    dtkDistributedControllerStatusModel *q;
};

void dtkDistributedControllerStatusModelPrivate::clear(void)
{
    this->rootItem->clear();
}

void dtkDistributedControllerStatusModelPrivate::update(void)
{
    this->rootItem->clear();

    QList<dtkDistributedNode *> nodes;

    if(cluster.isEmpty())
        nodes = this->controller->nodes();
    else
        nodes = this->controller->nodes(cluster);

    foreach(dtkDistributedNode *node, nodes) {

        dtkDistributedControllerStatusModelItem *nodeItem = new dtkDistributedControllerStatusModelItem(QList<QVariant>() << node->name() << toString(node->network()), this->rootItem);
        nodeItem->kind = dtkDistributedControllerStatusModelItem::Node;

        foreach(dtkDistributedCpu *cpu, node->cpus()) {
            foreach(dtkDistributedCore *core, cpu->cores()) {
           
                QList<QVariant> data;

                if(core->job())
                    data << core->job()->Id() + " " + core->job()->Username();
                else
                    data << "Free";

                data << ""; // Network
     
                dtkDistributedControllerStatusModelItem *coreItem = new dtkDistributedControllerStatusModelItem(data, nodeItem);
                coreItem->kind = dtkDistributedControllerStatusModelItem::Core;
                nodeItem->appendChild(coreItem);
            }
        }

        this->rootItem->appendChild(nodeItem);
    }

    q->reset();
}

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerStatusModel
// /////////////////////////////////////////////////////////////////

dtkDistributedControllerStatusModel::dtkDistributedControllerStatusModel(QObject *parent) : QAbstractItemModel(parent), d(new dtkDistributedControllerStatusModelPrivate)
{
    d->q = this;
    d->controller = NULL;
    d->rootItem = new dtkDistributedControllerStatusModelItem(QList<QVariant>() << "Node" << "Network");
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

    this->onUpdated();

    connect(d->controller, SIGNAL(updated()), this, SLOT(onUpdated()));
    connect(d->controller, SIGNAL(updated(const QUrl&)), this, SLOT(onUpdated(const QUrl&)));
    connect(d->controller, SIGNAL(disconnected(const QUrl&)), this, SLOT(onDisconnected(const QUrl&)));
}

void dtkDistributedControllerStatusModel::setCluster(const QString& cluster)
{
    d->cluster = cluster;

    this->onUpdated();
}

void dtkDistributedControllerStatusModel::onUpdated(void)
{
    this->beginResetModel();
    d->update();
    this->endResetModel();
}

void dtkDistributedControllerStatusModel::onUpdated(const QUrl& server)
{
    this->beginResetModel();
    if(d->cluster == server.toString())
        d->update();
    this->endResetModel();
}

void dtkDistributedControllerStatusModel::onDisconnected(const QUrl& server)
{
    this->beginResetModel();
    if(d->cluster == server.toString())
        d->clear();
    this->endResetModel();
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
    
    dtkDistributedControllerStatusModelItem *item = static_cast<dtkDistributedControllerStatusModelItem *>(index.internalPointer());

    if (role == Qt::TextColorRole && item->kind == dtkDistributedControllerStatusModelItem::Core)
        return item->data(0).toString() == "Free" ? Qt::darkGreen : Qt::darkRed;

    if (role != Qt::DisplayRole)
        return QVariant();
    
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
