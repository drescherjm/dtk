/* dtkComposerNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 15:22:09 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
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

class dtkComposerNodePrivate;

class dtkComposerNode : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
     dtkComposerNode(dtkComposerNode *parent = 0);
    ~dtkComposerNode(void);

    QString propertyAt(const QPointF& point) const;
    QRectF propertyRect(const QString& prop) const;

public:
    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkComposerNodePrivate *d;
};

#endif
