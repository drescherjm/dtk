/* dtk3DQuickView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:19:13 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  2 17:03:37 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 488
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickView.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLPainter>
#include <Qt3D/QGLTeapot>

#include <OpenGL/gl.h>

class dtk3DQuickViewPrivate
{
public:
    dtk3DView *view;
};

dtk3DQuickView::dtk3DQuickView(QQuickItem *parent) : QQuickItem(parent), d(new dtk3DQuickViewPrivate)
{
    d->view = NULL;

    this->setFlag(QQuickItem::ItemHasContents, true);
}

dtk3DQuickView::~dtk3DQuickView(void)
{
    delete d;
}

void dtk3DQuickView::paint(void)
{
    QGLPainter painter;
    painter.begin(this->window()->openglContext());

    if(!d->view) {

	QGLBuilder *builder = new QGLBuilder;
	*builder << QGL::Smooth;
	*builder << QGLTeapot();
    
	dtk3DItem *teapot = new dtk3DItem;
	teapot->addNode(builder->finalizedSceneNode());
	teapot->setEffect(QGL::LitMaterial);
	teapot->setColor(Qt::green);

	dtk3DScene *scene = new dtk3DScene;
	scene->addItem(teapot);
	
	d->view = new dtk3DView;
	d->view->setScene(scene);
	d->view->resize(this->window()->size());


	// -- here goes initializeGL

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

#if defined(QT_OPENGL_ES)
	glDepthRangef(0.0f, 1.0f);
#else
	glDepthRange(0.0f, 1.0f);
#endif

	if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendColor))
	    painter.glBlendColor(0, 0, 0, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendEquation))
	    painter.glBlendEquation(GL_FUNC_ADD);
	else if (painter.hasOpenGLFeature(QOpenGLFunctions::BlendEquationSeparate))
	    painter.glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

	glDisable(GL_CULL_FACE);

	d->view->resizeGL(this->window()->width(), this->window()->height());

	// --

	d->view->initializeGL(&painter);

    } else {

	d->view->resizeGL(this->window()->width(), this->window()->height());
	painter.setCamera(d->view->camera());
	d->view->earlyPaintGL(&painter);
	d->view->paintGL(&painter);
    }
}

void dtk3DQuickView::sync(void)
{

}

void dtk3DQuickView::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData& data)
{
    if (change == QQuickItem::ItemSceneChange) {

	qDebug() << 33;

        QQuickWindow *window = this->window();

        if (!window)
            return;

        connect(window, SIGNAL(beforeRendering()), this, SLOT(paint()), Qt::DirectConnection);
        connect(window, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);

        window->setClearBeforeRendering(false);
    }

    QQuickItem::itemChange(change, data);
}
