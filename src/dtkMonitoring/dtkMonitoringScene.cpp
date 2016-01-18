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
#include "dtkMonitoringScene.h"

#include <dtkComposer/dtkComposerNode>

class dtkMonitoringScenePrivate
{
public:
    dtkMonitoringFactory *factory;
};

dtkMonitoringScene::dtkMonitoringScene(QObject *parent) : QGraphicsScene(parent)
{
    d = new dtkMonitoringScenePrivate;
}

dtkMonitoringScene::~dtkMonitoringScene(void)
{
    delete d;
}

void dtkMonitoringScene::setFactory(dtkMonitoringFactory *factory)
{
    d->factory = factory;
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

        dtkMonitor *monitor = NULL;

        if (dtkMonitoringController::instance()->monitor(node))
            continue;

        monitor = d->factory->create(node->type());

        if (!monitor)
            continue;

        monitor->setNode(node);

        dtkMonitoringController::instance()->replaceMonitor(node, monitor);

        this->addItem(monitor);
    }

    QGraphicsScene::dropEvent(event);
}

void dtkMonitoringScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Delete:
        foreach(QGraphicsItem *item, this->items()) {
            if (item->isSelected()) {
                this->removeItem(item);
                if (dtkMonitor *monitor = dynamic_cast<dtkMonitor *>(item)) {
                    dtkMonitoringController::instance()->removeMonitor(monitor);
                    delete monitor;
                }
            }
        }
        break;
    default:
        break;
    }
}

//
// dtkMonitoringScene.cpp ends here
