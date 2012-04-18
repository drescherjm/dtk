/* dtkComposerCompass.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 18 09:37:07 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 18 18:21:48 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 137
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
};

dtkComposerCompass::dtkComposerCompass(QWidget *parent) : QGraphicsView(parent), d(new dtkComposerCompassPrivate)
{
    d->view = NULL;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameStyle(QFrame::NoFrame);
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
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
    if (d->view
        && event->rect().width() > 20
        && event->rect().height() > 20
        && ( d->view->sceneRect().toRect().width() > event->rect().width()
          || d->view->sceneRect().toRect().height() > event->rect().height())) {

        this->fitInView(this->scene()->sceneRect(), Qt::KeepAspectRatio);
    }

    QGraphicsView::paintEvent(event);
}
