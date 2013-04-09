/* dtk3DView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:41:55 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Apr  5 00:49:35 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 257
 */

/* Change Log:
 * 
 */

#include "dtk3DItem.h"
#include "dtk3DScene.h"
#include "dtk3DView.h"
#include "dtk3DView_p.h"

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLSceneNode>
#include <Qt3D/QGLSphere>
#include <Qt3D/QGLView>

#include <QtGui>

dtk3DView::dtk3DView(QWindow *parent) : QGLView(parent), d(new dtk3DViewPrivate)
{
    d->embedded = false;
    d->current = NULL;
    d->scene = NULL;

    this->camera()->setFieldOfView(30);
    this->camera()->setNearPlane(0.01);

    this->setOption(QGLView::ObjectPicking, true);
}

dtk3DView::~dtk3DView(void)
{
    delete d;
}

void dtk3DView::setScene(dtk3DScene *scene)
{
    d->scene = scene;
}

void dtk3DView::fit(void)
{
    QVector3D eye = this->camera()->eye();
    QVector3D ctr = this->camera()->center();
    QVector3D direction = ctr-eye;

    this->fit(direction);
}

void dtk3DView::fit(const QVector3D& direction)
{
    QBox3D box;

    if(d->current)
	box = d->current->boundingBox();
    else
	box = d->scene->boundingBox();

    QVector3D center = box.center();
    QVector3D size = box.size();

    qreal s = qMax(size.x(), qMax(size.y(), size.z()));
    qreal a = this->camera()->fieldOfView();
    qreal d = (s/2)/tan((a*M_PI/180)/2);

    this->camera()->setCenter(center);
    this->camera()->setEye(center - direction.normalized()*(d+s/2.0));
}

void dtk3DView::fitFromTop(void)
{
    this->fit(QVector3D(0.0, -1.0, 0.0));
    this->camera()->setUpVector(QVector3D(0.0, 0.0, 1.0));
}

void dtk3DView::fitFromBack(void)
{
    this->fit(QVector3D(0.0, 0.0, 1.0));
    this->camera()->setUpVector(QVector3D(0.0, 1.0, 0.0));
}

void dtk3DView::fitFromLeft(void)
{
    this->fit(QVector3D(-1.0, 0.0, 0.0));
    this->camera()->setUpVector(QVector3D(0.0, 1.0, 0.0));
}

void dtk3DView::fitFromFront(void)
{
    this->fit(QVector3D(0.0, 0.0, -1.0));
    this->camera()->setUpVector(QVector3D(0.0, 1.0, 0.0));
}

void dtk3DView::fitFromRight(void)
{
    this->fit(QVector3D(1.0, 0.0, 0.0));
    this->camera()->setUpVector(QVector3D(0.0, 1.0, 0.0));
}

void dtk3DView::fitFromBottom(void)
{
    this->fit(QVector3D(0.0, 1.0, 0.0));
    this->camera()->setUpVector(QVector3D(0.0, 0.0, 1.0));
}

const QPoint dtk3DView::mapToScreen(const QVector3D& point)
{
    QMatrix4x4 modl = this->camera()->modelViewMatrix();
    QMatrix4x4 proj = this->camera()->projectionMatrix(qreal(this->width())/qreal(this->height()));

    QVector4D pos = QVector4D(point, 1.0);
    pos = modl.map(pos);
    pos = proj.map(pos);
    pos /= pos.w();
    pos *= 0.5;
    pos += QVector4D(0.5, 0.5, 0.5, 0.5);
    
    QPoint position;
    position.setX(                pos.x()*qreal(this->width()));
    position.setY(this->height()-(pos.y()*qreal(this->height())));
    return position;
}

void dtk3DView::initializeGL(QGLPainter *painter)
{
    if (d->scene)
        d->scene->initialize(painter, this);

    QGLView::initializeGL(painter);
}

void dtk3DView::earlyPaintGL(QGLPainter *painter)
{
    QGLView::earlyPaintGL(painter);
}

void dtk3DView::paintGL(QGLPainter *painter)
{
    if (d->scene)
        d->scene->paint(painter, this);

    QGLView::paintGL(painter);
}

void dtk3DView::resizeGL(int width, int height)
{
    QGLView::resizeGL(width, height);
}

void dtk3DView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Tab:
        this->setOption(QGLView::ShowPicking, ((options() & QGLView::ShowPicking) == 0));
        this->update();
	break;
    case Qt::Key_F:
	this->fit();
	break;
    case Qt::Key_O:
	this->camera()->setProjectionType(QGLCamera::Orthographic);
	break;
    case Qt::Key_P:
	this->camera()->setProjectionType(QGLCamera::Perspective);
	break;
    case Qt::Key_X:
	if(event->modifiers() & Qt::AltModifier)
	    this->fitFromLeft();
	else
	    this->fitFromRight();
	break;
    case Qt::Key_Y:
	if(event->modifiers() & Qt::AltModifier)
	    this->fitFromBottom();
	else
	    this->fitFromTop();
	break;
    case Qt::Key_Z:
	if(event->modifiers() & Qt::AltModifier)
	    this->fitFromBack();
	else
	    this->fitFromFront();
	break;
    default:
	QGLView::keyPressEvent(event);
    };
}

void dtk3DView::mouseMoveEvent(QMouseEvent *event)
{
    QGLView::mouseMoveEvent(event);

    if(d->embedded)
	return;

    if(dtk3DItem *item = qobject_cast<dtk3DItem *>(this->objectForPoint(event->pos())))
	d->current = item;
    else
	d->current = NULL;
}

void dtk3DView::mousePressEvent(QMouseEvent *event)
{
    QGLView::mousePressEvent(event);
}

void dtk3DView::mouseReleaseEvent(QMouseEvent *event)
{
    QGLView::mouseReleaseEvent(event);
}

void dtk3DView::exposeEvent(QExposeEvent *event)
{
    if(!d->embedded)
	QGLView::exposeEvent(event);
}
