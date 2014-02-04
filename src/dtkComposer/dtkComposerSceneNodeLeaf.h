/* dtkComposerSceneNodeLeaf.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:34:45 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 10 16:47:10 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 44
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerSceneNode.h"

class dtkComposerNode;
class dtkComposerSceneNodeLeafPrivate;

class  dtkComposerSceneNodeLeaf : public dtkComposerSceneNode
{
public:
     dtkComposerSceneNodeLeaf(void);
    ~dtkComposerSceneNodeLeaf(void);

public:
    void wrap(dtkComposerNode *node);

public:
    void flag(Qt::GlobalColor color, bool on);
    void flag(QColor color);
    bool flagged(Qt::GlobalColor color);
    bool flagged(void);

    QString flagColorName(void);
    Qt::GlobalColor flagColor(void);

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

