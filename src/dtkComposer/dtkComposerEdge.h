/* dtkComposerEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 14:26:53 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep  8 13:14:48 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
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
class dtkComposerNodeProperty;

class dtkComposerEdge : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
     dtkComposerEdge(void);
    ~dtkComposerEdge(void);

    dtkComposerNodeProperty *source(void);
    dtkComposerNodeProperty *destination(void);

    void setSource(dtkComposerNodeProperty *property);
    void setDestination(dtkComposerNodeProperty *property);

public:
    QRectF boundingRect(void) const;

    QPointF start(void) const;
    QPointF end(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void adjust(void);
    void adjust(const QPointF& start, const QPointF& end);

    bool link(void);
    bool unlink(void);

private:
    dtkComposerEdgePrivate *d;
};

#endif
