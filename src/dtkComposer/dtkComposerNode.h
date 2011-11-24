/* dtkComposerNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 13:48:02 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Nov 24 16:46:15 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 363
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
#include "dtkComposerNodeGraphic.h"
#include "dtkComposerNodeLogic.h"

#include <QtCore>
#include <QtDebug>
#include <QtGui>

class dtkAbstractObject;
class dtkComposerNodeAbstractTransmitter;
class dtkComposerEdge;
class dtkComposerEvaluatorPrivate;
class dtkComposerNodePrivate;
class dtkComposerNodeProperty;
class dtkComposerScene;

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
    void setObject(dtkAbstractObject *object, bool update = true);

    void addAction(const QString& text, const QObject *receiver, const char *slot);

    Attribute attribute(void);
    Kind kind(void);
    QString type(void);

    dtkAbstractObject *object(void);

    QList<dtkComposerNode *> inputNodes(void);
    QList<dtkComposerNode *> outputNodes(void);

    dtkComposerNodeProperty *propertyAt(const QPointF& point) const;

    dtkComposerNodeProperty  *leftProperty(const QString& name, dtkComposerNode *from) const;
    dtkComposerNodeProperty *rightProperty(const QString& name, dtkComposerNode *from) const;

    QString title(void);

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
    // void alter(void);
    virtual void touch(void);

// public slots:
//     virtual void update(void);

public slots:
    virtual bool evaluate(dtkComposerEvaluatorPrivate *evaluator);

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
    virtual QList<dtkComposerEdge *> allRoutes(void);
    virtual void removeRoute(dtkComposerEdge *route);

public:
    virtual QVariant DTK_DEPRECATED value(dtkComposerNodeProperty *property);

    virtual void chooseImplementation(void);
    virtual void  setupImplementation(QString implementation = QString());

protected:
    virtual bool dirtyUpstreamNodes(void);
    virtual void markDirtyDownstreamNodes(void);

protected:
    virtual void pull(dtkComposerEdge *route, dtkComposerNodeProperty *property);
    virtual void  run(void);
    virtual void push(dtkComposerEdge *route, dtkComposerNodeProperty *property);

private:
    friend class dtkComposerScene; 
    friend class dtkComposerNodePrivate;

private:
    dtkComposerNodePrivate *d;

public:
    dtkComposerNodeGraphic *g;
      dtkComposerNodeLogic *l;

public:
    virtual dtkComposerNodeAbstractTransmitter *emitter(dtkComposerNodeProperty *property);

public:
    virtual bool onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination);
    virtual bool onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property);

protected:
    friend class dtkComposerEvaluatorPrivate;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode  node);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode& node);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug dbg, dtkComposerNode *node);

#endif
