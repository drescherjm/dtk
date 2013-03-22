/* dtk3DViewTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 11:35:55 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 14:56:20 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 78
 */

/* Change Log:
 * 
 */

#include "dtk3DViewTest.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLCube>
#include <Qt3D/QGLTeapot>

void dtk3DViewTestCase::initTestCase(void)
{

}

void dtk3DViewTestCase::init(void)
{

}

void dtk3DViewTestCase::testInstanciation(void)
{
    dtk3DView view;
    view.resize(800, 600);
    view.show();
    view.raise();
}

void dtk3DViewTestCase::testShapes(void)
{
    dtk3DScene scene;

    dtk3DItem teapot(&scene); {
	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLTeapot();
	teapot.setNode(builder.finalizedSceneNode());
    }

    dtk3DItem cube1(&scene); {
	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLCube();
	cube1.setNode(builder.finalizedSceneNode());
        cube1.setPosition(QVector3D(2.5, 0.0, 0.0));
    }

    dtk3DItem cube2(&scene); {
        QGLBuilder builder;
        builder << QGL::Faceted;
        builder << QGLCube();
        cube2.setNode(builder.finalizedSceneNode());
        cube2.setPosition(QVector3D(-2.5, 0.0, 0.0));
    }
    
    dtk3DView view;
    view.setScene(&scene);
    view.resize(800, 600);
    view.show();
    view.raise();

    QEventLoop loop;
// connect(&cube1, SIGNAL(clicked()), &loop, SLOT(quit()));
    loop.exec();
}

void dtk3DViewTestCase::cleanupTestCase(void)
{

}

void dtk3DViewTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DViewTest, dtk3DViewTestCase)
