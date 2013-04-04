/* dtk3DQuickItem.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 14:57:36 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 11:31:20 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 69
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickItem.h"

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGraphicsScale3D>
#include <Qt3D/QGLSceneNode>
#include <Qt3D/QGLSphere>

class dtk3DQuickItemPrivate
{
public:
    dtk3DItem *item;
};

dtk3DQuickItem::dtk3DQuickItem(QObject *parent) : QObject(parent), d(new dtk3DQuickItemPrivate)
{
    QGLBuilder builder;
    builder << QGL::Faceted;
    builder << QGLSphere();

    QGraphicsScale3D *transform = new QGraphicsScale3D;
    transform->setScale(QVector3D(0.5, 0.5, 0.5));

    QGLSceneNode *node = builder.finalizedSceneNode();
    node->setObjectName("node");
    node->addTransform(transform);

    d->item = new dtk3DItem;
    d->item->addNode(node);
    d->item->setEffect(QGL::LitMaterial);
    d->item->setColor(Qt::green);
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

void dtk3DQuickItem::translate(qreal dx, qreal dy, qreal dz)
{
    qDebug() << Q_FUNC_INFO;

    d->item->translate(QVector3D(dx, dy, dz));
}
