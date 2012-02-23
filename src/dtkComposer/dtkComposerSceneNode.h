/* dtkComposerSceneNode.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:31:15 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 23 17:02:17 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 70
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
class dtkComposerSceneEdgeList;
class dtkComposerScenePort;
class dtkComposerScenePortList;

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

    dtkComposerSceneEdgeList  inputEdges(void);
    dtkComposerSceneEdgeList outputEdges(void);

public:
    void  addInputPort(dtkComposerScenePort *port);
    void addOutputPort(dtkComposerScenePort *port);

    void  removeInputPort(dtkComposerScenePort *port);
    void removeOutputPort(dtkComposerScenePort *port);

    dtkComposerScenePortList  inputPorts(void);
    dtkComposerScenePortList outputPorts(void);

#pragma mark -
#pragma mark Attributes setup

public:
    const QString& title(void);

public:
    void setTitle(const QString& title);

public:
    bool embedded(void);

public:
    void setEmbedded(bool embedded);

#pragma mark -
#pragma mark Graphics

public:
    virtual QRectF boundingRect(void) const = 0;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) = 0;

public:
    virtual void layout(void) = 0;

public:
    virtual void resize(qreal width, qreal height) = 0;

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
