/* dtkUiItemDelegate.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jun 12 19:08:11 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep  9 13:59:05 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 54
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QDebug>
#include <QPainter>

#include "dtkUiItemDelegate.h"
#include "dtkUiItem.h"

static QPainterPath roundRectangle(const QRectF& rect, qreal leftTopRadius, qreal leftBottomRadius, qreal rightTopRadius, qreal rightBottomRadius)
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
    
    return(path);
}

dtkUiItemDelegate::dtkUiItemDelegate (QObject *parent) : QItemDelegate(parent)
{

}

dtkUiItemDelegate::~dtkUiItemDelegate(void)
{

}

void dtkUiItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    painter->save();
    
    painter->setRenderHint(QPainter::Antialiasing);
    
    QString keyName = index.data(Qt::DisplayRole).toString();
    QIcon keyIcon = qVariantValue<QIcon>(index.data(Qt::DecorationRole));
    int itemType = index.data(Qt::UserRole + 2).toInt();
    QVariant keyValue = index.data(Qt::UserRole + 1);
    
    int h = option.rect.height();
    int w = option.rect.width() - 10;
    int x = option.rect.x() + 5;
    int y = option.rect.y();
    
    if (itemType == dtkUiItem::Group) {
        painter->setPen(QColor(0x61, 0x6a, 0x7e));
        painter->setFont(QFont(painter->font().family(), 12, QFont::Bold));
        painter->drawText(x + 15, y, w - 30, h - 5, Qt::AlignLeft | Qt::AlignBottom, keyName);
    } else if (itemType == dtkUiItem::Info) {
        painter->setPen(QColor(0x61, 0x6a, 0x7e));
        painter->setFont(QFont(painter->font().family(), 12, QFont::Light));
        painter->drawText(x + 15, y, w - 30, h, Qt::AlignCenter, keyName);
    } else {
        painter->setPen(QColor(0xb8, 0xb9, 0xbc));
        
        if (option.state & QStyle::State_Selected)
            painter->setBrush(QColor(0xb0, 0xc0, 0xf2));
        else
            painter->setBrush(Qt::white);
        
        if (index.model()->rowCount(index.parent()) == 1)
            painter->drawPath(roundRectangle(QRectF(x, y - 1, w, h + 1), 10, 10, 10, 10));
        else if (index.row() == 0)
            painter->drawPath(roundRectangle(QRectF(x, y, w, h), 10, 0, 10, 0));
        else if (index.row() == (index.model()->rowCount(index.parent()) - 1))
            painter->drawPath(roundRectangle(QRectF(x, y - 1, w, h + 1), 0, 10, 0, 10));
        else
            painter->drawRect(x, y - 1, w, h + 1);
        
        x += 15; w -= 10;
        
        if (!keyIcon.isNull()) {
            painter->drawPixmap(x, y + 4, h - 8, h - 8, keyIcon.pixmap(h - 8));
            x += h; w -= h;
        }
        
        int keyAlign = Qt::AlignLeft | Qt::AlignVCenter;
        if (itemType == dtkUiItem::Button)
            keyAlign = Qt::AlignCenter;
        
        painter->setPen(Qt::black);
        painter->setFont(QFont(painter->font().family(), 12, QFont::DemiBold));
        painter->drawText(x, y, w, h, keyAlign, keyName);
        
        if (itemType != dtkUiItem::Button)
            drawValue(painter, x, y, w, h, itemType, keyValue);
    }
    
    painter->restore();
}

QSize dtkUiItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);
        
    QString keyName = index.data(Qt::DisplayRole).toString();

    if (index.parent() == QModelIndex())
        return(QSize(30, keyName.isEmpty() ? 20 : 40));

    return(QSize(30, 30));
}

void dtkUiItemDelegate::drawValue(QPainter *painter, int x, int y, int w, int h, int itemType, QVariant& value) const
{
    if (itemType == dtkUiItem::Link) {
        drawLinkValue(painter, y, w, h);
    } else if (value.type() == QVariant::Bool) {
        drawBoolValue(painter, y + 6, w, h - 12, value.toBool());
    } else if (qVariantCanConvert<QString>(value)) {
        drawStringValue(painter, y, w - 18, h, value.toString());
        
        if (itemType == dtkUiItem::MultiValue)
            drawLinkValue(painter, y, w, h);
    }
}

void dtkUiItemDelegate::drawBoolValue(QPainter *painter, int y, int w, int h, bool value) const
{
    painter->save();

    int rectWidth = 60;
    int rectPart = 30;
    int x1 = (w - rectWidth);
    int x2 = (w - rectPart);

    QLinearGradient blueGradient(x1, y, x1, y + h);
    blueGradient.setColorAt(0.0, QColor(0x23, 0x4e, 0x97));
    blueGradient.setColorAt(0.5, QColor(0x66, 0x9b, 0xeb));
    blueGradient.setColorAt(0.6, QColor(0x72, 0xa4, 0xee));
    blueGradient.setColorAt(1.0, QColor(0x96, 0xbd, 0xf9));
    
    QLinearGradient grayGradient(x2, y, x2, y + h);
    grayGradient.setColorAt(0.0, QColor(0xd6, 0xd6, 0xd6));
    grayGradient.setColorAt(0.5, QColor(0xe9, 0xe9, 0xe9));
    grayGradient.setColorAt(0.6, QColor(0xeb, 0xeb, 0xeb));
    grayGradient.setColorAt(1.0, QColor(0xfc, 0xfc, 0xfc));

    QPainterPath pathL = roundRectangle(QRectF(x1, y, rectPart, h), 6, 6, 0, 0);
    QPainterPath pathR = roundRectangle(QRectF(x2, y, rectPart, h), 0, 0, 6, 6);
    
    painter->setPen(QColor(0xa2, 0xa2, 0xa2));
    painter->setBrush(blueGradient);
    painter->drawPath(value ? pathL : pathR);
    
    painter->setBrush(grayGradient);
    painter->drawPath(value ? pathR : pathL);
    
    painter->setPen(Qt::white);
    painter->setFont(QFont(painter->font().family(), 11, QFont::Bold));
    painter->drawText(value ? x1 : x2, y, rectPart, h, Qt::AlignCenter, value ? tr("ON") : tr("OFF"));
    
    painter->restore();
}

void dtkUiItemDelegate::drawStringValue(QPainter *painter, int y, int w, int h,	const QString& value) const
{
    painter->save();
    
    painter->setPen(QColor(0x4a, 0x64, 0x94));
    painter->setFont(QFont(painter->font().family(), 12, QFont::Bold));
    
    painter->drawText(0, y, w, h, Qt::AlignRight | Qt::AlignVCenter, value);
    
    painter->restore();
}

void dtkUiItemDelegate::drawLinkValue(QPainter *painter, int y, int w, int h) const
{
    painter->save();
    
    int x = w - 8;
    int ya = y + (h / 2) - 4;
    
    painter->setPen(QPen(QColor(0x91, 0x91, 0x91), 2));
    painter->drawLine(x, ya, x + 5, ya + 4);
    painter->drawLine(x, ya + 8, x + 5, ya + 4);
    
    painter->restore();
}
