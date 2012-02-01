/* dtkComposerStackView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:14:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  1 10:41:34 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 62
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

    QPushButton *undo_button = new QPushButton("Undo", this);
    QPushButton *redo_button = new QPushButton("Redo", this);
    QPushButton *clear_button = new QPushButton("Clear", this);
    QHBoxLayout *unre_layout = new QHBoxLayout;
    unre_layout->addWidget(undo_button);
    unre_layout->addWidget(redo_button);
    unre_layout->addWidget(clear_button);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->view);
    layout->addLayout(unre_layout);

    connect(undo_button, SIGNAL(clicked()), this, SLOT(undo()));
    connect(redo_button, SIGNAL(clicked()), this, SLOT(redo()));
    connect(clear_button, SIGNAL(clicked()), this, SLOT(clear()));
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

void dtkComposerStackView::undo(void)
{
    d->stack->undo();
}

void dtkComposerStackView::redo(void)
{
    d->stack->redo();
}

void dtkComposerStackView::clear(void)
{
    d->stack->clear();
}
