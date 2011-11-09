/* dtkComposerNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:47:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov  9 12:14:27 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 145
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
    void appendBlock(dtkComposerNodeControlBlock *block);
    void removeBlock(dtkComposerNodeControlBlock *block);

    void setCurrentBlock(dtkComposerNodeControlBlock *block);

public:
    dtkComposerNodeControlBlock    *block(const QString& title);
    dtkComposerNodeControlBlock *addBlock(const QString& title);

    QList<dtkComposerNodeControlBlock *> blocks(void);

    dtkComposerNodeControlBlock *currentBlock(void);

public:
    virtual void appendBlockLeftProperty(QString name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block);
    virtual void appendBlockRightProperty(QString name, dtkComposerNodeProperty::Behavior behavior, dtkComposerNodeProperty::Multiplicity multiplicity, dtkComposerNodeControlBlock *block);

    QList<dtkComposerNodeProperty *>  leftProperties(dtkComposerNodeControlBlock *block);
    QList<dtkComposerNodeProperty *> rightProperties(dtkComposerNodeControlBlock *block);

public:
    dtkComposerNodeProperty  *inputProperty(const QString& block_title, const QString& name) const;
    dtkComposerNodeProperty *outputProperty(const QString& block_title, const QString& name) const;

public:
    void  addInputRelayRoute(dtkComposerEdge *route);
    void addOutputRelayRoute(dtkComposerEdge *route);

    void  removeInputRelayRoute(dtkComposerEdge *route);
    void removeOutputRelayRoute(dtkComposerEdge *route);
    void   removeAllRelayRoutes(void);

    QList<dtkComposerEdge *>  inputRelayRoutes(void);
    QList<dtkComposerEdge *> outputRelayRoutes(void);

    void  addInputActiveRoute(dtkComposerEdge *route);
    void addOutputActiveRoute(dtkComposerEdge *route);

    void  removeInputActiveRoute(dtkComposerEdge *route);
    void removeOutputActiveRoute(dtkComposerEdge *route);
    void   removeAllActiveRoutes(void);

    QList<dtkComposerEdge *>  inputActiveRoutes(void);
    QList<dtkComposerEdge *> outputActiveRoutes(void);

    QList<dtkComposerEdge *> allRoutes(void);
    void removeRoute(dtkComposerEdge *route);

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
            bool dirtyInputValue(void);
            bool dirtyUpstreamNodes(void);
    virtual bool dirtyBlockEndNodes(void);

    void markDirtyDownstreamNodes(void);

    void cleanInputActiveRoutes(void);
    void cleanOutputActiveRoutes(void);

protected:
    virtual void pull(dtkComposerEdge *i_route, dtkComposerNodeProperty *property);
    virtual void push(dtkComposerEdge *o_route, dtkComposerNodeProperty *property);

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
