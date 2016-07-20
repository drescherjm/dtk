/* dtkComposerSceneEdge.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:29:21 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 25 09:07:07 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 36
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtWidgets>

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
    virtual QPainterPath shape(void) const;

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
    void setConnected(bool value);

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

