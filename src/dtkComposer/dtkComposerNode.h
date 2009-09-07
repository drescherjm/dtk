/* dtkComposerNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 23:15:40 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODE_H
#define DTKCOMPOSERNODE_H

#include <QtCore>
#include <QtGui>

class dtkComposerEdge;
class dtkComposerNodePrivate;
class dtkComposerNodeProperty;

class dtkComposerNode : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
     dtkComposerNode(dtkComposerNode *parent = 0);
    ~dtkComposerNode(void);

    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

    void addInputEdge(dtkComposerEdge *edge);
    void addOutputEdge(dtkComposerEdge *edge);

public:
    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkComposerNodePrivate *d;
};

#endif
