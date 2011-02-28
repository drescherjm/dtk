/* dtkComposerNote.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 26 20:21:10 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 27 17:32:39 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 129
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerNote.h"

class dtkComposerNotePrivate
{
public:
    QPointF drag_point;

public:
    QRectF bounding_rect;

public:
    QGraphicsTextItem *text;
};

dtkComposerNote::dtkComposerNote(dtkComposerNode *parent) : QObject(parent), QGraphicsItem(parent), d(new dtkComposerNotePrivate)
{
    d->bounding_rect = QRectF(-100, -100, 200, 200);

    d->text = new QGraphicsTextItem("Note", this);
    d->text->setPos(-100, -100);
    d->text->setTextInteractionFlags(Qt::TextEditorInteraction);
    d->text->setTextWidth(200);

    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

#if QT_VERSION >= 0x040600
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(5);
    shadow->setOffset(3);
    shadow->setColor(QColor(0, 0, 0, 127));
    this->setGraphicsEffect(shadow);
#endif
}

dtkComposerNote::~dtkComposerNote(void)
{
    delete d;

    d = NULL;
}

QString dtkComposerNote::text(void) const
{
    return d->text->toPlainText();
}

void dtkComposerNote::setSize(const QSizeF& size)
{
    d->bounding_rect.setHeight(size.height());
    d->bounding_rect.setWidth(size.width());

    d->text->setTextWidth(size.width());
}

void dtkComposerNote::setText(const QString& text)
{
    d->text->setPlainText(text);
}

QRectF dtkComposerNote::boundingRect(void) const
{
    return d->bounding_rect;
}

void dtkComposerNote::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->fillRect(option->rect, QColor(Qt::yellow).darker());

    painter->fillRect(this->mapRectFromItem(d->text, d->text->boundingRect()), QColor(Qt::yellow));

    // Drawing size grip

    QPainterPath path;
    path.moveTo(d->bounding_rect.bottomRight());
    path.lineTo(d->bounding_rect.bottomRight() + QPointF(-12, 0));
    path.lineTo(d->bounding_rect.bottomRight() + QPointF(0, -12));
    path.lineTo(d->bounding_rect.bottomRight());

    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#ffff88"));
    painter->drawPath(path);

    if(this->isSelected()) {
        QPen pen;
        pen.setColor(Qt::magenta);
        pen.setWidth(2);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(option->rect);
    }
}

void dtkComposerNote::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && !d->drag_point.isNull()) {
        
        QPointF delta = QPointF(event->scenePos() - d->drag_point);

        d->bounding_rect.setBottomRight(d->bounding_rect.bottomRight() + delta);
        d->text->setTextWidth(d->bounding_rect.width());

        d->drag_point = event->scenePos();

        event->accept();

        this->update();

    } else {

        QGraphicsItem::mouseMoveEvent(event);
    }
}

void dtkComposerNote::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF br = d->bounding_rect.bottomRight();

    QRectF corner(br.x() - 16, br.y() - 16, 16, 16);

    if (event->button() & Qt::LeftButton && corner.contains(event->pos())) {
        d->drag_point = event->scenePos();
        event->accept();
    }

    QGraphicsItem::mousePressEvent(event);
}

void dtkComposerNote::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() & Qt::LeftButton && !d->drag_point.isNull()) {
        d->drag_point = QPointF(0, 0);
        event->accept();
    }

    QGraphicsItem::mouseReleaseEvent(event);
}
