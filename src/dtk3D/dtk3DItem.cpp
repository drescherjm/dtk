/* dtk3DItem.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 12:24:34 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 17:35:18 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 141
 */

/* Change Log:
 * 
 */

#include "dtk3DItem.h"

#include <QtGui>

class dtk3DItemPrivate
{
public:
    QVector3D position;
    QVector3D orientation;
    qreal     orientation_angle;
    qreal     scale;
    int       id;

public:
    QGLSceneNode *node;

public:
    QGLAbstractEffect   *effect;
    QGLMaterial       *material;
    QGLMaterial *hover_material;

public:
    bool hovering;
};

dtk3DItem::dtk3DItem(QObject *parent) : QObject(parent), d(new dtk3DItemPrivate)
{
    d->id = -1;
    d->scale = 1.0;
    d->node = NULL;
    d->effect = NULL;
    d->material = NULL;
    d->hover_material = NULL;
    d->hovering = false;
}

dtk3DItem::~dtk3DItem(void)
{
    delete d->node;
    delete d;

    d = NULL;
}

QGLSceneNode *dtk3DItem::node(void)
{
    return d->node;
}

void dtk3DItem::setId(int id)
{
    d->id = id;
}

void dtk3DItem::setNode(QGLSceneNode *node)
{
    d->node = node;
    d->node->setParent(this);
}

void dtk3DItem::setScale(qreal scale)
{
    d->scale = scale;
}

void dtk3DItem::setPosition(const QVector3D& position)
{
    d->position = position;
}

void dtk3DItem::setOrientation(const QVector3D& orientation, qreal angle)
{
    d->orientation = orientation;
    d->orientation_angle = angle;
}

void dtk3DItem::setOrientation(const QQuaternion& orientation)
{
    d->orientation = orientation.vector();
    d->orientation_angle = orientation.scalar();
}

void dtk3DItem::setMaterial(QGLMaterial *material)
{
    d->material = material;
}

void dtk3DItem::setHoverMaterial(QGLMaterial *material)
{
    d->hover_material = material;
}

void dtk3DItem::initialize(QGLView *view, QGLPainter *painter)
{
    Q_UNUSED(painter);

    if (d->id != -1)
        view->registerObject(d->id, this);
}

void dtk3DItem::paint(QGLView *view, QGLPainter *painter)
{
    Q_UNUSED(view);

    painter->modelViewMatrix().push();
    painter->modelViewMatrix().translate(d->position);

    if (d->scale != 1.0)
        painter->modelViewMatrix().scale(d->scale);

    if (d->orientation_angle != 0.0f)
        painter->modelViewMatrix().rotate(d->orientation_angle, d->orientation);

    if(QGLMaterial *material = d->hovering ? d->hover_material : d->material) {
	painter->setColor(material->diffuseColor());
	painter->setFaceMaterial(QGL::AllFaces, material);
    }

    if (d->effect)
        painter->setUserEffect(d->effect);
    else
        painter->setStandardEffect(QGL::LitMaterial);

    int pr_id = painter->objectPickId();

    if (d->id != -1)
        painter->setObjectPickId(d->id);

    if (d->node)
        d->node->draw(painter);

    if (d->effect)
        painter->setStandardEffect(QGL::LitMaterial);

    painter->setObjectPickId(pr_id);

    painter->modelViewMatrix().pop();
}

bool dtk3DItem::event(QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouse_event = (QMouseEvent *)event;
        if (mouse_event->button() == Qt::LeftButton)
            emit pressed();
    } else if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouse_event = (QMouseEvent *)event;
        if (mouse_event->button() == Qt::LeftButton) {
            emit released();
            if (mouse_event->x() >= 0)
                emit clicked();
        }
    } else if (event->type() == QEvent::MouseButtonDblClick) {
        emit doubleClicked();
    } else if (event->type() == QEvent::Enter) {
        d->hovering = true;
        emit hoverChanged();
	emit hovered(true);
    } else if (event->type() == QEvent::Leave) {
        d->hovering = false;
        emit hoverChanged();
	emit hovered(false);
    }

    return QObject::event(event);
}
