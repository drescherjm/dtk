/* dtkComposerGraphView.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:43:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 12:31:54 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
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

dtkComposerGraphView::dtkComposerGraphView(QWidget *parent) : QGraphicsView(parent), d(new dtkComposerGraphViewPrivate)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setWindowTitle("Graph");
}

dtkComposerGraphView::~dtkComposerGraphView(void)
{
    delete d;

    d = NULL;
}
