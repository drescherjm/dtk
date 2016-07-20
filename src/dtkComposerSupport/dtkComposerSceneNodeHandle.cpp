/* dtkComposerSceneNodeHandle.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep 18 14:05:45 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 16:51:21 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 84
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerSceneNodeHandle.h"

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeHandlePrivate
{
public:
    dtkComposerSceneNodeControl *parent;

public:
    dtkComposerSceneNodeComposite *top;
    dtkComposerSceneNodeComposite *bot;

public:
    QRectF rect;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

dtkComposerSceneNodeHandle::dtkComposerSceneNodeHandle(dtkComposerSceneNodeControl *parent) : QGraphicsItem(parent), d(new dtkComposerSceneNodeHandlePrivate)
{
    d->parent = parent;

    d->top = NULL;
    d->bot = NULL;

    d->rect = QRectF(-20, -3, 40, 6);

    this->setFlag(QGraphicsItem::ItemIsMovable, true);
}

dtkComposerSceneNodeHandle::~dtkComposerSceneNodeHandle(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeHandle::setTopBlock(dtkComposerSceneNodeComposite *block)
{
    d->top = block;

    this->layout();
}

void dtkComposerSceneNodeHandle::setBotBlock(dtkComposerSceneNodeComposite *block)
{
    d->bot = block;

    this->layout();
}

void dtkComposerSceneNodeHandle::layout(void)
{
    if (!d->top)
        return;

    if (!d->bot)
        return;

    this->setPos(d->top->boundingRect().width() / 2, d->top->pos().y() + d->top->boundingRect().bottom() - 2);
}

QRectF dtkComposerSceneNodeHandle::boundingRect(void) const
{
    return d->rect;
}

void dtkComposerSceneNodeHandle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::lightGray);
    painter->setBrush(QColor(60, 60, 60));
    painter->drawRoundedRect(d->rect, 3, 3);
}

void dtkComposerSceneNodeHandle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal delta = event->pos().y() - event->lastPos().y();

    d->parent->resizeBlock(d->top, 0.0, delta);
    d->parent->moveBlock(d->bot, 0.0, delta);

    d->parent->layout();
}
