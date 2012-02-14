/* dtkComposerGraphView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  9 15:48:41 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
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
    this->setWindowTitle("Graph");
}

dtkComposerGraphView::~dtkComposerGraphView(void)
{
    delete d;

    d = NULL;
}
