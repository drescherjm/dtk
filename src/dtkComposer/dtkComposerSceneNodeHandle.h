/* dtkComposerSceneNodeHandle.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep 18 14:05:01 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Mar 25 09:08:14 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class dtkComposerSceneNodeControl;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeHandlePrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNodeHandle
// /////////////////////////////////////////////////////////////////

class  dtkComposerSceneNodeHandle : public QGraphicsItem
{
public:
     dtkComposerSceneNodeHandle(dtkComposerSceneNodeControl *parent);
    ~dtkComposerSceneNodeHandle(void);

public:
    void setTopBlock(dtkComposerSceneNodeComposite *block);
    void setBotBlock(dtkComposerSceneNodeComposite *block);

public:
    void layout(void);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    dtkComposerSceneNodeHandlePrivate *d;
};


