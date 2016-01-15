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

//
// dtkMonitor.cpp ends here
