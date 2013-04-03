/* dtk3DQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:19:13 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 10:26:13 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 815
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

dtk3DQuickView::dtk3DQuickView(QQuickItem *parent) : QQuickItem(parent), d(new dtk3DQuickViewPrivate)
{
    d->view = NULL;

    this->setAcceptedMouseButtons(Qt::LeftButton);
    this->setAcceptHoverEvents(true);
    this->setFlag(QQuickItem::ItemHasContents, true);
}

dtk3DQuickView::~dtk3DQuickView(void)
{
    delete d;
}

void dtk3DQuickView::paint(void)
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
	d->view->setScene(scene);
    }

    auto clearGL = [=]() {
#if defined(QT_OPENGL_ES)
	glClearDepthf(1);
#else
	glClearDepth(1);
#endif
	glDepthMask(GL_TRUE);
#if defined(QT_OPENGL_ES)
	glDepthRangef(0.0f, 1.0f);
#else
	glDepthRange(0.0f, 1.0f);
#endif
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };

    if(!initialized) {
	QGLPainter painter;
	painter.begin();
	clearGL();
	d->view->resizeGL(this->width(), this->height());
    	d->view->initializeGL(&painter);
    }

    if(true) {
	QGLPainter painter;
	painter.begin();
	clearGL();
	d->view->earlyPaintGL(&painter);
	painter.setCamera(d->view->camera());
	d->view->paintGL(&painter);
    }
}

void dtk3DQuickView::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData& data)
{
    if (change == QQuickItem::ItemSceneChange) {

        QQuickWindow *window = this->window();

        if (!window)
            return;

        connect(window, SIGNAL(beforeRendering()), this, SLOT(paint()), Qt::DirectConnection);

        window->setClearBeforeRendering(false);
    }

    QQuickItem::itemChange(change, data);
}
