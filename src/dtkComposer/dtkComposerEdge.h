/* dtkComposerEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 14:26:53 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 15:04:22 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREDGE_H
#define DTKCOMPOSEREDGE_H

#include <QtCore>
#include <QtGui>

class dtkComposerEdgePrivate;

class dtkComposerEdge : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
     dtkComposerEdge(void);
    ~dtkComposerEdge(void);

    QRectF boundingRect(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    dtkComposerEdgePrivate *d;
};

#endif
