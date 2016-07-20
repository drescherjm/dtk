/* dtkComposerStackView.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:14:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb  7 13:23:02 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 70
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerStack.h"
#include "dtkComposerStackView.h"

class dtkComposerStackViewPrivate
{
public:
    QUndoView *view;
    QUndoStack *stack;
};

dtkComposerStackView::dtkComposerStackView(QWidget *parent) : QWidget(parent), d(new dtkComposerStackViewPrivate)
{
    d->view = new QUndoView(this);
    d->view->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->view->setFrameStyle(QFrame::NoFrame);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->view);
}

dtkComposerStackView::~dtkComposerStackView(void)
{
    delete d;

    d = NULL;
}

void dtkComposerStackView::setStack(dtkComposerStack *stack)
{
    d->view->setStack(stack);

    d->stack = stack;
}
