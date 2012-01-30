/* dtkComposerScene.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/01/30 10:13:25
 * Version: $Id$
 * Last-Updated: lun. janv. 30 11:31:28 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 7
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerScene.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerScenePrivate
// /////////////////////////////////////////////////////////////////
class dtkComposerScenePrivate
{

};

dtkComposerScene::dtkComposerScene(QObject *parent) : QGraphicsScene(parent), d(new dtkComposerScenePrivate)
{

}

dtkComposerScene::~dtkComposerScene(void)
{
    delete d;

    d = NULL;
}

