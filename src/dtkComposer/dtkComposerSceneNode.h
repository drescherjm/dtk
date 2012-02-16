/* dtkComposerSceneNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:31:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 13:00:42 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 57
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

class dtkComposerNode;
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

#pragma mark -
#pragma mark Wrapping of logic

public:
    virtual void wrap(dtkComposerNode *wrapee);

public:
    dtkComposerNode *wrapee(void);

#pragma mark -
#pragma mark Parent/Child relationships

public:
    dtkComposerSceneNode *parent(void);

public:
    void setParent(dtkComposerSceneNode *parent);

#pragma mark -
#pragma mark Structure management

public:
    void  addInputEdge(dtkComposerSceneEdge *edge);
    void addOutputEdge(dtkComposerSceneEdge *edge);

    void  removeInputEdge(dtkComposerSceneEdge *edge);
    void removeOutputEdge(dtkComposerSceneEdge *edge);

    QList<dtkComposerSceneEdge *>  inputEdges(void);
    QList<dtkComposerSceneEdge *> outputEdges(void);

public:
    void  addInputPort(dtkComposerScenePort *port);
    void addOutputPort(dtkComposerScenePort *port);

    void  removeInputPort(dtkComposerScenePort *port);
    void removeOutputPort(dtkComposerScenePort *port);

    QList<dtkComposerScenePort *>  inputPorts(void);
    QList<dtkComposerScenePort *> outputPorts(void);

#pragma mark -
#pragma mark Attributes setup

public:
    const QString& title(void);

public:
    void setTitle(const QString& title);

public:
    dtkComposerScenePort *port(unsigned int id);

#pragma mark -
#pragma mark Graphics

public:
    virtual QRectF boundingRect(void) const = 0;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) = 0;

public:
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
