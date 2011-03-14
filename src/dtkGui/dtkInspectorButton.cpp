/* dtkInspectorButton.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 13 21:36:50 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 14:53:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspectorButton.h"

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

class dtkInspectorButtonPrivate
{
public:
    QPixmap pixmap;

    bool toggled;
};

dtkInspectorButton::dtkInspectorButton(QWidget *parent) : QWidget(parent), d(new dtkInspectorButtonPrivate)
{
    d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorButton-close-hover.png");

    d->toggled = false;

    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

dtkInspectorButton::~dtkInspectorButton(void)
{
    delete d;

    d = NULL;
}

QSize dtkInspectorButton::sizeHint(void) const
{
    return d->pixmap.size();
}

void dtkInspectorButton::mousePressEvent(QMouseEvent *event)
{
    d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorButton-close-pressed.png");

    this->update();
}

void dtkInspectorButton::mouseReleaseEvent(QMouseEvent *event)
{
    d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorButton-close-hover.png");

    this->update();

    emit clicked();
}

void dtkInspectorButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(event->rect(), d->pixmap);
}
