/* dtk3DItem.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 12:24:34 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 27 20:38:51 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 547
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
    int    pr_id;

public:
    QGLSceneNode *node;

public:
    QGLAbstractEffect   *effect;

public:
    QGLMaterial       *material;
    QGLMaterial *hover_material;

public:
           QColor          color;
    static QColor hovering_color;

public:
    bool hovering;

public:
    QPoint start;
    bool pan;
    bool rot;

public:
    QGLView *view;
};

QColor dtk3DItemPrivate::hovering_color = qRgb(255, 186, 210);

dtk3DItem::dtk3DItem(QObject *parent) : QObject(parent), d(new dtk3DItemPrivate)
{
    d->id = -1;
    d->scale = 1.0;
    d->node = NULL;
    d->hovering = false;
    d->effect = NULL;
    d->color = qRgb(170, 202, 0);
    d->material = NULL;
    d->hover_material = NULL;
    d->pan = false;
    d->rot = false;
    d->view = NULL;
}

dtk3DItem::~dtk3DItem(void)
{
    delete d->node;
    delete d;
}

QBox3D dtk3DItem::boundingBox(void) const
{
    if (d->node)
	return d->node->boundingBox();
    else
	return QBox3D();
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

void dtk3DItem::setColor(const QColor& color)
{
    d->color = color;
}

void dtk3DItem::initialize(QGLView *view, QGLPainter *painter)
{
    Q_UNUSED(painter);

    if (d->id != -1)
        view->registerObject(d->id, this);

    foreach (QObject *object, this->children()) {
        dtk3DItem *item = qobject_cast<dtk3DItem *>(object);
        if (item) {
	    item->initialize(view, painter);
	}
    }

    d->view = view;
}

void dtk3DItem::paint(QGLView *view, QGLPainter *painter)
{
     this->predraw(view, painter);
     this->draw(view, painter);
     
     foreach (QObject *object, this->children()) {
     	 dtk3DItem *item = qobject_cast<dtk3DItem *>(object);
     	 if (item) {
     	     item->paint(view, painter);
     	 }
     }
	
    this->postdraw(view, painter);
}

bool dtk3DItem::event(QEvent *event)
{
    if(!d->view)
	return QObject::event(event);

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouse_event = (QMouseEvent *)event;
        if (mouse_event->button() == Qt::LeftButton) {
	    d->pan = (mouse_event->button() && (mouse_event->modifiers() & Qt::ShiftModifier));
	    d->rot = (mouse_event->button() && (mouse_event->modifiers()  ==  Qt::NoModifier));
	    d->start = d->view->mapFromGlobal(mouse_event->globalPos());
            emit pressed();
	    d->view->update();
	}
    }

    if (event->type() == QEvent::MouseMove) {
	QMouseEvent *mouse_event = (QMouseEvent *)event;
	QPoint delta = d->view->mapFromGlobal(mouse_event->globalPos()) - d->start;
	if(d->pan)
	    this->pan(delta.x(), delta.y());
	if(d->rot)
	    this->rot(delta.x(), delta.y());
	d->start = d->view->mapFromGlobal(mouse_event->globalPos());
	emit moved();
	d->view->update();
    }

    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouse_event = (QMouseEvent *)event;
        if (mouse_event->button() == Qt::LeftButton) {
	    d->pan = false;
	    d->rot = false;
	    d->start = QPoint();
            emit released();
            if (mouse_event->x() >= 0)
                emit clicked();
	    d->view->update();
        }
    }

    if (event->type() == QEvent::MouseButtonDblClick) {
        emit doubleClicked();
	d->view->update();
    }

    if (event->type() == QEvent::Enter) {
        d->hovering = true;
        emit hoverChanged();
	emit hovered(true);
	d->view->update();
    }

    if (event->type() == QEvent::Leave) {
        d->hovering = false;
        emit hoverChanged();
	emit hovered(false);
	d->view->update();
    }

    return QObject::event(event);
}

void dtk3DItem::predraw(QGLView *view, QGLPainter *painter)
{
    Q_UNUSED(view);

    painter->modelViewMatrix().push();
    painter->modelViewMatrix().translate(d->position);

    if (d->scale != 1.0)
        painter->modelViewMatrix().scale(d->scale);

    if (d->orientation_angle != 0.0f)
        painter->modelViewMatrix().rotate(d->orientation_angle, d->orientation);

    if (d->effect)
        painter->setUserEffect(d->effect);
    else
        painter->setStandardEffect(QGL::LitMaterial);

    if(QGLMaterial *material = d->hovering ? d->hover_material : d->material) {
	painter->setColor(material->diffuseColor());
	painter->setFaceMaterial(QGL::AllFaces, material);
    } else {
	QColor color = d->hovering ? d->hovering_color : d->color;
	painter->setFaceColor(QGL::AllFaces, color);
    }

    d->pr_id = painter->objectPickId();

    if (d->id != -1)
        painter->setObjectPickId(d->id);
}

void dtk3DItem::draw(QGLView *view, QGLPainter *painter)
{
    Q_UNUSED(view);
    
    if (d->node)
        d->node->draw(painter);
}

void dtk3DItem::postdraw(QGLView *view, QGLPainter *painter)
{
    Q_UNUSED(view);

    if (d->effect)
        painter->setStandardEffect(QGL::LitMaterial);

    painter->setObjectPickId(d->pr_id);

    painter->modelViewMatrix().pop();
}

#include "dtk3DView.h"

void dtk3DItem::pan(int deltax, int deltay)
{
    if(!d->view)
	return;
}

void dtk3DItem::rot(int deltax, int deltay)
{
    if(!d->view)
	return;    
}
