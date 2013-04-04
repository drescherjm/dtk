/* dtk3DQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:19:13 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 16:51:45 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 950
 */

/* Change Log:
 * 
 */

#include "dtk3dQuickScene.h"
#include "dtk3DQuickView.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLPainter>
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

void dtk3DQuickView::paint(QPainter *p)
{
    bool initialized = true;

    if(!d->view) {

	initialized = false;
	
	d->view = new dtk3DView;
	d->view->setOption(QGLView::ObjectPicking, false);

	foreach(QObject *object, this->children()) {
	
	    dtk3DQuickScene *scene;

	    if((scene = qobject_cast<dtk3DQuickScene *>(object)))
		d->view->setScene(scene);
	}
    }

    QGLPainter painter;
    painter.begin(p);
    painter.setClearColor(Qt::black);

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
