/* dtkInspectorSwitch.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb  4 17:35:45 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 14:54:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 9
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspectorSwitch.h"

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

class dtkInspectorSwitchPrivate
{
public:
    QPixmap pixmap;

    bool toggled;
};

dtkInspectorSwitch::dtkInspectorSwitch(QWidget *parent) : QWidget(parent), d(new dtkInspectorSwitchPrivate)
{
    d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorSwitch-off.png");

    d->toggled = false;

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

dtkInspectorSwitch::~dtkInspectorSwitch(void)
{
    delete d;

    d = NULL;
}

QSize dtkInspectorSwitch::sizeHint(void) const
{
    return d->pixmap.size();
}

void dtkInspectorSwitch::mousePressEvent(QMouseEvent *event)
{
    d->toggled = !d->toggled;

    if(d->toggled)
        d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorSwitch-on.png");
    else
        d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorSwitch-off.png");

    this->update();

    emit toggled(d->toggled);
}

void dtkInspectorSwitch::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(event->rect(), d->pixmap);
}
