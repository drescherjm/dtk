/* dtkComposerNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:47:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 15:19:48 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 178
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
    void  addInputRelayRoute(dtkComposerRoute *route);
    void addOutputRelayRoute(dtkComposerRoute *route);

    void  removeInputRelayRoute(dtkComposerRoute *route);
    void removeOutputRelayRoute(dtkComposerRoute *route);
    void   removeAllRelayRoutes(void);

    void  addInputActiveRoute(dtkComposerRoute *route);
    void addOutputActiveRoute(dtkComposerRoute *route);

    void  removeInputActiveRoute(dtkComposerRoute *route);
    void removeOutputActiveRoute(dtkComposerRoute *route);
    void   removeAllActiveRoutes(void);

public:
    QList<dtkComposerRoute *>  inputRelayRoutes(void);
    QList<dtkComposerRoute *> outputRelayRoutes(void);

    QList<dtkComposerRoute *>  inputActiveRoutes(void);
    QList<dtkComposerRoute *> outputActiveRoutes(void);

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
    bool    dirtyInputValue(void);
    bool dirtyUpstreamNodes(void);

    void markDirtyDownstreamNodes(void);

    void cleanInputActiveRoutes(void);
    void cleanOutputActiveRoutes(void);

protected:
    virtual void pull(dtkComposerRoute *i_route, dtkComposerNodeProperty *property);
    virtual void push(dtkComposerRoute *o_route, dtkComposerNodeProperty *property);

    void run(void);

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
