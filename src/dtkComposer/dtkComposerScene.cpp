/* dtkComposerScene.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:06 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 15:41:12 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerScene.h"

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent)
{
    this->addItem(new dtkComposerNode);
    this->addItem(new dtkComposerNode);
}

dtkComposerScene::~dtkComposerScene(void)
{

}

void dtkComposerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void dtkComposerScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void dtkComposerScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    dtkComposerNode *node = nodeAt(mouseEvent->scenePos());
    if (node) {
        // dtkComposerNodeProperty prop = node->propertyAt(item->mapFromScene(mouseEvent->scenePos()));

        // if (!prop.isEmpty()) {
        //     delete m_currentEdge;
        //     m_currentEdge = new dtkEdgeGraphicsItem();
        //     addItem(m_currentEdge);
        //     m_currentEdge->setSource(node, prop);
        //     m_currentEdge->show();
        // }
    }
}

dtkComposerNode *dtkComposerScene::nodeAt(const QPointF& point) const
{
    QList<QGraphicsItem *> cs = items(point.x(), point.y(), 1, 1, Qt::IntersectsItemBoundingRect);
    dtkComposerNode *node = 0;
    if (!cs.isEmpty()) {
        QGraphicsItem *qitem = cs.first();
        node = qgraphicsitem_cast<dtkComposerNode *>(qitem);
    }
    return node;
}
