/* dtk3DMeshTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 12:57:14 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 18:04:41 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 187
 */

/* Change Log:
 * 
 */

#include "dtk3DMeshTest.h"

#include <dtk3D>

void dtk3DMeshTestCase::initTestCase(void)
{

}

void dtk3DMeshTestCase::init(void)
{

}

void dtk3DMeshTestCase::testGeometry(void)
{
    dtk3DMesh *mesh = new dtk3DMesh;
    mesh->data().appendVertex(QVector3D(-1, 0, 0), QVector3D(+1, 0, 0), QVector3D(+0, 1, 0));
    mesh->data().appendNormal(QVector3D(+0, 0, 1), QVector3D(+0, 0, 1), QVector3D(+0, 0, 1));
    mesh->data().appendColor(QColor4ub(255, 0, 0), QColor4ub(0, 255, 0), QColor4ub(0, 0, 255));
    mesh->setColor(Qt::blue);
    mesh->setEffect(QGL::LitMaterial);

    dtk3DScene scene;
    scene.addItem(mesh);

    dtk3DView view;
    view.setScene(&scene);
    view.setTitle("Hit 'Q' key to validate test");
    view.resize(800, 600);
    view.show();
    view.raise();

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
