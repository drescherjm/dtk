/* dtkComposerCompass.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 18 09:37:07 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 18 22:34:19 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 170
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
    QRect s_rect;
    QRect t_rect;
};

dtkComposerCompass::dtkComposerCompass(QWidget *parent) : QGraphicsView(parent), d(new dtkComposerCompassPrivate)
{
    d->view = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
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
}
