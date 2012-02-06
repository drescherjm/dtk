/* dtkComposerSceneView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:25:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  6 09:51:35 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneView.h"

class dtkComposerSceneViewPrivate
{
public:
};

dtkComposerSceneView::dtkComposerSceneView(QWidget *parent) : QTreeView(parent), d(new dtkComposerSceneViewPrivate)
{
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
