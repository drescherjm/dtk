/* dtkComposerGraphNode.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 20 10:17:44 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 82
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkGlobal.h>

#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"

class dtkComposerGraphNodePrivate
{
public:
    QString title;
};

dtkComposerGraphNode::dtkComposerGraphNode() : QGraphicsItem(),d(new dtkComposerGraphNodePrivate)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setZValue(1);
    this->setTitle("Graph node");
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
    painter->drawText(this->boundingRect(), Qt::AlignCenter, d->title);
}

const QString& dtkComposerGraphNode::title(void)
{
    return d->title;
}

void dtkComposerGraphNode::setTitle(const QString& title)
{
    d->title = title;
}

void dtkComposerGraphNode::eval(void)
{
    DTK_DEFAULT_IMPLEMENTATION_NO_MOC;
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
