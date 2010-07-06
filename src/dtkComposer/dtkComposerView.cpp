/* dtkComposerView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Sep  7 15:07:37 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jul  6 17:04:44 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 73
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNodeFactory.h"
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
    this->setBackgroundBrush(QColor(0x32, 0x32, 0x32));
    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setAcceptDrops(true);
}

dtkComposerView::~dtkComposerView(void)
{

}

void dtkComposerView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void dtkComposerView::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void dtkComposerView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void dtkComposerView::dropEvent(QDropEvent *event)
{
    QUrl url = event->mimeData()->urls().first();

    if (url.scheme() != "type") {
        event->ignore();
        return;
    }

    dtkComposerNode *node = dtkComposerNodeFactory::instance()->create(url.path());

    if (!node)
        qDebug() << "Unable to create node for type" << url.path();

    dtkComposerScene *scene = dynamic_cast<dtkComposerScene *>(this->scene());

    if (!scene)
        qDebug() << "Unable to retrieve composition scene";

    if (node)
        node->setPos(this->mapToScene(event->pos()));

    if (node && scene)
        scene->addNode(node);

    event->acceptProposedAction();
}

void dtkComposerView::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() & Qt::ShiftModifier)
        this->setDragMode(QGraphicsView::ScrollHandDrag);
}

void dtkComposerView::keyReleaseEvent(QKeyEvent *event)
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
}

void dtkComposerView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = pow((double)2, -event->delta() / 240.0);

    qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

    if (factor < 0.3 || factor > 100)
        return;
    
    scale(scaleFactor, scaleFactor);
}
