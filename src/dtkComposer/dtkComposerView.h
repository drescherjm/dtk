/* dtkComposerView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:06:52 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  7 15:07:26 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
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
    void wheelEvent(QWheelEvent *event);
};

#endif
