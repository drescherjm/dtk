/* dtkComposerGraphNode.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:08:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:22:11 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 162
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>
#include <QtWidgets>

class dtkComposerGraph;
class dtkComposerGraphNodePrivate;
class dtkComposerGraphNodeList;
class dtkComposerNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNode
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNode : public QGraphicsObject
{
    Q_OBJECT

public:
     dtkComposerGraphNode(void);
    ~dtkComposerGraphNode(void);

public:
    enum Status { Ready, Done, Running, Break};
    enum   Kind { SelectBranch, Leaf, Data, Process, View, Actor, Begin, BeginLoop, BeginComposite,BeginIf, End, SetOutputs, SetInputs, SetVariables, SetConditions };

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
    void addChild(dtkComposerGraphNode *node);
    void removeChild(dtkComposerGraphNode *node);

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
    bool   breakpoint(void);
    bool   endloop(void);

public:
    dtkComposerGraph    *graph(void);
    void              setGraph(dtkComposerGraph *graph);

public:
    virtual void clean(void);

public:
    void  setStatus(Status status);
    void  setEndLoop(bool value = true);

public:
    void  setBreakPoint(bool value = true);

public:
    virtual dtkComposerGraphNodeList successors(void);
    virtual dtkComposerGraphNode    *firstSuccessor(void);
    virtual dtkComposerGraphNodeList predecessors(void);
            dtkComposerGraphNodeList childs(void);
    virtual dtkComposerGraphNodeList evaluableChilds(void);

public:
    const QString&  title(void);

public slots:
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

