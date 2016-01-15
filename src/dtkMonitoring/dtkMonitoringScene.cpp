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
#include "dtkMonitoringScene.h"

#include <dtkComposer/dtkComposerNode>

class dtkMonitoringScenePrivate
{
public:

};

dtkMonitoringScene::dtkMonitoringScene(QObject *parent) : QGraphicsScene(parent)
{
    d = new dtkMonitoringScenePrivate;
}

dtkMonitoringScene::~dtkMonitoringScene(void)
{
    delete d;
}

void dtkMonitoringScene::dragEnterEvent(QGraphicsSceneDragDropEvent * event)
{
    if (event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragEnterEvent(event);
}

void dtkMonitoringScene::dragLeaveEvent(QGraphicsSceneDragDropEvent * event)
{
    if (event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragEnterEvent(event);
}

void dtkMonitoringScene::dragMoveEvent(QGraphicsSceneDragDropEvent * event)
{
    if (event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragEnterEvent(event);
}

void dtkMonitoringScene::dropEvent(QGraphicsSceneDragDropEvent * event)
{

    QStringList list=event->mimeData()->text().split(" ", QString::SkipEmptyParts);

    for(QString id : list) {

        dtkComposerNode *node = (dtkComposerNode*)(id.trimmed().toLongLong());

        dtkMonitor *monitor = dtkMonitoringController::instance()->monitor(node);

        if(monitor)
            this->addItem(monitor);
    }

    QGraphicsScene::dropEvent(event);
}

//
// dtkMonitoringScene.cpp ends here
