/* dtk3DShaderTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 19:25:58 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 15:42:14 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 116
 */

/* Change Log:
 * 
 */

#include "dtk3DShaderTest.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLShaderProgramEffect>
#include <Qt3D/QGLTeapot>

void dtk3DShaderTestCase::initTestCase(void)
{

}

void dtk3DShaderTestCase::init(void)
{

}

void dtk3DShaderTestCase::test(void)
{
    dtk3DItem *teapot = new dtk3DItem;
    {
	QGLShaderProgramEffect *effect = new QGLShaderProgramEffect;
	effect->setVertexShaderFromFile(":dtk3DShaderTest/dtk3DShaderTest.vert");
	effect->setFragmentShaderFromFile(":dtk3DShaderTest/dtk3DShaderTest.frag");

	QGLBuilder builder;
	builder << QGL::Smooth;
	builder << QGLTeapot();
	teapot->addNode(builder.finalizedSceneNode());
	teapot->setEffect(QGL::LitMaterial);
	teapot->setUserEffect(effect);
    }

    dtk3DScene scene;
    scene.addItem(teapot);
    
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

void dtk3DShaderTestCase::cleanupTestCase(void)
{

}

void dtk3DShaderTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DShaderTest, dtk3DShaderTestCase)
