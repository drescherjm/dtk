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

}

dtkMonitor::~dtkMonitor(void)
{

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
