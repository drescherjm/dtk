/* dtkComposerSceneNodeComposite.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:32:09 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 14:50:19 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 39
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODECOMPOSITE_H
#define DTKCOMPOSERSCENENODECOMPOSITE_H

#include "dtkComposerSceneNode.h"

class dtkComposerSceneEdge;
class dtkComposerSceneEdgeList;
class dtkComposerSceneNodeList;
class dtkComposerSceneNodeCompositePrivate;
class dtkComposerSceneNote;
class dtkComposerSceneNoteList;

class dtkComposerSceneNodeComposite : public dtkComposerSceneNode
{
public:
     dtkComposerSceneNodeComposite(void);
    ~dtkComposerSceneNodeComposite(void);

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
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void   reveal(void);
    void unreveal(void);

private:
    dtkComposerSceneNodeCompositePrivate *d;
};

#endif
