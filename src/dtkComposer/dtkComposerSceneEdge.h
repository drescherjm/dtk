/* dtkComposerSceneEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:29:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 16:02:44 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENEEDGE_H
#define DTKCOMPOSERSCENEEDGE_H

#include <QtGui>

class dtkComposerSceneEdgePrivate;
class dtkComposerSceneNode;
class dtkComposerScenePort;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneEdge
// /////////////////////////////////////////////////////////////////

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

public:
    bool   valid(void);
    bool invalid(void);

public:
    void   validate(void);
    void invalidate(void);

public:
    dtkComposerSceneNode *parent(void);

public:
    void setParent(dtkComposerSceneNode *parent);

private:
    dtkComposerSceneEdgePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneEdgeList
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneEdgeList : public QList<dtkComposerSceneEdge *> {};

#endif
