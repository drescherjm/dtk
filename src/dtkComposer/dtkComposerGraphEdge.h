/* dtkComposerGraphEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:08:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  9 15:59:01 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
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
#include <QtGui>

class dtkComposerGraphEdgePrivate;
class dtkComposerGraphNode;

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdge
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphEdge : public QGraphicsItem
{
public:
     dtkComposerGraphEdge(void);
    ~dtkComposerGraphEdge(void);

public:
    void setSource(dtkComposerGraphNode *source);
    void setDestination(dtkComposerGraphNode *destination);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerGraphEdgePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdgeList
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphEdgeList : public QList<dtkComposerGraphEdge *> {};

#endif
