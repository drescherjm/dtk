/* dtkComposerScene_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 15:32:14 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  2 23:56:57 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 157
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_P_H
#define DTKCOMPOSERSCENE_P_H

#include <QtGui>

class dtkComposerFactory;
class dtkComposerMachine;
class dtkComposerStack;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePortPrivate;

class dtkComposerScenePort : public QGraphicsItem
{
public:
     dtkComposerScenePort(unsigned int id, QGraphicsItem *parent);
    ~dtkComposerScenePort(void);

public:
    unsigned int id(void) const;

public:
    virtual QRectF boundingRect(void) const;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerScenePortPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneEdgePrivate;

class dtkComposerSceneEdge : public QGraphicsItem
{
public:
     dtkComposerSceneEdge(void);
    ~dtkComposerSceneEdge(void);

public:
    virtual QRectF boundingRect(void) const;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
    dtkComposerScenePort *source(void);
    dtkComposerScenePort *destination(void);

public:
    void setSource(dtkComposerScenePort *port);
    void setDestination(dtkComposerScenePort *port);
    
public:
    void adjust(void);
    void adjust(const QPointF& start, const QPointF& end);

public:
    bool   link(bool anyway = false);
    bool unlink(void);

private:
    dtkComposerSceneEdgePrivate *d;
};

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

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeComposite
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeCompositePrivate;

class dtkComposerSceneNodeComposite : public dtkComposerSceneNode
{
public:
     dtkComposerSceneNodeComposite(void);
    ~dtkComposerSceneNodeComposite(void);

public:
    void    addNode(dtkComposerSceneNode *node);
    void removeNode(dtkComposerSceneNode *node);

public:
    bool entered(void);
    void enter(void);
    void leave(void);

public:
    void layout(void);

public:
    dtkComposerSceneNodeList children(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerSceneNodeCompositePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeLeaf
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNodeLeafPrivate;

class dtkComposerSceneNodeLeaf : public dtkComposerSceneNode
{
public:
     dtkComposerSceneNodeLeaf(void);
    ~dtkComposerSceneNodeLeaf(void);

public:
    void layout(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerSceneNodeLeafPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNote
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNotePrivate;

class dtkComposerSceneNote : public QGraphicsItem
{
public:
     dtkComposerSceneNote(dtkComposerSceneNode *parent = 0);
    ~dtkComposerSceneNote(void);

    QString text(void) const;

    void setSize(const QSizeF& size);
    void setText(const QString& text);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkComposerSceneNotePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePrivate
{
public:
    dtkComposerMachine *machine;
    dtkComposerFactory *factory;
    dtkComposerStack *stack;

// public:
//     dtkComposerSceneNodeComposite *root_node;

public:
    dtkComposerSceneNode *current_node;
    dtkComposerSceneEdge *current_edge;

public:
    QList<dtkComposerSceneEdge *> edges;
    QList<dtkComposerSceneNode *> nodes;
    QList<dtkComposerSceneNote *> notes;
};

#endif
