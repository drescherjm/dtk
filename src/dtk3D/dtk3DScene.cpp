/* dtk3DScene.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 12:05:00 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 16:31:14 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 26
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

    d = NULL;
}

void dtk3DScene::initialize(QGLView *view, QGLPainter *painter)
{
    foreach (QObject *object, this->children()) {
        dtk3DItem *item = qobject_cast<dtk3DItem *>(object);
        if (item) {
            item->initialize(view, painter);
	    connect(item, SIGNAL(pressed()), view, SLOT(update()));
	    connect(item, SIGNAL(released()), view, SLOT(update()));
	    connect(item, SIGNAL(clicked()), view, SLOT(update()));
	    connect(item, SIGNAL(doubleClicked()), view, SLOT(update()));
	    connect(item, SIGNAL(hoverChanged()), view, SLOT(update()));
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
