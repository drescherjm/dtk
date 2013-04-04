/* dtk3DQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:19:13 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 11:31:30 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 980
 */

/* Change Log:
 * 
 */

#include "dtk3dQuickScene.h"
#include "dtk3DQuickView.h"

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

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    if(!initialized)
	d->view->initializeGL(&painter);

    QRect viewport = mapRectToScene(boundingRect()).toRect();
    QRect target_rect(0, 0, viewport.width(), viewport.height());
    QGLSubsurface surface(painter.currentSurface(), target_rect);

    painter.pushSurface(&surface);
    d->view->earlyPaintGL(&painter);
    painter.setCamera(d->view->camera());
    d->view->paintGL(&painter);
    painter.popSurface();
    painter.disableEffect();
}
