/* dtk3DQuickScene.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr  3 12:50:26 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 16:46:58 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 43
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtk3DQuickItem.h"

#include <dtk3D>

#include <QtCore>
#include <QtQuick>

class dtk3DQuickScenePrivate;

class dtk3DQuickScene : public dtk3DScene
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<dtk3DQuickItem> items READ items)

public:
     dtk3DQuickScene(QObject *parent = 0);
    ~dtk3DQuickScene(void);

public:
    QQmlListProperty<dtk3DQuickItem> items(void);

public:
    static void addItem(QQmlListProperty<dtk3DQuickItem> *items, dtk3DQuickItem *item);
    static int countItems(QQmlListProperty<dtk3DQuickItem> *items);
    static void clearItems(QQmlListProperty<dtk3DQuickItem> *items);
    static dtk3DQuickItem *itemAt(QQmlListProperty<dtk3DQuickItem> *items, int index);

private:
    dtk3DQuickScenePrivate *d;
};

QML_DECLARE_TYPE(dtk3DQuickScene)
