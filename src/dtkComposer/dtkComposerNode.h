/* dtkComposerNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct  5 13:39:54 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 291
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
#include <QtDebug>
#include <QtGui>

class dtkAbstractObject;
class dtkComposerEdge;
class dtkComposerNodePrivate;
class dtkComposerNodeProperty;
class stkComspoerScene;

class DTKCOMPOSER_EXPORT dtkComposerNode : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
    enum Kind {
        Unknown,
        Atomic,
        Composite,
        Control,
        Data,
        Process,
        View
    };

    enum Attribute {
        Sequential,
        Parallel
    };

             dtkComposerNode(dtkComposerNode *parent = 0);
    virtual ~dtkComposerNode(void);

    virtual QString description(void); 

    void setAttribute(Attribute attribute);
    void setTitle(const QString& title);
    void setKind(Kind kind);
    void setType(QString type);
    void setObject(dtkAbstractObject *object);

    void  addInputProperty(dtkComposerNodeProperty *property);
    void addOutputProperty(dtkComposerNodeProperty *property);

    void  removeInputProperty(dtkComposerNodeProperty *property);
    void removeOutputProperty(dtkComposerNodeProperty *property);

    void  addInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void addOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void  addGhostInputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void addGhostOutputEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void  addInputRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    void addOutputRelayEdge(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

    void  addInputRoute(dtkComposerEdge *route);
    void addOutputRoute(dtkComposerEdge *route);

    void  removeInputEdge(dtkComposerEdge *edge);
    void removeOutputEdge(dtkComposerEdge *edge);
    void   removeAllEdges(void);

    void  removeGhostInputEdge(dtkComposerEdge *edge);
    void removeGhostOutputEdge(dtkComposerEdge *edge);
    void   removeAllGhostEdges(void);

    void  removeInputRelayEdge(dtkComposerEdge *edge);
    void removeOutputRelayEdge(dtkComposerEdge *edge);
    void   removeAllRelayEdges(void);

    void  removeInputRoute(dtkComposerEdge *route);
    void removeOutputRoute(dtkComposerEdge *route);
    void   removeAllRoutes(void);

    void addAction(const QString& text, const QObject *receiver, const char *slot);

    int  count(dtkComposerNodeProperty *property);
    int number(dtkComposerNodeProperty *property);

    Attribute attribute(void);
    Kind kind(void);
    QString type(void);

    dtkAbstractObject *object(void);

    QList<dtkComposerNodeProperty *> inputProperties(void);
    QList<dtkComposerNodeProperty *> outputProperties(void);

    QList<dtkComposerEdge *> inputEdges(void);
    QList<dtkComposerEdge *> outputEdges(void);

    QList<dtkComposerEdge *> inputGhostEdges(void);
    QList<dtkComposerEdge *> outputGhostEdges(void);

    QList<dtkComposerEdge *> inputRelayEdges(void);
    QList<dtkComposerEdge *> outputRelayEdges(void);

    QList<dtkComposerNode *> inputNodes(void);
    QList<dtkComposerNode *> outputNodes(void);

    QList<dtkComposerEdge *> inputRoutes(void);
    QList<dtkComposerEdge *> outputRoutes(void);

    dtkComposerEdge *edge(dtkComposerNodeProperty *property);

    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

    dtkComposerNodeProperty  *inputProperty(const QString& name) const;
    dtkComposerNodeProperty  *inputProperty(const QString& name, dtkComposerNode *from) const;
    dtkComposerNodeProperty *outputProperty(const QString& name) const;
    dtkComposerNodeProperty *outputProperty(const QString& name, dtkComposerNode *from) const;

    QString title(void);

    bool active(void);
    void setActive(bool active);

    virtual bool dirty(void);
    virtual void setDirty(bool dirty);

    bool resizable(void);
    void setResizable(bool resizable);

    virtual void layout(void);

    // -- Composite operations

    void    addChildNode(dtkComposerNode *node);
    void removeChildNode(dtkComposerNode *node);

    void setParentNode(dtkComposerNode *node);

    QList<dtkComposerNode *> childNodes(void);

    dtkComposerNode *parentNode(void);
    
    bool isChildOf(dtkComposerNode *node);
    bool isChildOfControlNode(dtkComposerNode *node);

    void setGhost(bool ghost);
    bool  isGhost(void);

    void    setGhostPosition(QPointF pos);
    QPointF    ghostPosition(void);
    void setNonGhostPosition(QPointF pos);
    QPointF nonGhostPosition(void);

    // --

    void setSize(const QSizeF& size);
    void setSize(qreal w, qreal h);

    // --

    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode& node);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode *node);

signals:
    void elapsed(QString duration);
    void evaluated(dtkComposerNode *node);
    void progressed(QString message);
    void progressed(int progress);

public slots:
    void alter(void);
    void touch(void);

public slots:
    virtual void update(void);

public:
    virtual QRectF boundingRect(void) const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    void highlight(bool ok);

    QColor penColor(void) const;
    QPen pen(void) const;

    void setPenColor(const QColor& color);
    void setPen(const QColor& color, const Qt::PenStyle& style, const qreal& width);

protected:
    qreal nodeRadius(void);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    void    onEdgeConnected(dtkComposerEdge *edge);
    void onEdgeDisconnected(dtkComposerEdge *edge);

    virtual QList<dtkComposerEdge *> allRoutes(void);
    virtual void removeRoute(dtkComposerEdge *route);

public:
    virtual QVariant value(dtkComposerNodeProperty *property);

    virtual void chooseImplementation(void);
    virtual void  setupImplementation(QString implementation = QString());

protected:
    virtual bool dirtyUpstreamNodes(void);
    virtual void markDirtyDownstreamNodes(void);

protected:
    virtual void pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void  run(void);
    virtual void push(dtkComposerEdge *edge, dtkComposerNodeProperty *property);

private:
    friend class dtkComposerScene; 
    friend class dtkComposerNodePrivate;

private:
    dtkComposerNodePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode  node);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode& node);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode *node);

#endif
