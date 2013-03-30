/* dtk3DItemTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 27 14:14:24 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 30 16:55:19 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 155
 */

/* Change Log:
 * 
 */

#include "dtk3DItemTest.h"

#include <dtk3D>

#include <Qt3D/QGLBuilder>
#include <Qt3D/QGLSphere>
#include <Qt3D/QGLTeapot>
#include <Qt3D/QGraphicsRotation3D>
#include <Qt3D/QGraphicsScale3D>
#include <Qt3D/QGraphicsTranslation3D>

void dtk3DItemTestCase::initTestCase(void)
{

}

void dtk3DItemTestCase::init(void)
{

}

void dtk3DItemTestCase::testHierarchy(void)
{
    QGLSceneNode *node0; {

	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLSphere();

	QGraphicsScale3D *transform = new QGraphicsScale3D;
	transform->setScale(QVector3D(0.5, 0.5, 0.5));

	QGLMaterial *material = new QGLMaterial;
	material->setColor(Qt::blue);
	
	node0 = builder.finalizedSceneNode();
	node0->addTransform(transform);
	node0->setObjectName("node0");
	node0->setEffect(QGL::LitMaterial);
	node0->setMaterial(material);
	node0->setPosition(QVector3D(2.0, 0.0, 0.0));
    }

    QGLSceneNode *node1; {

	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLSphere();

	QGraphicsScale3D *transform = new QGraphicsScale3D;
	transform->setScale(QVector3D(0.5, 0.5, 0.5));

	QGLMaterial *material = new QGLMaterial;
	material->setColor(Qt::green);
	
	node1 = builder.finalizedSceneNode();
	node1->addTransform(transform);
	node1->setObjectName("node1");
	node1->setEffect(QGL::LitMaterial);
	node1->setMaterial(material);
	node1->setPosition(QVector3D(-2.0, 0.0, 0.0));
    }

// ///////////////////////////////////////////////////////////////////
// Using item API
// ///////////////////////////////////////////////////////////////////

    dtk3DItem *item1 = new dtk3DItem; {

	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLTeapot();

	QGraphicsScale3D *transform = new QGraphicsScale3D;
	transform->setScale(QVector3D(0.5, 0.5, 0.5));

	QGLSceneNode *node = builder.finalizedSceneNode();
	node->setObjectName("node");
	node->addTransform(transform);

	item1->setObjectName("item1");
	item1->addNode(node);
	item1->translate(QVector3D(0.0, 0.0, -2.0));
	item1->rotate(QVector3D(0.0, 1.0, 0.0), -90.0);
	item1->setEffect(QGL::LitMaterial);
	item1->setColor(Qt::red);
    }

    dtk3DItem *item2 = new dtk3DItem; {

	QGLBuilder builder;
	builder << QGL::Faceted;
	builder << QGLSphere(0.5, 2);

	QGLSceneNode *node = builder.finalizedSceneNode();
	node->setObjectName("node");

	item2->setObjectName("item2");
	item2->addNode(node);
	item2->setFlag(dtk3DItem::Interactive, true);
	item2->setEffect(QGL::LitMaterial);
	item2->setColor(Qt::green);

	dtk3DItem *item2_1 = new dtk3DItem(item2); {

	    item2_1->setObjectName("item2_1");
	    item2_1->addNode(node);
	    item2_1->translate(QVector3D(0.0, 1.0, 0.0));
	    item2_1->setFlag(dtk3DItem::Interactive, true);
	    item2_1->setEffect(QGL::LitMaterial);
	    item2_1->setColor(Qt::magenta);

	    dtk3DItem *item2_1_1 = new dtk3DItem(item2_1); {

		item2_1_1->setObjectName("item2_1_1");
		item2_1_1->addNode(node);
		item2_1_1->translate(QVector3D(0.0, 1.0, 0.0));
		item2_1_1->setFlag(dtk3DItem::Interactive, false);
		item2_1_1->setEffect(QGL::LitMaterial);
		item2_1_1->setColor(Qt::yellow);
	    }
	}
    }

    qDebug() << item2;

    dtk3DScene scene;
    scene.addNode(node0);
    scene.addNode(node1);
    scene.addItem(item1);
    scene.addItem(item2);

    dtk3DView view;
    view.setScene(&scene);
    view.setTitle("Hit 'Q' key to validate test");
    view.resize(1024, 512);
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
