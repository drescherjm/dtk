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
#include "dtkMonitoringController.h"
#include "dtkMonitor.h"

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

void dtkMonitoringScene::dragMoveEvent (QGraphicsSceneDragDropEvent * event)
{
    if (event->mimeData()->hasText())
        event->acceptProposedAction();
    else
        QGraphicsScene::dragEnterEvent(event);
}

void dtkMonitoringScene::dropEvent     (QGraphicsSceneDragDropEvent * event)
{
    qDebug()<<event->mimeData()->text();
    QStringList list=event->mimeData()->text().split(" ", QString::SkipEmptyParts);
    for(QString id:list)
    {
        dtkComposerNode* node=(dtkComposerNode*)(id.trimmed().toLongLong());
        qDebug()<<node->type();
        dtkMonitor* monitor=dtkMonitoringController::instance()->monitor(node);

        if(monitor)
        {
            this->addItem(monitor);
        }
        else
            qDebug()<<Q_FUNC_INFO<<" monitor is NULL";
    }


    QGraphicsScene::dropEvent(event);
}


//
// dtkMonitoringScene.cpp ends here
