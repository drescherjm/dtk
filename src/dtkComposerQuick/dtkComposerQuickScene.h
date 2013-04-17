/* dtkComposerQuickScene.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:17:24 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 11:40:35 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkComposer>

#include <QtCore>
#include <QtQuick>

class dtkComposerQuickScenePrivate;

class dtkComposerQuickScene : public QObject
{
    Q_OBJECT

public:
     dtkComposerQuickScene(QObject *parent = 0);
    ~dtkComposerQuickScene(void);

public:
    dtkComposerScene *scene(void);

private:
    dtkComposerQuickScenePrivate *d;
};

QML_DECLARE_TYPE(dtkComposerQuickScene)
