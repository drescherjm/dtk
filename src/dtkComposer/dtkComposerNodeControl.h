/* dtkComposerNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:47:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar 17 09:10:19 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 84
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROL_H
#define DTKCOMPOSERNODECONTROL_H

#include "dtkComposerNode.h"

class dtkComposerNodeControlBlock;
class dtkComposerNodeControlPrivate;

class dtkComposerNodeControl : public dtkComposerNode
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

public:
    void layout(void);
  
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void resize(const QRectF& rect);
    void resize(const QPointF& delta);
    void resize(qreal dw, qreal dh);
    void resize(void);

    QRectF minimalBoundingRect(void);

public slots:
    virtual void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void update(void) = 0;

protected:
    bool condition(void);
    QVariant value(void);

protected:
    void setColor(const QColor& color);
    void setInputPropertyName(const QString& name);

private:
    dtkComposerNodeControlPrivate *d;
};

#endif
