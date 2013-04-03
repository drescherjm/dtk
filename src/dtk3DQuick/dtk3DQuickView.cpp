/* dtk3DQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:19:13 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 11:49:37 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 886
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickView.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLPainter>
#include <Qt3D/QGLSubsurface>
#include <Qt3D/QGLTeapot>

#if defined(Q_OS_MAC)
#include <OpenGL/gl.h>
#else
#include <Gl/gl.h>
#endif

class dtk3DQuickViewPrivate
{
public:
    dtk3DView *view;
};

dtk3DQuickView::dtk3DQuickView(QQuickItem *parent) : QQuickPaintedItem(parent), d(new dtk3DQuickViewPrivate)
{
    d->view = NULL;

    this->setAcceptedMouseButtons(Qt::AllButtons);
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

	QGLBuilder builder;
	builder << QGL::Smooth;
	builder << QGLTeapot();
    
	dtk3DItem *teapot = new dtk3DItem;
	teapot->addNode(builder.finalizedSceneNode());
	teapot->setEffect(QGL::LitMaterial);
	teapot->setColor(Qt::green);

	dtk3DScene *scene = new dtk3DScene;
	scene->addItem(teapot);
	
	d->view = new dtk3DView;
	d->view->setOption(QGLView::ObjectPicking, false);
	d->view->setScene(scene);
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
