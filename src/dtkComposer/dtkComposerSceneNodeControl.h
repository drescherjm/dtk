/* dtkComposerSceneNodeControl.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Feb  8 15:43:44 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 16 12:12:33 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
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
    virtual void layout(void);

public:
    virtual QRectF boundingRect(void) const;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerSceneNodeControlPrivate *d;
};

#endif
