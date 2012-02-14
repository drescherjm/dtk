/* dtkComposerGraphNode.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr. 14 15:41:44 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 64
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"

class dtkComposerGraphNodePrivate
{
public:
};

dtkComposerGraphNode::dtkComposerGraphNode() : QGraphicsItem(),d(new dtkComposerGraphNodePrivate)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setZValue(1);
}

dtkComposerGraphNode::~dtkComposerGraphNode(void)
{
    delete d;

    d = NULL;
}


QRectF dtkComposerGraphNode::boundingRect(void) const
{
    return QRectF(0, 0, 100, 75);
}

void dtkComposerGraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(this->isSelected())
        painter->setPen(Qt::red);
    else
        painter->setPen(Qt::black);
    painter->setBrush(Qt::white);
    painter->drawRect(this->boundingRect());
}


void dtkComposerGraphNode::eval(void)
{
    DTK_DEFAULT_IMPLEMENTATION;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeList
// /////////////////////////////////////////////////////////////////

dtkComposerGraphNodeList::dtkComposerGraphNodeList(void) : QList<dtkComposerGraphNode *>()
{

}

dtkComposerGraphNodeList::dtkComposerGraphNodeList(const QList<dtkComposerGraphNode *>& other) : QList<dtkComposerGraphNode *>(other)
{

}
