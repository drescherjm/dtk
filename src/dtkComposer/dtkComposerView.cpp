/* dtkComposerView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:07:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov 29 17:01:22 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 87
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerView.h"

dtkComposerView::dtkComposerView(QWidget *parent) : QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setBackgroundBrush(QColor(0x32, 0x32, 0x32));
    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setAcceptDrops(true);

    this->setDragMode(QGraphicsView::RubberBandDrag);
}

dtkComposerView::~dtkComposerView(void)
{

}

void dtkComposerView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = pow((double)2, -event->delta() / 240.0);

    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < 0.1 || factor > 10)
        return;
    
    scale(scaleFactor, scaleFactor);
}
