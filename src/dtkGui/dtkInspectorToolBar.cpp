/* dtkInspectorToolBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 13 22:48:21 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr 20 13:04:14 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 115
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspectorToolBar.h"

#include <QtGui>

class dtkInspectorToolBarPrivate
{
public:
    QSizeGrip *grip;
    QPixmap pixmap;

public:
    QList<QPair<QAction *, QRect *> > actions;
};

dtkInspectorToolBar::dtkInspectorToolBar(QWidget *parent) : QWidget(parent), d(new dtkInspectorToolBarPrivate)
{
    d->grip = new QSizeGrip(this);
    d->grip->setFixedWidth(16);

    d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorToolBar-bg.png");

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

dtkInspectorToolBar::~dtkInspectorToolBar(void)
{
    delete d;

    d = NULL;
}

QSize dtkInspectorToolBar::sizeHint(void) const
{
    return QSize(100, 32);
}

void dtkInspectorToolBar::addAction(QAction *action)
{
    d->actions << qMakePair(action, new QRect);
}

void dtkInspectorToolBar::mouseReleaseEvent(QMouseEvent *event)
{
    typedef QPair<QAction *, QRect *> it;

    foreach(it action, d->actions)
        if(action.second->contains(event->pos()))
            action.first->trigger();

    this->update();
}

void dtkInspectorToolBar::paintEvent(QPaintEvent *event)
{
    int x = 5;
    int y = 5;

    QPainter painter(this);
    painter.drawTiledPixmap(event->rect(), d->pixmap);

    QFont font = painter.font();
#if defined(Q_WS_MAC)
    font.setPointSize(11);
#else
    font.setPointSize(9);
#endif

    QFontMetrics metrics(font);
    painter.setFont(font);

    typedef QPair<QAction *, QRect *> it;

    foreach(it action, d->actions) {

        painter.setPen(Qt::black);
        painter.drawText(event->rect().left() + x, metrics.height() + 3 + y, action.first->text());
        if(action.first->isEnabled())
            painter.setPen("#bbbbbb");
        else
            painter.setPen("#00a2fd");
        painter.drawText(event->rect().left() + x, metrics.height() + 2 + y, action.first->text());

        action.second->setRect(x, 0, metrics.width(action.first->text()), 32);

        x += metrics.width(action.first->text()) + 10;
    }
}

void dtkInspectorToolBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    
    d->grip->move(this->width()-d->grip->width(), this->height()-d->grip->height());
}
