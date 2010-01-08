/* dtkComposerNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Jan  8 14:38:54 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 58
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODE_H
#define DTKCOMPOSERNODE_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtGui>

class dtkAbstractObject;
class dtkComposerEdge;
class dtkComposerNodePrivate;
class dtkComposerNodeProperty;

class DTKCOMPOSER_EXPORT dtkComposerNode : public QObject, public QGraphicsItem
{
    Q_OBJECT

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
    enum Type {
        Unknown,
        GenericData,
        Data,
        Process,
        View,
        All
    };

     dtkComposerNode(dtkComposerNode *parent = 0);
    ~dtkComposerNode(void);

    void setType(Type type);
    void setObject(dtkAbstractObject *object);
    void addScript(const QString& script);
    void setScript(const QString& script);

public:

    void addInputProperty(dtkComposerNodeProperty *property);
    void addOutputProperty(dtkComposerNodeProperty *property);

    void addInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void addOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void removeInputEdge(dtkComposerEdge *edge);
    void removeOutputEdge(dtkComposerEdge *edge);

    int count(dtkComposerNodeProperty *property);

    Type type(void);

    dtkAbstractObject *object(void);

    QList<dtkComposerEdge *> inputEdges(void);
    QList<dtkComposerEdge *> outputEdges(void);

    QList<dtkComposerNode *> inputNodes(void);
    QList<dtkComposerNode *> outputNodes(void);

    dtkComposerEdge *edge(dtkComposerNodeProperty *property);

    QString script(void) const;

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
