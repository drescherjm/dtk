/* dtkComposerNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:47:08 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 19:20:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 23
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

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBloc
// /////////////////////////////////////////////////////////////////

#include <QtGui>

class dtkComposerNodeControlBloc : public QGraphicsRectItem
{
public:
     dtkComposerNodeControlBloc(QGraphicsItem *parent);
    ~dtkComposerNodeControlBloc(void);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate;

class dtkComposerNodeControl : public dtkComposerNode
{
    Q_OBJECT

public:
     dtkComposerNodeControl(dtkComposerNode *parent = 0);
    ~dtkComposerNodeControl(void);
  
    dtkComposerNodeControlBloc *addBlock(void);

public:
    void layout(void);
  
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    virtual void  onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property);
    virtual void update(void) = 0;

private:
    dtkComposerNodeControlPrivate *d;
};

#endif
