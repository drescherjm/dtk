/* dtkComposerSceneNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:43:44 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 11:06:39 2012 (+0100)
 *           By: tkloczko
 *     Update #: 56
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODECONTROL_H
#define DTKCOMPOSERSCENENODECONTROL_H

#include "dtkComposerSceneNode.h"

class dtkComposerNodeControl;
class dtkComposerSceneEdgeList;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeControlPrivate;
class dtkComposerSceneNodeLeaf;

class dtkComposerSceneNodeControl : public dtkComposerSceneNode
{
public:
     dtkComposerSceneNodeControl(void);
    ~dtkComposerSceneNodeControl(void);

public:
    void wrap(dtkComposerNode *wrapee);

public:
    QList<dtkComposerSceneNodeComposite *> blocks(void);

public:
    dtkComposerSceneNodeComposite *block(const QString& title);

public:
    dtkComposerSceneNodeLeaf *header(void);
    dtkComposerSceneNodeLeaf *footer(void);

protected:
    void   setHeader(dtkComposerSceneNodeLeaf *header);
    void   setFooter(dtkComposerSceneNodeLeaf *footer);
    
protected:
    void    addBlock(dtkComposerSceneNodeComposite *block);
    void removeBlock(dtkComposerSceneNodeComposite *block);

public:
    void layout(void);

public:
    void resize(qreal width, qreal height);

public:
    dtkComposerSceneNodeComposite *blockAt(const QPointF& point) const;

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkComposerSceneNodeControlPrivate *d;
};

#endif
