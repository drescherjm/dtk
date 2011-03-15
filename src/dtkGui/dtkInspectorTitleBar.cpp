/* dtkInspectorTitleBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Feb 13 21:14:07 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 14 14:49:02 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 57
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkInspectorButton.h"
#include "dtkInspectorTitleBar.h"

#include <QtGui>

class dtkInspectorTitleBarPrivate
{
public:
    dtkInspectorButton *button;

public:
    QPixmap pixmap;
    QString title;
};

dtkInspectorTitleBar::dtkInspectorTitleBar(QWidget *parent) : QWidget(parent), d(new dtkInspectorTitleBarPrivate)
{
    d->button = new dtkInspectorButton(this);

    d->pixmap = QPixmap(":dtkGui/pixmaps/dtkInspectorTitleBar-bg.png");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft);
    layout->setContentsMargins(6, 0, 0, 0);
    layout->addWidget(d->button);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(d->button, SIGNAL(clicked()), this, SIGNAL(closed()));
}

dtkInspectorTitleBar::~dtkInspectorTitleBar(void)
{
    delete d;

    d = NULL;
}

QSize dtkInspectorTitleBar::sizeHint(void) const
{
    return QSize(100, 22);
}

void dtkInspectorTitleBar::setTitle(const QString& title)
{
    d->title = title;
}

void dtkInspectorTitleBar::paintEvent(QPaintEvent *event)
{
    QRect rect = QRect(event->rect().x(), event->rect().y(), event->rect().width(), d->pixmap.height());

    QPainter painter(this);
    painter.fillRect(event->rect(), QColor("#1b1b1b"));
    painter.drawTiledPixmap(rect, d->pixmap);

    QFont font = painter.font();
#if defined(Q_WS_MAC)
    font.setPointSize(11);
#else
    font.setPointSize(9);
#endif

    QFontMetrics metrics(font);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText((event->rect().right()-event->rect().left())/2 - metrics.width(d->title)/2, metrics.height() + 3, d->title);
    painter.setPen("#bbbbbb");
    painter.drawText((event->rect().right()-event->rect().left())/2 - metrics.width(d->title)/2, metrics.height() + 2, d->title);

    QWidget::paintEvent(event);
}
