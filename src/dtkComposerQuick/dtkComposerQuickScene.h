/* dtkComposerQuickScene.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:17:24 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 10:26:09 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtQuick>

class dtkComposerQuickScenePrivate;

class dtkComposerQuickScene : public QObject
{
    Q_OBJECT

public:
     dtkComposerQuickScene(QObject *parent = 0);
    ~dtkComposerQuickScene(void);

private:
    dtkComposerQuickScenePrivate *d;
};

QML_DECLARE_TYPE(dtkComposerQuickScene)
