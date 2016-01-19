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
#include "dtkMonitoringModel.h"

#include <dtkComposer/dtkComposerNode.h>

class dtkMonitoringControllerPrivate
{
public:
    QMap<dtkComposerNode *, dtkMonitor *> monitors;
    dtkMonitoringModel *m_model;
};

dtkMonitoringController *dtkMonitoringController::instance(void)
{
    if(!s_instance)
        s_instance = new dtkMonitoringController;

    return s_instance;
}

void dtkMonitoringController::registerNode(dtkComposerNode *node)
{
    qDebug() << Q_FUNC_INFO << node->type();

    d->monitors.insert(node, NULL);
    if(d->m_model)
        d->m_model->update(d->monitors.keys().indexOf(node));
}

void dtkMonitoringController::unregisterNode(dtkComposerNode *node)
{
    qDebug() << Q_FUNC_INFO << node->type()<<" "<<d->monitors.keys().indexOf(node);
    int index=d->monitors.keys().indexOf(node);
    d->monitors.remove(node);
    if(d->m_model)
        d->m_model->update(index);
}

void dtkMonitoringController::registerModel(dtkMonitoringModel *model)
{
    d->m_model=model;
}


void dtkMonitoringController::replaceMonitor(dtkComposerNode *node, dtkMonitor *monitor)
{
    if (!d->monitors.keys().contains(node))
        return;

    d->monitors[node] = monitor;
}

void dtkMonitoringController::removeMonitor(dtkMonitor *monitor)
{
    qDebug() << Q_FUNC_INFO;

    dtkComposerNode *node = d->monitors.key(monitor);

    d->monitors[node] = NULL;
}

int dtkMonitoringController::nodeCount(void) const
{
    return d->monitors.size();
}

QList<dtkComposerNode *> dtkMonitoringController::nodeList(void) const
{
    return d->monitors.keys();
}

dtkMonitor* dtkMonitoringController::monitor(dtkComposerNode* node)
{
    if(!node)
        return NULL;

    return d->monitors.value(node);
}

void dtkMonitoringController::onMonitoringChanged(dtkComposerNode *node, bool status)
{
    qDebug() << Q_FUNC_INFO << node->type() << status;

    if(status) {

        this->registerNode(node);

    } else {

        dtkMonitor *monitor = this->monitor(node);

        if(monitor) {
            this->removeMonitor(monitor);

            delete monitor;
        }

        this->unregisterNode(node);
    }
}

dtkMonitoringController::dtkMonitoringController(void) : QObject()
{
    d = new dtkMonitoringControllerPrivate;
    d->m_model=NULL;
}

dtkMonitoringController::~dtkMonitoringController(void)
{
    delete d;
}

dtkMonitoringController *dtkMonitoringController::s_instance = NULL;

//
// dtkMonitoringController.cpp ends here
