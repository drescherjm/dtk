/* dtkAnchoredBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 08:45:44 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 16 10:25:51 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAnchoredBar.h"

#include <dtkCore/dtkGlobal.h>

dtkAnchoredBar::dtkAnchoredBar(QWidget *parent) : QToolBar(parent)
{
    this->setMouseTracking(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setStyleSheet(dtkReadFile(":dtkGui/dtkAnchoredBar.qss"));
}

QSize dtkAnchoredBar::sizeHint(void) const
{
    return QSize(100, 23);
}

void dtkAnchoredBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->pos().x() > this->width() - 23)
        this->setCursor(Qt::SplitHCursor);
    else
        this->setCursor(Qt::ArrowCursor);

    if(!dragPosition.isNull())
        parentWidget()->setMaximumWidth(parentWidth + (event->pos().x() - dragPosition.x()));
}

void dtkAnchoredBar::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() > this->width() - 23) {
        parentHeight = parentWidget()->height();
        parentWidth = parentWidget()->width();
        dragPosition = event->pos();
    }
}

void dtkAnchoredBar::mouseReleaseEvent(QMouseEvent *event)
{
    dragPosition = QPoint();
}
