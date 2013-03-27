/* dtk3DItemTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 27 14:14:24 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 27 15:32:24 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 115
 */

/* Change Log:
 * 
 */

#include "dtk3DItemTest.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLSphere>

void dtk3DItemTestCase::initTestCase(void)
{

}

void dtk3DItemTestCase::init(void)
{

}

void dtk3DItemTestCase::testHierarchy(void)
{
    static int id = 0;

    QGLBuilder builder;
    builder << QGL::Faceted;
    builder << QGLSphere();

    QGLSceneNode *node = builder.finalizedSceneNode();

    dtk3DScene scene;
    
    dtk3DItem root(&scene);
    root.setObjectName("root");
    root.setId(id++);
    root.setNode(node->clone());
    root.setColor(Qt::red);

    dtk3DItem right_sub_item(&scene);
    right_sub_item.setObjectName("right_sub_item");
    right_sub_item.setId(id++);
    right_sub_item.setNode(node->clone());
    right_sub_item.setColor(Qt::green);
    right_sub_item.setPosition(QVector3D(1.0, 1.0, 0.0));
    
    dtk3DItem right_sub_sub_item(&right_sub_item);
    right_sub_sub_item.setObjectName("right_sub_sub_item");
    right_sub_sub_item.setId(id++);
    right_sub_sub_item.setNode(node->clone());
    right_sub_sub_item.setColor(Qt::blue);
    right_sub_sub_item.setPosition(QVector3D(1.0, 1.0, 0.0));

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

void dtk3DItemTestCase::cleanupTestCase(void)
{

}

void dtk3DItemTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DItemTest, dtk3DItemTestCase)
