/* dtk3DQuickScene.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 12:52:16 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 16:51:07 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 68
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickItem.h"
#include "dtk3DQuickScene.h"

class dtk3DQuickScenePrivate
{
public:
    QList<dtk3DQuickItem *> items;
};

dtk3DQuickScene::dtk3DQuickScene(QObject *parent) : dtk3DScene(parent), d(new dtk3DQuickScenePrivate)
{

}

dtk3DQuickScene::~dtk3DQuickScene(void)
{
    delete d;
}

QQmlListProperty<dtk3DQuickItem> dtk3DQuickScene::items(void)
{
    return QQmlListProperty<dtk3DQuickItem>(this, &(d->items),
					    &dtk3DQuickScene::addItem,
					    &dtk3DQuickScene::countItems,
					    &dtk3DQuickScene::itemAt,
					    &dtk3DQuickScene::clearItems);
}

void dtk3DQuickScene::addItem(QQmlListProperty<dtk3DQuickItem> *items, dtk3DQuickItem *item)
{
    dtk3DQuickScene *scene = qobject_cast<dtk3DQuickScene *>(items->object);

    if (scene) {
	scene->dtk3DScene::addItem(item);
	scene->d->items << item;
    }
}

int dtk3DQuickScene::countItems(QQmlListProperty<dtk3DQuickItem> *items)
{
    dtk3DQuickScene *scene = qobject_cast<dtk3DQuickScene *>(items->object);

    if (scene) {
	return scene->d->items.count();
    }

    return 0;
}

void dtk3DQuickScene::clearItems(QQmlListProperty<dtk3DQuickItem> *items)
{
    dtk3DQuickScene *scene = qobject_cast<dtk3DQuickScene *>(items->object);

    if (scene) {
	return scene->d->items.clear();
    }
}

dtk3DQuickItem *dtk3DQuickScene::itemAt(QQmlListProperty<dtk3DQuickItem> *items, int index)
{
    dtk3DQuickScene *scene = qobject_cast<dtk3DQuickScene *>(items->object);

    if (scene) {
	return scene->d->items.at(index);
    }

    return NULL;
}
