/* dtkAnchoredBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 16 08:45:44 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Jun 12 16:13:58 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAnchoredBar.h"

#include <dtkCore/dtkGlobal.h>

class dtkAnchoredBarPrivate
{
public:
    QPoint dragPosition;
    int parentHeight;
    int parentWidth;
};

dtkAnchoredBar::dtkAnchoredBar(QWidget *parent) : QToolBar(parent), d(new dtkAnchoredBarPrivate)
{
    this->setMouseTracking(true);
    this->setFixedHeight(23);
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

    if(!d->dragPosition.isNull())
        parentWidget()->setMaximumWidth(d->parentWidth + (event->pos().x() - d->dragPosition.x()));
}

void dtkAnchoredBar::mousePressEvent(QMouseEvent *event)
{
    if(event->pos().x() > this->width() - 23) {
        d->parentHeight = parentWidget()->height();
        d->parentWidth = parentWidget()->width();
        d->dragPosition = event->pos();
    }
}

void dtkAnchoredBar::mouseReleaseEvent(QMouseEvent *event)
{
    d->dragPosition = QPoint();
}
