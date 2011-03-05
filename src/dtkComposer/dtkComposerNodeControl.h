/* dtkComposerNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:47:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Mar  5 21:38:41 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 64
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
  
    dtkComposerNodeControlBlock *addBlock(const QString& title);

    QList<dtkComposerNodeControlBlock *> blocks(void);

    dtkComposerNodeProperty  *inputProperty(const QString& block_title, const QString& name) const;
    dtkComposerNodeProperty *outputProperty(const QString& block_title, const QString& name) const;

public:
    void layout(void);
  
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool resize(const QRectF& rect);

public slots:
    virtual void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void update(void) = 0;

protected:
    bool condition(void);

protected:
    void setColor(const QColor& color);
    void setInputPropertyName(const QString& name);

private:
    dtkComposerNodeControlPrivate *d;
};

#endif
