/* dtkComposerSceneView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:25:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  6 14:03:43 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 180
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerSceneModel.h"
#include "dtkComposerSceneView.h"

class dtkComposerSceneViewPrivate
{
public:
    dtkComposerScene *scene;
};

dtkComposerSceneView::dtkComposerSceneView(QWidget *parent) : QTreeView(parent), d(new dtkComposerSceneViewPrivate)
{
    d->scene = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
}

dtkComposerSceneView::~dtkComposerSceneView(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneView::setScene(dtkComposerScene *scene)
{
    d->scene = scene;

    // connect(d->scene, SIGNAL(selected(QGraphicsItem *)), this, SLOT(select(QGraphicsItem *)));
    connect(d->scene, SIGNAL(selectionCleared()), this, SLOT(clearSelection()));
}

void dtkComposerSceneView::clearSelection(void)
{
    this->selectionModel()->clearSelection();
}

// void dtkComposerSceneView::select(QGraphicsItem *item)
// {
//     dtkComposerSceneModel *model = dynamic_cast<dtkComposerSceneModel *>(this->model());
    
//     if(!model)
//         return;

//     QModelIndex idx;

//     QStack<QModelIndex> stack; stack.push(QModelIndex());

//     while(!idx.isValid() || !stack.isEmpty()) {

//         QModelIndex current = stack.pop();

//         for(int i = 0; i < model->rowCount(current); i++) {

//             QModelIndex index = model->index(i, 0, current);

//             if(!index.isValid())
//                 continue;

//             if((QGraphicsItem *)(index.internalPointer()) == item)
//                 idx = index;

//             if(model->rowCount(index))
//                 stack.push(index);
//         }
//     }

//     this->selectionModel()->select(idx, QItemSelectionModel::ClearAndSelect);
// }

void dtkComposerSceneView::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    QTreeView::selectionChanged(selected, deselected);

    d->scene->blockSignals(true);

    d->scene->clearSelection();

    if(selected.indexes().count())
        if(QGraphicsItem *item = static_cast<QGraphicsItem *>(selected.indexes().first().internalPointer()))
            item->setSelected(true);

    if(deselected.indexes().count())
        if(QGraphicsItem *item = static_cast<QGraphicsItem *>(deselected.indexes().first().internalPointer()))
            item->setSelected(false);

    d->scene->blockSignals(false);
}
