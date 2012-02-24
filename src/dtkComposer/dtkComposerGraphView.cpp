/* dtkComposerGraphView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. févr. 24 15:52:29 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerGraphView.h"

class dtkComposerGraphViewPrivate
{
public:
};

dtkComposerGraphView::dtkComposerGraphView(QWidget *parent) : QGraphicsView(parent),d(new dtkComposerGraphViewPrivate)
{
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setWindowTitle("Graph");
}

dtkComposerGraphView::~dtkComposerGraphView(void)
{
    delete d;

    d = NULL;
}
