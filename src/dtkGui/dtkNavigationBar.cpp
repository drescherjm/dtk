/* dtkNavigationBar.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb  4 18:28:35 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb  5 09:12:07 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 58
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkNavigationBar.h"

// /////////////////////////////////////////////////////////////////
// dtkNavigationBarButton
// /////////////////////////////////////////////////////////////////

class dtkNavigationBarButtonPrivate
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

dtkNavigationBarButton::dtkNavigationBarButton(QWidget *parent): QAbstractButton(parent), d(new dtkNavigationBarButtonPrivate)
{
    this->setRadius(10);
}

dtkNavigationBarButton::dtkNavigationBarButton(const QString& text, QWidget *parent) : QAbstractButton(parent), d(new dtkNavigationBarButtonPrivate)
{
    this->setRadius(10);
    this->setText(text);
}

dtkNavigationBarButton::~dtkNavigationBarButton(void)
{
    delete d;
}

void dtkNavigationBarButton::setRadius(qreal radius)
{
    d->leftTopRadius = radius;
    d->leftBottomRadius = radius;
    d->rightTopRadius = radius;
    d->rightBottomRadius = radius;
}

void dtkNavigationBarButton::setRadius(qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius)
{
    d->leftTopRadius = leftTopRadius;
    d->leftBottomRadius = leftBottomRadius;
    d->rightTopRadius = rightTopRadius;
    d->rightBottomRadius = rightBottomRadius;
}

QSize dtkNavigationBarButton::minimumSizeHint(void) const
{
    QFontMetrics fontMetrics(QFont("Arial", 8, QFont::Bold));

    int width = fontMetrics.width(text()) + 28;

    return QSize(width, 22);
}

void dtkNavigationBarButton::paintEvent(QPaintEvent *event)
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
    p.translate(qMax(d->leftBottomRadius, d->leftTopRadius), 0);
    d->fillRoundRect(&p, QRect(0, 0, width, mh), d->leftTopRadius, 0, d->rightTopRadius, 0, QBrush(linearGrad));
    d->fillRoundRect(&p, QRect(0, mh, width, mh), 0, d->leftBottomRadius, 0, d->rightBottomRadius, color);
    d->drawRoundRect(&p, QRect(0, 0, width, height), d->leftTopRadius, d->leftBottomRadius, d->rightTopRadius, d->rightBottomRadius);
    p.translate(-1*qMax(d->rightBottomRadius, d->rightTopRadius), 0);
    p.setFont(QFont("Arial", 9, QFont::Bold));

    if(this->isEnabled())
        p.setPen(QPen(Qt::white, 1));
    else
        p.setPen(QPen(Qt::gray, 1));

    p.drawText(event->rect(), Qt::AlignCenter, text());
    p.end();
}


// /////////////////////////////////////////////////////////////////
// dtkNavigationBar
// /////////////////////////////////////////////////////////////////

class dtkNavigationBarPrivate
{
public:
    dtkNavigationBarButton *backwardButton;
    dtkNavigationBarButton *forwardButton;
};

dtkNavigationBar::dtkNavigationBar(QWidget *parent) : QWidget(parent), d(new dtkNavigationBarPrivate)
{
    d->backwardButton = new dtkNavigationBarButton("Backward", this);
    d->backwardButton->setRadius(5, 5, 0, 0);
    
    d->forwardButton = new dtkNavigationBarButton("Forward", this);
    d->forwardButton->setRadius(0, 0, 5, 5);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 5, 0, 5);
    layout->setSpacing(0);
    layout->addWidget(d->backwardButton);
    layout->addWidget(d->forwardButton);
}

dtkNavigationBar::~dtkNavigationBar(void)
{
    delete d;

    d = NULL;
}

QSize dtkNavigationBar::sizeHint(void) const
{
    return d->backwardButton->sizeHint() + d->forwardButton->sizeHint();
}

QAbstractButton *dtkNavigationBar::backwardButton(void)
{
    return d->backwardButton;
}

QAbstractButton *dtkNavigationBar::forwardButton(void)
{
    return d->forwardButton;
}
