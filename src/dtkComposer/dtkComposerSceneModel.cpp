/* dtkComposerSceneModel.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:30:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  6 09:35:52 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 743
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
#include "dtkComposerSceneModel.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneModelPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneModelPrivate
{
public:
    dtkComposerScene *scene; 

public:
    dtkComposerSceneModel *q;
};

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

    connect(d->scene, SIGNAL(reset()), this, SIGNAL(modelReset()));
    connect(d->scene, SIGNAL(modified(bool)), this, SIGNAL(modelReset()));
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

    if(role != Qt::DisplayRole)
        return QVariant();

    dtkComposerSceneNodeComposite *composite;

    if(dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>((QGraphicsItem *)(index.internalPointer())))
        composite = node->parent();
    else if(dtkComposerSceneNote *note = dynamic_cast<dtkComposerSceneNote *>((QGraphicsItem *)(index.internalPointer())))
        composite = note->parent();
    else if(dtkComposerSceneEdge *edge = dynamic_cast<dtkComposerSceneEdge *>((QGraphicsItem *)(index.internalPointer())))
        composite = edge->parent();

    int c_notes = composite->notes().count();
    int c_nodes = composite->nodes().count();
    int c_edges = composite->edges().count();

    if (c_notes && index.row() < c_notes)
        return QString("Note (%1)").arg(this->rowCount(index));
    else if (c_nodes && index.row() < c_notes + c_nodes)
        return QString("Node (%1)").arg(this->rowCount(index));
    else if (c_edges && index.row() < c_notes + c_nodes + c_edges)
        return QString("Edge (%1)").arg(this->rowCount(index));

    return QVariant();
}

QVariant dtkComposerSceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QString("Composition");

    if (orientation == Qt::Vertical && role == Qt::DisplayRole)
        return QString("Composition");
    
    return QVariant();
}

QModelIndex dtkComposerSceneModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    dtkComposerSceneNodeComposite *composite;

    if(!parent.isValid())
        composite = d->scene->root();
    else
        composite = dynamic_cast<dtkComposerSceneNodeComposite *>((QGraphicsItem *)(parent.internalPointer()));

    int c_notes = composite->notes().count();
    int c_nodes = composite->nodes().count();
    int c_edges = composite->edges().count();

    if (c_notes && row < c_notes)
        return this->createIndex(row, column, composite->notes().at(row));
    else if (c_nodes && row < c_notes + c_nodes)
        return this->createIndex(row, column, composite->nodes().at(row - c_notes));
    else if (c_edges && row < c_notes + c_nodes + c_edges)
        return this->createIndex(row, column, composite->edges().at(row - c_notes - c_nodes));

    return QModelIndex();
}

QModelIndex dtkComposerSceneModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    dtkComposerSceneNodeComposite *composite;

    if(dtkComposerSceneNode *node = dynamic_cast<dtkComposerSceneNode *>((QGraphicsItem *)(index.internalPointer())))
        composite = node->parent();
    else if(dtkComposerSceneNote *note = dynamic_cast<dtkComposerSceneNote *>((QGraphicsItem *)(index.internalPointer())))
        composite = note->parent();
    else if(dtkComposerSceneEdge *edge = dynamic_cast<dtkComposerSceneEdge *>((QGraphicsItem *)(index.internalPointer())))
        composite = edge->parent();

    if(composite == d->scene->root())
        return QModelIndex();
    else
        return this->createIndex(composite->parent()->notes().count() + composite->parent()->nodes().indexOf(composite), 0, composite);
}

int dtkComposerSceneModel::rowCount(const QModelIndex& parent) const
{
    if(!d->scene)
        return 0;

    if(!parent.isValid())
        return d->scene->root()->notes().count() + d->scene->root()->nodes().count() + d->scene->root()->edges().count();

    if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>((QGraphicsItem *)(parent.internalPointer())))
        return composite->notes().count() + composite->nodes().count() + composite->edges().count();
    
    return 0;
}

int dtkComposerSceneModel::columnCount(const QModelIndex& parent) const
{
    return 1;
}
