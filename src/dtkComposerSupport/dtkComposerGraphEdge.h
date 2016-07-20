/* dtkComposerGraphEdge.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:08:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:11:34 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 73
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPHEDGE_H
#define DTKCOMPOSERGRAPHEDGE_H

#include <QtCore>
#include <QtWidgets>

#include <dtkMath/dtkGraphEdge.h>
#include "dtkComposerGraphNode.h"

class dtkComposerGraphEdgePrivate;
class dtkGraphEdge;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphEdge : public QGraphicsItem, public dtkGraphEdge
{
public:
    dtkComposerGraphEdge(void);
    ~dtkComposerGraphEdge(void);

public:
    dtkComposerGraphNode *source(void) const ;
    dtkComposerGraphNode *destination(void) const;

public:
    int id(void);

public:
    void setId(int id);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void drawArrow(QPainter *p, QPointF from, QPointF to, qreal size = 10, qreal end_margin = 18);

private:
    dtkComposerGraphEdgePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdgeList
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphEdgeList : public QList<dtkComposerGraphEdge *>
{
public:
    dtkComposerGraphEdgeList(void);
    dtkComposerGraphEdgeList(const QList<dtkComposerGraphEdge *>& other);
};

#endif
