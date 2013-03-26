/* dtk3DViewTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 11:35:55 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 16:34:35 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 111
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
    view.setTitle("Hit 'Q' key to validate test");
    view.resize(800, 600);
    view.show();
    view.raise();

    QEventLoop loop;
    connect(&view, SIGNAL(quit()), &loop, SLOT(quit()));
    loop.exec();
}

void dtk3DViewTestCase::testShapes(void)
{
    static int id;

    QGLMaterial *material = new QGLMaterial(this);
    material->setAmbientColor(QColor(192, 150, 128));
    material->setSpecularColor(QColor(60, 60, 60));
    material->setShininess(128);
    
    QGLMaterial *materialHighlight = new QGLMaterial(this);
    materialHighlight->setAmbientColor(QColor(255, 192, 0));
    materialHighlight->setSpecularColor(QColor(60, 60, 0));
    materialHighlight->setShininess(128);

    dtk3DScene scene;

    dtk3DItem teapot(&scene); {
	QGLBuilder builder;
	builder << QGL::Smooth;
	builder << QGLTeapot();
	teapot.setId(id++);
	teapot.setNode(builder.finalizedSceneNode());
	teapot.setMaterial(material);
	teapot.setHoverMaterial(materialHighlight);
    }

    dtk3DItem cube1(&scene); {
	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLCube();
	cube1.setId(id++);
	cube1.setNode(builder.finalizedSceneNode());
        cube1.setPosition(QVector3D(2.5, 0.0, 0.0));
	cube1.setMaterial(material);
	cube1.setHoverMaterial(materialHighlight);
    }

    dtk3DItem cube2(&scene); {
        QGLBuilder builder;
        builder << QGL::Faceted;
        builder << QGLCube();
	cube2.setId(id++);
        cube2.setNode(builder.finalizedSceneNode());
        cube2.setPosition(QVector3D(-2.5, 0.0, 0.0));
	cube2.setMaterial(material);
	cube2.setHoverMaterial(materialHighlight);
    }
    
    dtk3DView view;
    view.setScene(&scene);
    view.setTitle("Click right cube to validate test");
    view.resize(1600, 800);
    view.show();
    view.raise();

    QEventLoop loop;
    connect(&cube1, SIGNAL(clicked()), &loop, SLOT(quit()));
    loop.exec();
}

void dtk3DViewTestCase::cleanupTestCase(void)
{

}

void dtk3DViewTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DViewTest, dtk3DViewTestCase)
