/* dtkComposerView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:07:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Dec 10 22:51:56 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 160
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
}

dtkComposerView::~dtkComposerView(void)
{

}

void dtkComposerView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && (event->modifiers() & Qt::AltModifier))
        this->setDragMode(QGraphicsView::ScrollHandDrag);
    else
        this->setDragMode(QGraphicsView::RubberBandDrag);

    QGraphicsView::mousePressEvent(event);
}

void dtkComposerView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void dtkComposerView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = pow((double)2, -event->delta() / 240.0);

    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < 0.1 || factor > 10)
        return;
    
    this->scale(scaleFactor, scaleFactor);
}
