/* dtkComposerSceneNote.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:35:30 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb  5 23:03:30 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENENOTE_H
#define DTKCOMPOSERSCENENOTE_H

#include <QtGui>

class dtkComposerSceneNodeComposite;
class dtkComposerSceneNotePrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNote
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNote : public QGraphicsItem
{
public:
     dtkComposerSceneNote(void);
    ~dtkComposerSceneNote(void);

    QString text(void) const;

    void setSize(const QSizeF& size);
    void setText(const QString& text);

public:
    QRectF boundingRect(void) const;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

public:
    dtkComposerSceneNodeComposite *parent(void);

public:
    void setParent(dtkComposerSceneNodeComposite *parent);

private:
    dtkComposerSceneNotePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNoteList
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNoteList : public QList<dtkComposerSceneNote *> {};

#endif
