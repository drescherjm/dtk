/* dtkComposerCompass.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 18 09:37:07 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 19 00:02:50 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 264
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerCompass.h"
#include "dtkComposerView.h"

class dtkComposerCompassPrivate
{
public:
    dtkComposerView *view;

public:
    QRect c_rect; // crop
    QRect s_rect; // source
    QRect t_rect; // target

public:
    QPoint pos;
};

dtkComposerCompass::dtkComposerCompass(QWidget *parent) : QGraphicsView(parent), d(new dtkComposerCompassPrivate)
{
    d->view = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setBackgroundBrush(QColor(0xc5, 0xc5, 0xc5));
    this->setFrameStyle(QFrame::NoFrame);
    this->setInteractive(false);
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

dtkComposerCompass::~dtkComposerCompass(void)
{
    delete d;

    d = NULL;
}

void dtkComposerCompass::setView(dtkComposerView *view)
{
    d->view = view;
}

#define CROP_BORDER_LINE 10
#define CROP_GRID_SIZE    3

void dtkComposerCompass::paintEvent(QPaintEvent *event)
{
    if(!d->view)
        return;

    if(event->rect().width() < 20 || event->rect().height() < 20)
        return;

    bool fit = false;

    if (d->s_rect != d->view->sceneRect().toRect()) {
        d->s_rect  = d->view->sceneRect().toRect();
        fit = true;
    }

    if (d->t_rect != event->rect()) {
        d->t_rect  = event->rect();
        fit = true;
    }

    if(fit && (d->s_rect.width() > d->t_rect.width() || d->s_rect.height() > d->t_rect.height()))
        this->fitInView(this->scene()->sceneRect(), Qt::KeepAspectRatio);

    QGraphicsView::paintEvent(event);
    
    // -- Drawing grid

    if (d->c_rect.isNull())
        d->c_rect = QRect(20, 20, 100, 70);

    // --

    QPainterPath cropPath;
    cropPath.addRect(d->c_rect);
    
    QPainterPath windowPath;
    windowPath.addRect(d->t_rect);
    windowPath -= cropPath;

    QPainter painter(this->viewport());
    painter.setRenderHints(QPainter::Antialiasing);
    
    // Draw Alpha-Black Background.
    painter.fillPath(windowPath, QColor(0x83, 0x83, 0x83, 0x77));
    
    // Draw Crop Rect
    painter.setPen(QPen(QColor(0xdd, 0xdd, 0xdd), 1));
    painter.drawPath(cropPath);

    // --

    int topRightX = d->c_rect.x() + d->c_rect.width();
    int bottomY = d->c_rect.y() + d->c_rect.height();

    qreal f = 1.0f / CROP_GRID_SIZE;
    qreal hsize = d->c_rect.height() * f;
    qreal wsize = d->c_rect.width() * f;
    
    QPainterPath gridPath;
    for (uint i = 1; i < CROP_GRID_SIZE; ++i) {
        qreal y = d->c_rect.y() + i * hsize;
        gridPath.moveTo(d->c_rect.x(), y);
        gridPath.lineTo(topRightX, y);
        
        for (uint j = 1; j < CROP_GRID_SIZE; ++j) {
            qreal x = d->c_rect.x() + j * wsize;
            gridPath.moveTo(x, d->c_rect.y());
            gridPath.lineTo(x, bottomY);
        }
    }
    
    // Draw Grid Path
    painter.setPen(QPen(QColor(0x99, 0x99, 0x99, 0x80), 1));
    painter.drawPath(gridPath);

    // --

    QPainterPath borderPath;

    // Top-Left Corner
    borderPath.moveTo(d->c_rect.x(), d->c_rect.y());
    borderPath.lineTo(d->c_rect.x() + CROP_BORDER_LINE, d->c_rect.y());
    borderPath.moveTo(d->c_rect.x(), d->c_rect.y());
    borderPath.lineTo(d->c_rect.x(), d->c_rect.y() + CROP_BORDER_LINE);
    
    // Top-Right Corner
    borderPath.moveTo(topRightX - CROP_BORDER_LINE, d->c_rect.y());
    borderPath.lineTo(topRightX, d->c_rect.y());
    borderPath.moveTo(topRightX, d->c_rect.y());
    borderPath.lineTo(topRightX, d->c_rect.y() + CROP_BORDER_LINE);
    
    // Bottom-Left Corner
    borderPath.moveTo(d->c_rect.x(), bottomY);
    borderPath.lineTo(d->c_rect.x() + CROP_BORDER_LINE, bottomY);
    borderPath.moveTo(d->c_rect.x(), bottomY - CROP_BORDER_LINE);
    borderPath.lineTo(d->c_rect.x(), bottomY);
    
    // Bottom-Left Corner
    borderPath.moveTo(topRightX, bottomY);
    borderPath.lineTo(topRightX - CROP_BORDER_LINE, bottomY);
    borderPath.moveTo(topRightX, bottomY - CROP_BORDER_LINE);
    borderPath.lineTo(topRightX, bottomY);
    
    // Draw Border Path    
    painter.setPen(QPen(QColor(0xee, 0xee, 0xee), 3));
    painter.drawPath(borderPath);
}

void dtkComposerCompass::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void dtkComposerCompass::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {

        QPoint delta = event->pos() - d->pos;
        
        if(!d->s_rect.isNull())
            d->c_rect.translate(delta);

        this->update();
    }

    d->pos = event->pos();
}

void dtkComposerCompass::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
