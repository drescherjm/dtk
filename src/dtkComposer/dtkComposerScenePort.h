/* dtkComposerScenePort.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:28:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  3 12:29:04 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENEPORT_H
#define DTKCOMPOSERSCENEPORT_H

#include <QtGui>

class dtkComposerScenePortPrivate;

class dtkComposerScenePort : public QGraphicsItem
{
public:
     dtkComposerScenePort(unsigned int id, QGraphicsItem *parent);
    ~dtkComposerScenePort(void);

public:
    unsigned int id(void) const;

public:
    virtual QRectF boundingRect(void) const;

public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:
    dtkComposerScenePortPrivate *d;
};

#endif
