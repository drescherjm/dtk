// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerSceneNode.h"

class dtkComposerNodeControl;
class dtkComposerSceneEdgeList;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeControlPrivate;
class dtkComposerSceneNodeLeaf;

class DTKCOMPOSER_EXPORT dtkComposerSceneNodeControl : public dtkComposerSceneNode
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

//
// dtkComposerSceneNodeControl.h ends here
