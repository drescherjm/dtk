/* dtkComposerView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:07:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 16 15:45:14 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerScene.h"
#include "dtkComposerView.h"

dtkComposerView::dtkComposerView(QWidget *parent) : QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setAcceptDrops(true);
}

dtkComposerView::~dtkComposerView(void)
{

}

void dtkComposerView::drawBackground(QPainter *painter, const QRectF& rect)
{
    QPixmap tile(128, 128);
    tile.fill(Qt::white);
    
    QPainter pt(&tile);
    pt.fillRect(0, 0, 64, 64, QColor(230, 230, 230));
    pt.fillRect(64, 64, 64, 64, QColor(230, 230, 230));
    pt.end();

    painter->drawTiledPixmap(rect, tile);
}

void dtkComposerView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void dtkComposerView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void dtkComposerView::dropEvent(QDropEvent *event)
{
    QUrl url = event->mimeData()->urls().first();

    if (url.scheme() != "type")
        return;

    if (dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene()))
        scene->addNode(url.path());
    
    event->acceptProposedAction();
}

void dtkComposerView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = pow((double)2, -event->delta() / 240.0);

    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < 0.07 || factor > 100)
        return;
    
    scale(scaleFactor, scaleFactor);
}
