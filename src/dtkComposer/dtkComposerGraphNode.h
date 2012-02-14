/* dtkComposerGraphNode.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:08:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr. 14 15:42:03 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 49
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

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphNode
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphNode : public QGraphicsItem
{
public:
     dtkComposerGraphNode(void);
    ~dtkComposerGraphNode(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

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
