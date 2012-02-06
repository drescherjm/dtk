/* dtkComposerSceneView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:25:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  6 11:40:54 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 71
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

    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
}

dtkComposerSceneView::~dtkComposerSceneView(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneView::setScene(dtkComposerScene *scene)
{
    d->scene = scene;

    connect(d->scene, SIGNAL(selectionCleared()), this, SLOT(clearSelection()));
}

void dtkComposerSceneView::clearSelection(void)
{
    this->selectionModel()->clearSelection();
}

void dtkComposerSceneView::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    if(selected.indexes().count())
        if(QGraphicsItem *item = static_cast<QGraphicsItem *>(selected.indexes().first().internalPointer()))
            item->setSelected(true);

    if(deselected.indexes().count())
        if(QGraphicsItem *item = static_cast<QGraphicsItem *>(deselected.indexes().first().internalPointer()))
            item->setSelected(false);
}
