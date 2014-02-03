/* dtkComposerSceneView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:25:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov  8 13:50:29 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 188
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

    connect(d->scene, SIGNAL(selectionCleared()), this, SLOT(clearSelection()));
}

void dtkComposerSceneView::reset(void)
{
    QTreeView::reset();
    
    this->expandAll();
}

void dtkComposerSceneView::clearSelection(void)
{
    this->selectionModel()->clearSelection();
}

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
