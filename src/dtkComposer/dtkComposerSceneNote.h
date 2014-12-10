/* dtkComposerSceneNote.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 12:35:30 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 10 17:01:37 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerSceneNode;
class dtkComposerSceneNotePrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNote
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerSceneNote : public QGraphicsItem
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
    dtkComposerSceneNode *parent(void);

public:
    void setParent(dtkComposerSceneNode *parent);

private:
    dtkComposerSceneNotePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneNoteList
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneNoteList : public QList<dtkComposerSceneNote *> {};

