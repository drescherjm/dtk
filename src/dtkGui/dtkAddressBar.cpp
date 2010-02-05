/* dtkAddressBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb  4 11:07:43 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  5 09:14:22 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAddressBar.h"

// /////////////////////////////////////////////////////////////////
// dtkAddressBarButton
// /////////////////////////////////////////////////////////////////

class dtkAddressBarButtonPrivate
{
public:
    void drawRoundRect(QPainter *painter, const QRectF& rect, qreal radius)
    {
        painter->drawPath(roundRectangle(rect, radius, radius, radius, radius));
    }
    
    void drawRoundRect(QPainter *painter, const QRectF& rect, qreal leftRadius, qreal rightRadius) 
    {
        painter->drawPath(roundRectangle(rect, leftRadius, leftRadius, rightRadius, rightRadius));
    }
    
    void drawRoundRect(QPainter *painter, const QRectF& rect, qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius)
    {
        painter->drawPath(roundRectangle(rect, leftTopRadius, leftBottomRadius, rightTopRadius, rightBottomRadius));
    }
    
    void fillRoundRect(QPainter *painter, const QRectF& rect, qreal radius, const QBrush& brush)
    {
        painter->fillPath(roundRectangle(rect, radius, radius, radius, radius), brush);
    }
    
    void fillRoundRect(QPainter *painter, const QRectF& rect, qreal leftRadius, qreal rightRadius, const QBrush& brush)
    {
        painter->fillPath(roundRectangle(rect, leftRadius, leftRadius, rightRadius, rightRadius), brush);
    }
    
    void fillRoundRect(QPainter *painter, const QRectF& rect, qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius, const QBrush& brush)
    {
        painter->fillPath(roundRectangle(rect, leftTopRadius, leftBottomRadius, rightTopRadius, rightBottomRadius), brush);
    }
    
    QPainterPath roundRectangle(const QRectF& rect, qreal radius)
    {
	return roundRectangle(rect, radius, radius, radius, radius);
    }
    
    QPainterPath roundRectangle(const QRectF& rect, qreal leftRadius, qreal rightRadius)
    {
        return roundRectangle(rect, leftRadius, leftRadius, rightRadius, rightRadius);
    }
    
    QPainterPath roundRectangle(const QRectF& rect, qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius)
    {
        QPainterPath path(QPoint(rect.left(), rect.top() + leftTopRadius));
        path.quadTo(rect.left(), rect.top(), rect.left() + leftTopRadius, rect.top());
        path.lineTo(rect.right() - rightTopRadius, rect.top());
        path.quadTo(rect.right(), rect.top(), rect.right(), rect.top() + rightTopRadius);
        path.lineTo(rect.right(), rect.bottom() - rightBottomRadius);
        path.quadTo(rect.right(), rect.bottom(), rect.right() - rightBottomRadius, rect.bottom());
        path.lineTo(rect.left() + leftBottomRadius, rect.bottom());
        path.quadTo(rect.left(), rect.bottom(), rect.left(), rect.bottom() - leftBottomRadius);
        path.closeSubpath();
        
        return path;
    }
    
public:
    qreal leftTopRadius;
    qreal leftBottomRadius;
    qreal rightTopRadius;
    qreal rightBottomRadius;
};

dtkAddressBarButton::dtkAddressBarButton(QWidget *parent): QAbstractButton(parent), d(new dtkAddressBarButtonPrivate)
{
    this->setRadius(10);
}

dtkAddressBarButton::dtkAddressBarButton(const QString& text, QWidget *parent) : QAbstractButton(parent), d(new dtkAddressBarButtonPrivate)
{
    this->setRadius(10);
    this->setText(text);
}

dtkAddressBarButton::~dtkAddressBarButton(void)
{
    delete d;
}

void dtkAddressBarButton::setRadius(qreal radius)
{
    d->leftTopRadius = radius;
    d->leftBottomRadius = radius;
    d->rightTopRadius = radius;
    d->rightBottomRadius = radius;
}

void dtkAddressBarButton::setRadius(qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius)
{
    d->leftTopRadius = leftTopRadius;
    d->leftBottomRadius = leftBottomRadius;
    d->rightTopRadius = rightTopRadius;
    d->rightBottomRadius = rightBottomRadius;
}

QSize dtkAddressBarButton::minimumSizeHint(void) const
{
    QFontMetrics fontMetrics(QFont("Arial", 8, QFont::Bold));

    int width = fontMetrics.width(text()) + 48;

    return QSize(width, 22);
}

void dtkAddressBarButton::paintEvent(QPaintEvent *event)
{
    int height = event->rect().height();
    int width = event->rect().width();
    int mh = (height / 2);
        
    QLinearGradient linearGrad;
    QColor color;

    if (isDown()) {
        linearGrad = QLinearGradient(QPointF(0, 0), QPointF(0, mh));
        linearGrad.setColorAt(0, QColor("#8c95ad").darker(120));
        linearGrad.setColorAt(1, QColor("#818aa2").darker(120));
        color = QColor("#5d6984").darker(120);
    } else {
        linearGrad = QLinearGradient(QPointF(0, 0), QPointF(0, mh));
        linearGrad.setColorAt(0, QColor("#8c95ad"));
        linearGrad.setColorAt(1, QColor("#818aa2"));
        color = QColor("#5d6984");
    }
    
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing);
    p.setPen(QPen(QColor("#374262"), 1));
    p.translate(5, 0);
    d->fillRoundRect(&p, QRect(0, 0, width, mh), d->leftTopRadius, 0, d->rightTopRadius, 0, QBrush(linearGrad));
    d->fillRoundRect(&p, QRect(0, mh, width, mh), 0, d->leftBottomRadius, 0, d->rightBottomRadius, color);
    d->drawRoundRect(&p, QRect(0, 0, width, height), d->leftTopRadius, d->leftBottomRadius, d->rightTopRadius, d->rightBottomRadius);
    p.translate(-5, 0);
    p.setFont(QFont("Arial", 9, QFont::Bold));
    p.setPen(QPen(QColor(0xff, 0xff, 0xff), 1));
    p.drawText(event->rect(), Qt::AlignCenter, text());
    p.end();
}

// /////////////////////////////////////////////////////////////////
// dtkAddressBar
// /////////////////////////////////////////////////////////////////

class dtkAddressBarPrivate
{
public:
    dtkAddressBarButton *button;
    QLineEdit *edit;
};

dtkAddressBar::dtkAddressBar(QWidget *parent) : QWidget(parent), d(new dtkAddressBarPrivate)
{
    d->button = new dtkAddressBarButton("Address:", this);
    d->button->setRadius(5, 5, 0, 0);

    d->edit = new QLineEdit(this);
    d->edit->setAttribute(Qt::WA_MacShowFocusRect, false);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 5, 0, 5);
    layout->setSpacing(0);
    layout->addWidget(d->button);
    layout->addWidget(d->edit);
}

dtkAddressBar::~dtkAddressBar(void)
{
    delete d;

    d = NULL;
}

QSize dtkAddressBar::sizeHint(void) const
{
    return d->button->sizeHint() + d->edit->sizeHint();
}

QSizePolicy dtkAddressBar::sizePolicy(void) const
{
    return QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void dtkAddressBar::setText(const QString& text)
{
    d->edit->setText(text);
}
