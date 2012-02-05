/* dtkComposerSceneView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Sun Feb  5 15:25:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  5 15:54:50 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
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
}

dtkComposerSceneView::~dtkComposerSceneView(void)
{
    delete d;

    d = NULL;
}
