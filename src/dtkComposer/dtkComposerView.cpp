/* dtkComposerView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:07:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Mar 28 13:49:57 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 185
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
    this->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
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

void dtkComposerView::setBackgroundColor(const QColor &color)
{
    this->setBackgroundBrush(color);
}

void dtkComposerView::onCenterOn(const QPointF& point)
{
    this->centerOn(point);
}

void dtkComposerView::onFitInView(const QRectF& rect)
{
    // this->fitInView(rect, Qt::KeepAspectRatio);
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
    qreal scaleFactor = pow((double)2, -event->delta() / 500.0);

    qreal factor = this->matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < 0.1 || factor > 2.)
        return;
    
    this->scale(scaleFactor, scaleFactor);
}
