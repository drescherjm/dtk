/* dtkComposerSceneNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:43:44 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 17:01:34 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 63
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODECONTROL_H
#define DTKCOMPOSERSCENENODECONTROL_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerSceneNode.h"

class dtkComposerNodeControl;
class dtkComposerSceneEdgeList;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeControlPrivate;
class dtkComposerSceneNodeLeaf;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerSceneNodeControl : public dtkComposerSceneNode
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

public:
    void    addBlock(dtkComposerSceneNodeComposite *block);
    void removeBlock(dtkComposerSceneNodeComposite *block);

public:
    void layout(void);

public:
    void setBlockSize(dtkComposerSceneNodeComposite *block, qreal x, qreal y, qreal w, qreal h);
    void resizeBlock(dtkComposerSceneNodeComposite *block, qreal dx, qreal dy);
    void moveBlock(dtkComposerSceneNodeComposite *block, qreal dx, qreal dy);

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
