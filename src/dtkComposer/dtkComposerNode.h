/* dtkComposerNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 16:53:58 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 45
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

class dtkAbstractObject;
class dtkComposerEdge;
class dtkComposerNodePrivate;
class dtkComposerNodeProperty;

class dtkComposerNode : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum Type { Unknown, Data, Process, View };

     dtkComposerNode(dtkComposerNode *parent = 0);
    ~dtkComposerNode(void);

    void setType(Type type);
    void setObject(dtkAbstractObject *object);

    Type type(void);

    dtkAbstractObject *object(void);

    dtkComposerEdge *edge(dtkComposerNodeProperty *property);

    void addInputProperty(dtkComposerNodeProperty *property);
    void addOutputProperty(dtkComposerNodeProperty *property);

    void addInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void addOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void removeInputEdge(dtkComposerEdge *edge);
    void removeOutputEdge(dtkComposerEdge *edge);

    int count(dtkComposerNodeProperty *property);

public:
    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

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
