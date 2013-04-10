/* dtk3DQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:19:13 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 10 12:34:16 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 1250
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickScene.h"
#include "dtk3DQuickView.h"

#include <dtk3D/dtk3DView_p>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLCube>
#include <Qt3D/QGLPainter>
#include <Qt3D/QGLSphere>
#include <Qt3D/QGLSubsurface>
#include <Qt3D/QGLTeapot>

class dtk3DQuickViewPrivate
{
public:
    dtk3DView *view;
};

dtk3DQuickView::dtk3DQuickView(QQuickItem *parent) : QQuickPaintedItem(parent), d(new dtk3DQuickViewPrivate)
{
    d->view = NULL;

    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setFocus(true);
    this->setRenderTarget(QQuickPaintedItem::InvertedYFramebufferObject);
}

dtk3DQuickView::~dtk3DQuickView(void)
{
    delete d;
}

dtk3DView *dtk3DQuickView::view(void)
{
    return d->view;
}

void dtk3DQuickView::paint(QPainter *p)
{
    bool initialized = true;

    if(!d->view) {

	initialized = false;

	d->view = new dtk3DView;
	d->view->setOption(QGLView::ObjectPicking, false);
	d->view->d->embedded = true;

	int w = this->boundingRect().width();
	int h = this->boundingRect().height();

	d->view->blockSignals(true);
	d->view->setGeometry(QRect(0, 0, w, h));
	d->view->blockSignals(false);

	foreach(QObject *object, this->children()) {
	
	    dtk3DQuickScene *scene;

	    if((scene = qobject_cast<dtk3DQuickScene *>(object))) {
		d->view->setScene(scene->scene());
	    }
	}
    }

    QGLPainter painter;
    painter.begin(p);
    painter.setClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);

    if(!initialized)
	d->view->initializeGL(&painter);

    d->view->earlyPaintGL(&painter);
    painter.setCamera(d->view->camera());
    d->view->paintGL(&painter);
    painter.disableEffect();
}

void dtk3DQuickView::keyPressEvent(QKeyEvent *event)
{
    if(!d->view)
	return;

    d->view->keyPressEvent(event);

    this->update();
}

void dtk3DQuickView::mouseMoveEvent(QMouseEvent *event)
{
    if(!d->view)
	return;

    d->view->mouseMoveEvent(event);

    // Q_ASSERT(!qIsNaN(d->view->camera()->eye().x()));

    this->update();
}

void dtk3DQuickView::mousePressEvent(QMouseEvent *event)
{
    if(!d->view)
	return;

    d->view->mousePressEvent(event);

    this->update();
}

void dtk3DQuickView::mouseReleaseEvent(QMouseEvent *event)
{
    if(!d->view)
	return;

    d->view->mouseReleaseEvent(event);

    this->update();
}

#ifndef QT_NO_WHEELEVENT
void dtk3DQuickView::wheelEvent(QWheelEvent *event)
{
    if(!d->view)
	return;

    d->view->wheelEvent(event);

    this->update();
}
#endif
