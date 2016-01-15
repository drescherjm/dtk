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
#include "dtkMonitoringController.h"
#include "dtkMonitoringFactory.h"

#include <dtkComposer/dtkComposerNode.h>

class dtkMonitoringControllerPrivate
{
public:
    QMap<dtkComposerNode *, dtkMonitor *> monitors;
};

dtkMonitoringController *dtkMonitoringController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkMonitoringController;

    return s_instance;
}

void dtkMonitoringController::registerNode(dtkComposerNode *node)
{
    d->monitors.insert(node, NULL);
}

void dtkMonitoringController::replaceMonitor(dtkComposerNode *node, dtkMonitor *monitor)
{
    if (!d->monitors.keys().contains(node))
        return;

    d->monitors[node] = monitor;
}

void dtkMonitoringController::removeMonitor(dtkMonitor *monitor)
{
    dtkComposerNode *node = d->monitors.key(monitor);

    d->monitors[node] = NULL;
}

int dtkMonitoringController::nodeCount() const
{
    return d->monitors.size();
}

QList<dtkComposerNode*> dtkMonitoringController::nodeList() const
{
    return d->monitors.keys();
}

dtkMonitor* dtkMonitoringController::monitor(dtkComposerNode* node)
{
    if(!node)
        return NULL;

    return d->monitors.value(node);
}


dtkMonitoringController::dtkMonitoringController(void) : QObject()
{
    d = new dtkMonitoringControllerPrivate;
}

dtkMonitoringController::~dtkMonitoringController(void)
{
    delete d;
}

dtkMonitoringController *dtkMonitoringController::s_instance = NULL;

//
// dtkMonitoringController.cpp ends here
