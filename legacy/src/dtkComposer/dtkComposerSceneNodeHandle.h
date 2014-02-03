/* dtkComposerSceneNodeHandle.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep 18 14:05:01 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 14:41:22 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENODEHANDLE_H
#define DTKCOMPOSERSCENENODEHANDLE_H

#include <dtkComposerExport.h>

#include <QtCore>
#include <QtGui>

class dtkComposerSceneNodeControl;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeHandlePrivate;

class DTKCOMPOSER_EXPORT dtkComposerSceneNodeHandle : public QGraphicsItem
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

#endif
