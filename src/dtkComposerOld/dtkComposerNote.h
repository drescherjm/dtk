/* dtkComposerNote.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 26 20:19:26 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 27 00:30:43 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNOTE_H
#define DTKCOMPOSERNOTE_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtGui>

class dtkComposerNode;
class dtkComposerNotePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNote : public QObject, public QGraphicsItem
{
    Q_OBJECT

#if QT_VERSION >= 0x040600
    Q_INTERFACES(QGraphicsItem)
#endif

public:
     dtkComposerNote(dtkComposerNode *parent = 0);
    ~dtkComposerNote(void);

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

private:
    dtkComposerNotePrivate *d;
};

#endif
