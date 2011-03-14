/* dtkComposerEdge.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 14:26:53 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Mar  5 20:48:57 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSEREDGE_H
#define DTKCOMPOSEREDGE_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtGui>

class dtkComposerNode;
class dtkComposerNodeProperty;
class dtkComposerEdgePrivate;

class DTKCOMPOSER_EXPORT dtkComposerEdge : public QObject, public QGraphicsItem
{
    Q_OBJECT

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
     dtkComposerEdge(void);
    ~dtkComposerEdge(void);

    QString description(void);   

    dtkComposerNodeProperty *source(void);
    dtkComposerNodeProperty *destination(void);

    void setSource(dtkComposerNodeProperty *property);
    void setDestination(dtkComposerNodeProperty *property);

public:
    friend QDebug operator<<(QDebug dbg, dtkComposerEdge  edge);
    friend QDebug operator<<(QDebug dbg, dtkComposerEdge& edge);
    friend QDebug operator<<(QDebug dbg, dtkComposerEdge *edge);

public:
    QRectF boundingRect(void) const;

    QPointF start(void) const;
    QPointF end(void) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void adjust(void);
    void adjust(const QPointF& start, const QPointF& end);

    bool   link(bool anyway = false);
    bool unlink(void);

private:
    dtkComposerEdgePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

QDebug operator<<(QDebug dbg, dtkComposerEdge  edge);
QDebug operator<<(QDebug dbg, dtkComposerEdge& edge);
QDebug operator<<(QDebug dbg, dtkComposerEdge *edge);

#endif
