/* dtk3DMeshTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 12:57:14 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Mar 26 21:29:31 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 123
 */

/* Change Log:
 * 
 */

#include "dtk3DMeshTest.h"

#include <dtk3D>

void dtk3DMeshTestCase::initTestCase(void)
{
    dtk3DSettings settings;
    settings.beginGroup("mesh");
    dtk3D::mesh::pluginManager().initialize(settings.value("plugins").toString());
    settings.endGroup();
}

void dtk3DMeshTestCase::init(void)
{

}

void dtk3DMeshTestCase::testGMSH(void)
{
    static int id = 0;

    dtk3DScene scene;

    dtk3DMesh *mesh = dtk3D::mesh::pluginFactory().create("gmsh");
    if(!mesh)
	return;
    mesh->read("/Users/jwintz/Desktop/cyclone.geo");
    mesh->setId(id++);
    mesh->setParent(&scene);

    dtk3DView view;
    view.setScene(&scene);
    view.setTitle("Hit 'Q' key to validate test");
    view.resize(800, 600);
    view.show();
    view.raise();

    view.camera()->setEye(QVector3D(0, 0, scene.boundingBox().size().length()*4));
    view.camera()->setCenter(scene.boundingBox().center());

    QEventLoop loop;
    connect(&view, SIGNAL(quit()), &loop, SLOT(quit()));
    loop.exec();
}

void dtk3DMeshTestCase::cleanupTestCase(void)
{

}

void dtk3DMeshTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DMeshTest, dtk3DMeshTestCase)
