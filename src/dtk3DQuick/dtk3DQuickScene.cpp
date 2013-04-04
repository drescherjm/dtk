/* dtk3DQuickScene.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 12:52:16 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 10:07:33 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 76
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickItem.h"
#include "dtk3DQuickScene.h"

class dtk3DQuickScenePrivate
{
public:
    dtk3DScene *scene;

public:
    QList<dtk3DQuickItem *> items;
};

dtk3DQuickScene::dtk3DQuickScene(QObject *parent) : QObject(parent), d(new dtk3DQuickScenePrivate)
{
    d->scene = new dtk3DScene(this);
}

dtk3DQuickScene::~dtk3DQuickScene(void)
{
    delete d;
}

dtk3DScene *dtk3DQuickScene::scene(void)
{
    return d->scene;
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
	scene->d->scene->addItem(item->item());
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
