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

void dtkMonitoringController::replaceNode(dtkComposerNode *node, dtkMonitor *monitor)
{
    if (!d->monitors.keys().contains(node))
        return;

    d->monitors[node] = monitor;
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
    if(!node) {
        qDebug()<<Q_FUNC_INFO<<" node is NULL";
        return NULL;
    }
    qDebug()<<node;
    qDebug()<<d->monitors;

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
