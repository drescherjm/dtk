/* dtkComposerQuickScene.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:19:14 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 11:40:58 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickScene.h"

#include <dtkComposer>

class dtkComposerQuickScenePrivate
{
public:
    dtkComposerScene *scene;
};

dtkComposerQuickScene::dtkComposerQuickScene(QObject *parent) : QObject(parent), d(new dtkComposerQuickScenePrivate)
{
    d->scene = new dtkComposerScene;
}

dtkComposerQuickScene::~dtkComposerQuickScene(void)
{
    delete d->scene;
    delete d;
}

dtkComposerScene *dtkComposerQuickScene::scene(void)
{
    return d->scene;
}
