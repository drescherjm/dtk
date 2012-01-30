/* dtkComposerScene_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 15:32:14 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 23:53:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 77
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_P_H
#define DTKCOMPOSERSCENE_P_H

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePortPrivate;

class dtkComposerScenePort : public QGraphicsItem
{
#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
     dtkComposerScenePort(QGraphicsItem *parent);
    ~dtkComposerScenePort(void);

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
#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

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
#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
     dtkComposerSceneNode(void);
    ~dtkComposerSceneNode(void);

public:
    void  addInputEdge(dtkComposerSceneEdge *edge);
    void addOutputEdge(dtkComposerSceneEdge *edge);

    void  removeInputEdge(dtkComposerSceneEdge *edge);
    void removeOutputEdge(dtkComposerSceneEdge *edge);

    QList<dtkComposerSceneEdge *> inputEdges(void);
    QList<dtkComposerSceneEdge *> outputEdges(void);

public:
    virtual QRectF boundingRect(void) const;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
    QList<dtkComposerScenePort *>  inputPorts(void);
    QList<dtkComposerScenePort *> outputPorts(void);

protected:
    void layout(void);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);

private:
    dtkComposerSceneNodePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePrivate
{
public:
    dtkComposerSceneEdge *current_edge;

public:
    QList<dtkComposerSceneEdge *> edges;
    QList<dtkComposerSceneNode *> nodes;
};

#endif
