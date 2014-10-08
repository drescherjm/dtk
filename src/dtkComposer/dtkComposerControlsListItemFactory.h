/* @(#)dtkComposerControlsListItemFactory.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/06/04 13:21:50
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#ifndef DTKCOMPOSERCONTROLSLISTITEMFACTORY_H
#define DTKCOMPOSERCONTROLSLISTITEMFACTORY_H

#include <QtGui>

#include <dtkGuiSupport/dtkToolBox>

class dtkComposerSceneNode;
class dtkComposerControlsListItem;

class dtkComposerControlsListItemFactory
{
public:

    dtkComposerControlsListItemFactory(void);
    virtual ~dtkComposerControlsListItemFactory(void);

public:
    static dtkComposerControlsListItemFactory *instance(void);

private:
    static dtkComposerControlsListItemFactory *s_instance;

public:
    dtkComposerControlsListItem *create(QListWidget *list, dtkComposerSceneNode *node);
    dtkToolBoxItem *create(dtkComposerSceneNode *node);

};

#endif


