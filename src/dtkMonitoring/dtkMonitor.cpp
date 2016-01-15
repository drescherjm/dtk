// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkMonitor.h"

#include <dtkComposer>

class dtkMonitorPrivate
{
public:
    dtkComposerNode *node;
};

dtkMonitor::dtkMonitor(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    d = new dtkMonitorPrivate;

    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
}

dtkMonitor::~dtkMonitor(void)
{
    delete d;
}

void dtkMonitor::setNode(dtkComposerNode *node)
{
    d->node = node;
}

dtkComposerNode *dtkMonitor::node(void)
{
    return d->node;
}

void dtkMonitor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(2);

    if ( this->isSelected() ) {
        pen.setColor(Qt::magenta);
    } else {
        pen.setColor(Qt::black);
    }

    painter->setPen(pen);
    painter->drawRect(this->boundingRect());
}

//
// dtkMonitor.cpp ends here
