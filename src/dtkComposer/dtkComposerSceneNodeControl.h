/* dtkComposerSceneNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:43:44 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 18:26:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 42
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

protected:
    void   setHeader(dtkComposerSceneNodeLeaf *header);
    void   setFooter(dtkComposerSceneNodeLeaf *header);
    
protected:
    void    addBlock(dtkComposerSceneNodeComposite *block);
    void removeBlock(dtkComposerSceneNodeComposite *block);

public:
    void layout(void);

public:
    void resize(qreal width, qreal height);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerSceneNodeControlPrivate *d;
};

#endif
