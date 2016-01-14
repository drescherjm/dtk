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
    QHash<dtkComposerNode *, dtkMonitor *> monitors;
};

dtkMonitoringController *dtkMonitoringController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkMonitoringController;

    return s_instance;
}

void dtkMonitoringController::registerNode(dtkComposerNode *node)
{
    dtkMonitor *monitor = dtkMonitoringFactory::instance()->create(node->type());

    d->monitors.insert(node, monitor);
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
