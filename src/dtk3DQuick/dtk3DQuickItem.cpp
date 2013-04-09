/* dtk3DQuickItem.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 14:57:36 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  9 00:46:51 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 78
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickItem.h"

class dtk3DQuickItemPrivate
{
public:
    dtk3DItem *item;
};

dtk3DQuickItem::dtk3DQuickItem(QObject *parent) : QObject(parent), d(new dtk3DQuickItemPrivate)
{
    d->item = new dtk3DItem;
}

dtk3DQuickItem::~dtk3DQuickItem(void)
{
    delete d;
}

dtk3DItem *dtk3DQuickItem::item(void)
{
    return d->item;
}

QColor dtk3DQuickItem::color(void)
{
    return d->item->color();
}

qreal dtk3DQuickItem::x(void)
{
    return d->item->localPosition().x();
}

qreal dtk3DQuickItem::y(void)
{
    return d->item->localPosition().y();
}

qreal dtk3DQuickItem::z(void)
{
    return d->item->localPosition().z();
}

bool dtk3DQuickItem::wireframe(void)
{
    return d->item->flags() & dtk3DItem::Wireframe;
}

void dtk3DQuickItem::setColor(const QColor& color)
{
    d->item->setColor(color);
}

void dtk3DQuickItem::setX(qreal x)
{
    d->item->translate(QVector3D(x, 0.0, 0.0));
}

void dtk3DQuickItem::setY(qreal y)
{
    d->item->translate(QVector3D(0.0, y, 0.0));
}

void dtk3DQuickItem::setZ(qreal z)
{
    d->item->translate(QVector3D(0.0, 0.0, z));
}

void dtk3DQuickItem::setWireframe(bool on)
{
    d->item->setFlag(dtk3DItem::Wireframe, on);
}

void dtk3DQuickItem::translate(qreal dx, qreal dy, qreal dz)
{
    d->item->translate(QVector3D(dx, dy, dz));
}
