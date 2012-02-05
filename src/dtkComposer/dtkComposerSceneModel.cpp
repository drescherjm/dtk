/* dtkComposerSceneModel.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:30:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  5 19:52:35 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 406
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNote.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerSceneModel.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneModelPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneModelPrivate
{
public:
    dtkComposerSceneNodeComposite *node(const QModelIndex& index);

public:
    dtkComposerScene *scene; 

public:
    dtkComposerSceneModel *q;
};

dtkComposerSceneNodeComposite *dtkComposerSceneModelPrivate::node(const QModelIndex& index)
{
    if(!index.isValid())
        return this->scene->root();

    QStack<QModelIndex> indexes; indexes.push(index);
    QModelIndex parent = index.parent();

    while(parent.isValid()) {
        indexes.push(parent);
        parent = parent.parent();
    }

    dtkComposerSceneNodeComposite *node = this->scene->root();

    while(node && !indexes.isEmpty()) {

        QModelIndex idx = indexes.pop();

        if(idx.row() < node->notes().count())
            node = NULL;
        else if(idx.row() >= node->notes().count() + node->nodes().count())
            node = NULL;
        else
            node = dynamic_cast<dtkComposerSceneNodeComposite *>(node->nodes().at(idx.row() - node->notes().count()));
    }

    return node;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneModel
// /////////////////////////////////////////////////////////////////

dtkComposerSceneModel::dtkComposerSceneModel(QObject *parent) : QAbstractItemModel(parent), d(new dtkComposerSceneModelPrivate)
{
    d->q = this;
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

    connect(d->scene, SIGNAL(modified(bool)), this, SIGNAL(modelReset()));
}

Qt::ItemFlags dtkComposerSceneModel::flags(const QModelIndex& index) const
{
    qDebug() << __func__ << index;

    if (!index.isValid())
        return 0;
    
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant dtkComposerSceneModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return QVariant();

    int c_notes = d->scene->root()->notes().count();
    int c_nodes = d->scene->root()->nodes().count();
    int c_edges = d->scene->root()->edges().count();

    if (c_notes && index.row() < c_notes) {
        qDebug() << __func__ << index << "Note";
        return QString("Note");
    }
    
    else if (c_nodes && index.row() < c_notes + c_nodes) {
        qDebug() << __func__ << index << "Node";
        return QString("Node");
    }

    else if (c_edges && index.row() < c_notes + c_nodes + c_edges) {
        qDebug() << __func__ << index << "Edge";
        return QString("Edge");
    }
    
    qDebug() << __func__ << "Returning no data";

    return QVariant();
}

QVariant dtkComposerSceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QString("Column %1").arg(section);

    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString("Row %1").arg(section);
    
    return QVariant();
}

QModelIndex dtkComposerSceneModel::index(int row, int column, const QModelIndex& parent) const
{
    dtkComposerSceneNodeComposite *node = d->node(parent);

    if(!node) {
        qDebug() << "PARENT IS NO COMPOSITE .. WTF";
        return QModelIndex();
    }    

    int c_notes = d->scene->root()->notes().count();
    int c_nodes = d->scene->root()->nodes().count();
    int c_edges = d->scene->root()->edges().count();

    if (c_notes && row < c_notes)
        return this->createIndex(row, column, node->notes().at(row));
    
    else if (c_nodes && row < c_notes + c_nodes)
        return this->createIndex(row, column, node->nodes().at(row - c_notes));

    else if (c_edges && row < c_notes + c_nodes + c_edges)
        return this->createIndex(row, column, node->edges().at(row - c_notes - c_nodes));

    return QModelIndex();
}

QModelIndex dtkComposerSceneModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    // dtkComposerSceneNodeComposite *prt = NULL;

    // if (prt == d->scene->root())
    //     return QModelIndex();
    
    // return createIndex(parentItem->row(), 0, parentItem);

    return QModelIndex();
}

int dtkComposerSceneModel::rowCount(const QModelIndex& parent) const
{
    if(!d->scene)
        return 0;

    dtkComposerSceneNodeComposite *node = d->node(parent);

    if(!node) {
        qDebug() << "PARENT IS NO COMPOSITE .. WTF!";
        return 0;
    }

    return node->notes().count() + node->nodes().count() + node->edges().count();
}

int dtkComposerSceneModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}
