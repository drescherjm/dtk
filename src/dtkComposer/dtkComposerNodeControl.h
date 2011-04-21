/* dtkComposerNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:47:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 20 10:21:54 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 101
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

class dtkComposerNodeControlBlock;
class dtkComposerNodeControlPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControl : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeControl(dtkComposerNode *parent = 0);
    ~dtkComposerNodeControl(void);
  
    dtkComposerNodeControlBlock    *block(const QString& title);
    dtkComposerNodeControlBlock *addBlock(const QString& title);

    virtual int removeBlock(dtkComposerNodeControlBlock *block, bool clean = false);
    virtual int removeBlock(const QString& title);

    QList<dtkComposerNodeControlBlock *> blocks(void);

    dtkComposerNodeProperty  *inputProperty(const QString& block_title, const QString& name) const;
    dtkComposerNodeProperty *outputProperty(const QString& block_title, const QString& name) const;

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

    void setRunning(bool running);
    bool  isRunning(void);

public:
    void layout(void);
  
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void resize(const QRectF& rect);
    void resize(const QPointF& delta);
    void resize(qreal dw, qreal dh);
    void resize(void);

    QRectF minimalBoundingRect(void);

public slots:
    virtual void update(void) = 0;

protected:
    bool condition(void);
    QVariant value(void);

    dtkComposerNodeProperty *inputProperty(void);

protected:
    void setColor(const QColor& color);
    void setInputPropertyName(const QString& name);

private:
    dtkComposerNodeControlPrivate *d;
};

#endif
