/* dtk3DScene.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 12:05:00 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 27 19:18:15 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 120
 */

/* Change Log:
 * 
 */

#include "dtk3DItem.h"
#include "dtk3DScene.h"

class dtk3DScenePrivate
{
public:
};

dtk3DScene::dtk3DScene(QObject *parent) : QObject(parent), d(new dtk3DScenePrivate)
{

}

dtk3DScene::~dtk3DScene(void)
{
    delete d;
}

QBox3D dtk3DScene::boundingBox(void)
{
    QBox3D box;

    foreach (QObject *object, this->children()) {
        dtk3DItem *item = qobject_cast<dtk3DItem *>(object);
	if(item && !item->boundingBox().isNull())
	    box = box.united(item->boundingBox());
    }

    return box;
}

void dtk3DScene::initialize(QGLView *view, QGLPainter *painter)
{
    foreach (QObject *object, this->children()) {
        dtk3DItem *item = qobject_cast<dtk3DItem *>(object);
        if (item) {
	    item->initialize(view, painter);
	}
    }
}

void dtk3DScene::paint(QGLView *view, QGLPainter *painter)
{
    foreach (QObject *object, this->children()) {
        dtk3DItem *item = qobject_cast<dtk3DItem *>(object);
        if (item)
            item->paint(view, painter);
    }
}
