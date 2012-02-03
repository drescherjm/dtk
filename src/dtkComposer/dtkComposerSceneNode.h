/* dtkComposerSceneNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:31:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 12:31:58 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODE_H
#define DTKCOMPOSERSCENENODE_H

#include <QtGui>

class dtkComposerSceneEdge;
class dtkComposerScenePort;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNode
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodePrivate;

class dtkComposerSceneNode : public QGraphicsItem
{
public:
             dtkComposerSceneNode(void);
    virtual ~dtkComposerSceneNode(void);

public:
    void  addInputEdge(dtkComposerSceneEdge *edge);
    void addOutputEdge(dtkComposerSceneEdge *edge);

    void  removeInputEdge(dtkComposerSceneEdge *edge);
    void removeOutputEdge(dtkComposerSceneEdge *edge);

    QList<dtkComposerSceneEdge *> inputEdges(void);
    QList<dtkComposerSceneEdge *> outputEdges(void);

public:
    QList<dtkComposerScenePort *>  inputPorts(void);
    QList<dtkComposerScenePort *> outputPorts(void);

public:
    dtkComposerScenePort *port(unsigned int id);

public:
    virtual QRectF boundingRect(void) const = 0;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) = 0;

protected:
    virtual void layout(void) = 0;

// protected:
//     QVariant itemChange(GraphicsItemChange change, const QVariant& value);

protected:
    dtkComposerSceneNodePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeList
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeList : public QList<dtkComposerSceneNode *> {};

#endif
