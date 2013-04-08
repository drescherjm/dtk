/* dtk3DEffectTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 14:55:24 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 20:07:51 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Change Log:
 * 
 */

#include "dtk3DEffectTest.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLCube>

void dtk3DEffectTestCase::initTestCase(void)
{

}

void dtk3DEffectTestCase::init(void)
{

}

void dtk3DEffectTestCase::test(void)
{
    dtk3DItem *item = new dtk3DItem;
    {
	dtk3DEffect *effect = new dtk3DEffect;
	effect->setVertexShaderFromFile(":dtk3DEffectTest/dtk3DEffectTest.vert");
	effect->setGeometryShaderFromFile(":dtk3DEffectTest/dtk3DEffectTest.geom");
	effect->setFragmentShaderFromFile(":dtk3DEffectTest/dtk3DEffectTest.frag");

	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLCube();

	item->addNode(builder.finalizedSceneNode());
	item->setColor(Qt::red);
	item->setEffect(QGL::LitMaterial);
	item->setUserEffect(effect);
    }

    dtk3DScene scene;
    scene.addItem(item);
    
    dtk3DView view;
    view.setScene(&scene);
    view.setTitle("Hit 'Q' to validate test");
    view.resize(1600, 800);
    view.show();
    view.raise();

    QEventLoop loop;
    connect(&view, SIGNAL(quit()), &loop, SLOT(quit()));
    loop.exec();
}

void dtk3DEffectTestCase::cleanupTestCase(void)
{

}

void dtk3DEffectTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DEffectTest, dtk3DEffectTestCase)
