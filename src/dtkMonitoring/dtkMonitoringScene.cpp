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

#include "dtkMonitoringScene.h"

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
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragEnterEvent(event);
}

void dtkMonitoringScene::dragLeaveEvent(QGraphicsSceneDragDropEvent * event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragEnterEvent(event);
}

void dtkMonitoringScene::dragMoveEvent (QGraphicsSceneDragDropEvent * event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragEnterEvent(event);
}

void dtkMonitoringScene::dropEvent     (QGraphicsSceneDragDropEvent * event)
{
    QGraphicsScene::dropEvent(event);
}


//
// dtkMonitoringScene.cpp ends here
