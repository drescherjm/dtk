/* dtkComposerGraphNode.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:08:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. mars 16 18:05:55 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 105
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHNODE_H
#define DTKCOMPOSERGRAPHNODE_H

#include <QtCore>
#include <QtGui>

class dtkComposerGraphNodePrivate;
class dtkComposerGraphNodeList;
class dtkComposerNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNode
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNode : public QGraphicsItem
{
public:
     dtkComposerGraphNode(void);
    ~dtkComposerGraphNode(void);

public:
    enum Status { Done, Running, BreakPoint, Ready};
    enum   Kind { SelectBranch, Leaf, Begin, End, SetOutputs, SetInputs, SetVariables, SetConditions };

public:
    QRectF boundingRect(void) const;

public:
    virtual dtkComposerNode *wrapee(void);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void setTitle(const QString& title);

public:
    void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);

public:
    virtual void addSuccessor(dtkComposerGraphNode *node, int id = 0);
            void addPredecessor(dtkComposerGraphNode *node);

public:
    virtual void removeSuccessor(dtkComposerGraphNode *node);
            void removePredecessor(dtkComposerGraphNode *node);

public:
    virtual Kind kind(void) = 0;

public:
    Status status(void);

public:
    void  setStatus(Status status);

public:
    virtual dtkComposerGraphNodeList successors();
            dtkComposerGraphNodeList predecessors();

public:
    const QString&  title(void);

    virtual void eval() ;

private:
    dtkComposerGraphNodePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNodeList
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNodeList : public QList<dtkComposerGraphNode *>
{
public:
    dtkComposerGraphNodeList(void);
    dtkComposerGraphNodeList(const QList<dtkComposerGraphNode *>& other);
};

#endif
