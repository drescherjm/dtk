/* dtkComposerSceneNodeLeaf.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:34:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Nov 20 15:14:20 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODELEAF_H
#define DTKCOMPOSERSCENENODELEAF_H

#include "dtkComposerExport.h"

#include "dtkComposerSceneNode.h"

class dtkComposerNode;
class dtkComposerSceneNodeLeafPrivate;

class DTKCOMPOSER_EXPORT dtkComposerSceneNodeLeaf : public dtkComposerSceneNode
{
public:
     dtkComposerSceneNodeLeaf(void);
    ~dtkComposerSceneNodeLeaf(void);

public:
    void wrap(dtkComposerNode *node);

public:
    void flag(Qt::GlobalColor color, bool on);
    bool flagged(Qt::GlobalColor color);

public:
    void layout(void);

public:
    void resize(qreal width, qreal height);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerSceneNodeLeafPrivate *d;
};

#endif
