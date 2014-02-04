/* dtkComposerView.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:02:53
 * Version: $Id$
 * Last-Updated: Fri Apr 19 16:23:01 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 164
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerScene.h"
#include "dtkComposerSearchDialog.h"
#include "dtkComposerView.h"

class dtkComposerViewPrivate
{
public:
    dtkComposerSearchDialog *dialog;

public:
    QAction *search_action;
};

dtkComposerView::dtkComposerView(QWidget *parent) : QGraphicsView(parent), d(new dtkComposerViewPrivate)
{
    d->search_action = new QAction("Find node", this);
    d->search_action->setShortcut(QKeySequence::Find);

    d->dialog = NULL;

    this->setAcceptDrops(true);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setBackgroundBrush(QColor(0x55, 0x55, 0x55));
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setFrameStyle(QFrame::NoFrame);
    this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    this->setRubberBandSelectionMode(Qt::IntersectsItemShape);

    connect(d->search_action, SIGNAL(triggered()), this, SLOT(search()));
}

dtkComposerView::~dtkComposerView(void)
{
    delete d;
}

QAction *dtkComposerView::searchAction(void)
{
    return d->search_action;
}

void dtkComposerView::search(void)
{
    if(!d->dialog)
        d->dialog = new dtkComposerSearchDialog(this);

    d->dialog->setScene(dynamic_cast<dtkComposerScene *>(this->scene()));
    d->dialog->show();
}

void dtkComposerView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void dtkComposerView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO;

    QGraphicsView::mouseMoveEvent(event);
    
    event->accept();
}

void dtkComposerView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO;

    QGraphicsView::mousePressEvent(event);

    event->accept();
}

void dtkComposerView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO;

    QGraphicsView::mouseReleaseEvent(event);
}

#ifndef QT_NO_WHEELEVENT
void dtkComposerView::wheelEvent( QWheelEvent * event )
{
    if (event->modifiers().testFlag(Qt::ControlModifier)){ //zoom only when CTRL key pressed
        qreal scaleFactor = pow((double)2, event->delta() / 500.0);

        qreal factor = this->matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();

        if (factor < 0.1 || factor > 1.0)
            return;

        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        this->scale(scaleFactor, scaleFactor);
    } else {
        QGraphicsView::wheelEvent(event);
    }
}
#endif

void dtkComposerView::scroll(int dx, int dy)
{
    this->centerOn(this->mapToScene(this->viewport()->rect().center()) + QPointF(dx, dy));
}

void dtkComposerView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);

    emit scrolled();
}
