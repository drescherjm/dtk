/* dtkComposerView.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:02:53
 * Version: $Id$
 * Last-Updated: Wed Mar 21 11:25:00 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerView.h"

class dtkComposerViewPrivate
{
public:

};

dtkComposerView::dtkComposerView(QWidget *parent) : QGraphicsView(parent), d(new dtkComposerViewPrivate)
{
    this->setAcceptDrops(true);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setBackgroundBrush(QColor(0x55, 0x55, 0x55));
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setFrameStyle(QFrame::NoFrame);
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    this->setRubberBandSelectionMode(Qt::IntersectsItemShape);
}

dtkComposerView::~dtkComposerView(void)
{

}
