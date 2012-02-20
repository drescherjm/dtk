/* dtkComposerGraphEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:08:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 20 14:47:22 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 31
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
    dtkComposerGraphNode *source(void);
    dtkComposerGraphNode *destination(void);

public:
    int id(void);

public:
    void setId(int id);
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

class dtkComposerGraphEdgeList : public QList<dtkComposerGraphEdge *>
{
public:
    dtkComposerGraphEdgeList(void);
    dtkComposerGraphEdgeList(const QList<dtkComposerGraphEdge *>& other);
};

#endif
