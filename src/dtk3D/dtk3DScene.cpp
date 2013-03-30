/* dtk3DScene.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:45:53 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 30 14:03:38 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Change Log:
 * 
 */

#include "dtk3DItem.h"
#include "dtk3DScene.h"

class dtk3DScenePrivate
{
public:
    QGLSceneNode *root;

public:
    QGLView *view;
};

dtk3DScene::dtk3DScene(QObject *parent) : QGLAbstractScene(parent), d(new dtk3DScenePrivate)
{
    d->view = NULL;
    d->root = new QGLSceneNode(this);
    d->root->setObjectName("root");
}

dtk3DScene::~dtk3DScene(void)
{
    delete d;
}

void dtk3DScene::addItem(dtk3DItem *item)
{
    d->root->addNode(item);
}

void dtk3DScene::removeItem(dtk3DItem *item)
{
    d->root->removeNode(item);
}

void dtk3DScene::addNode(QGLSceneNode *node)
{
    d->root->addNode(node);
}

void dtk3DScene::removeNode(QGLSceneNode *node)
{
    d->root->removeNode(node);
}

QGLSceneNode *dtk3DScene::mainNode(void) const
{
    return d->root;
}

QList<QObject *> dtk3DScene::objects(void) const
{
    QObjectList objects;

    foreach(QGLSceneNode *node, d->root->allChildren())
        objects << node;

    return objects;
}

void dtk3DScene::initialize(QGLPainter *painter, QGLView *view)
{
    Q_UNUSED(painter);

    foreach(QGLSceneNode *node, d->root->allChildren()) {
        dtk3DItem *item = qobject_cast<dtk3DItem *>(node);
	if (item) {
	    item->initialize(painter, view);
	}
    }
    
    d->view = view;
}

void dtk3DScene::paint(QGLPainter *painter, QGLView *view)
{
    Q_UNUSED(view);

    d->root->draw(painter);
}
