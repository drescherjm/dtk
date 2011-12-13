/* dtkComposerNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:47:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec 13 13:25:12 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 188
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROL_H
#define DTKCOMPOSERNODECONTROL_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"
#include "dtkComposerNodeProperty.h"

class dtkComposerEdge;
class dtkComposerNodeControlBlock;

class dtkComposerNodeControlPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControl : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeControl(dtkComposerNode *parent = 0);
    ~dtkComposerNodeControl(void);

public:
    void     appendBlock(dtkComposerNodeControlBlock *block);
    void     removeBlock(dtkComposerNodeControlBlock *block);
    void setCurrentBlock(dtkComposerNodeControlBlock *block);

    void      appendBlockProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block);
    void  appendBlockLeftProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block);
    void appendBlockRightProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block);

    void      removeBlockProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeControlBlock *block);
    void  removeBlockLeftProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeControlBlock *block);
    void removeBlockRightProperty(const QString& name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeControlBlock *block);

public:
    const QList<dtkComposerNodeControlBlock *>& blocks(void) const;

    dtkComposerNodeControlBlock        *block(const QString& title) const;
    dtkComposerNodeControlBlock *currentBlock(void) const;

    const QList<dtkComposerNodeProperty *>&  leftProperties(const QString& block_title) const;
    const QList<dtkComposerNodeProperty *>& rightProperties(const QString& block_title) const;

    dtkComposerNodeProperty  *leftProperty(const QString& block_title, const QString& name) const;
    dtkComposerNodeProperty *rightProperty(const QString& block_title, const QString& name) const;

public:
    void  addLeftRelayRoute(dtkComposerRoute *route);
    void addRightRelayRoute(dtkComposerRoute *route);

    void  removeLeftRelayRoute(dtkComposerRoute *route);
    void removeRightRelayRoute(dtkComposerRoute *route);
    void   removeAllRelayRoutes(void);

    void  addLeftActiveRoute(dtkComposerRoute *route);
    void addRightActiveRoute(dtkComposerRoute *route);

    void  removeLeftActiveRoute(dtkComposerRoute *route);
    void removeRightActiveRoute(dtkComposerRoute *route);
    void   removeAllActiveRoutes(void);

public:
    QList<dtkComposerRoute *>  leftRelayRoutes(void);
    QList<dtkComposerRoute *> rightRelayRoutes(void);

    QList<dtkComposerRoute *>  leftActiveRoutes(void);
    QList<dtkComposerRoute *> rightActiveRoutes(void);

    QList<dtkComposerRoute *> allRoutes(void);
    void removeRoute(dtkComposerRoute *route);

public:
    bool isRunning(void);

protected:
    bool condition(void);
    QVariant value(void);

    dtkComposerNodeProperty *inputProperty(void);
    void disableInputProperty(void);

protected:
    void setRunning(bool running);

protected:
    bool    dirtyLeftValue(void);
    bool dirtyUpstreamNodes(void);

    void markDirtyDownstreamNodes(void);

    void  cleanLeftActiveRoutes(void);
    void cleanRightActiveRoutes(void);

protected:
    virtual void pull(dtkComposerRoute *i_route, dtkComposerNodeProperty *property);
    virtual void run(void);
    virtual void push(dtkComposerRoute *o_route, dtkComposerNodeProperty *property);

public:
    void layout(void);
  
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void resize(const QRectF& rect);
    void resize(const QPointF& delta);
    void resize(qreal dw, qreal dh);
    void resize(void);

    QRectF minimalBoundingRect(void);

protected:
    void setColor(const QColor& color);
    void setInputPropertyName(const QString& name);

private:
    dtkComposerNodeControlPrivate *d;

private:
    friend class dtkComposerEvaluatorPrivate;
};

#endif
