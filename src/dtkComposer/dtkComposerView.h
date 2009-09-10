/* dtkComposerView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:52 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep  8 22:10:44 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERVIEW_H
#define DTKCOMPOSERVIEW_H

#include <QtCore>
#include <QtGui>

class dtkComposerView : public QGraphicsView
{
public:
     dtkComposerView(QWidget *parent = 0);
    ~dtkComposerView(void);

    void drawBackground(QPainter *painter, const QRectF& rect);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif
