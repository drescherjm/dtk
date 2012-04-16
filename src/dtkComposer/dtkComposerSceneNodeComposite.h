/* dtkComposerSceneNodeComposite.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:32:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Apr 16 12:20:22 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 61
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODECOMPOSITE_H
#define DTKCOMPOSERSCENENODECOMPOSITE_H

#include "dtkComposerExport.h"
#include "dtkComposerSceneNode.h"

class dtkComposerSceneEdge;
class dtkComposerSceneEdgeList;
class dtkComposerSceneNodeList;
class dtkComposerSceneNodeCompositePrivate;
class dtkComposerSceneNote;
class dtkComposerSceneNoteList;

class DTKCOMPOSER_EXPORT dtkComposerSceneNodeComposite : public dtkComposerSceneNode
{
public:
     dtkComposerSceneNodeComposite(void);
    ~dtkComposerSceneNodeComposite(void);

public:
    void wrap(dtkComposerNode *wrapee);

public:
    void setFormer(dtkComposerSceneNodeComposite *former);

public:
    dtkComposerSceneNodeComposite *former(void);

public:
    void    addNote(dtkComposerSceneNote *note);
    void removeNote(dtkComposerSceneNote *note);

    void    addNode(dtkComposerSceneNode *node);
    void removeNode(dtkComposerSceneNode *node);

    void    addEdge(dtkComposerSceneEdge *edge);
    void removeEdge(dtkComposerSceneEdge *edge);

public:
    dtkComposerSceneNoteList notes(void);
    dtkComposerSceneNodeList nodes(void);
    dtkComposerSceneEdgeList edges(void);

public:
    bool entered(void);
    bool flattened(void);

public:
    void enter(void);
    void leave(void);

public:
    void flatten(void);
    void unflatten(void);

public:
    bool root(void);

public:
    void setRoot(bool);

public:
    void layout(void);

public:
    void resize(qreal width, qreal height);

public:
    void obfuscate(void);

public:
    void boundingBox(qreal& x_min, qreal& x_max, qreal& y_min, qreal& y_max);

    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void   reveal(void);
    void unreveal(void);

public:
    void resetPos(const QPointF& pos, const QRectF& rect);

public:
    void  setUnrevealPos(const QPointF& pos);
    void setUnrevealRect(const QRectF& rect);
    
    QPointF  unrevealPos(void) const;
    QRectF  unrevealRect(void) const;

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    dtkComposerSceneNodeCompositePrivate *d;
};

#endif
