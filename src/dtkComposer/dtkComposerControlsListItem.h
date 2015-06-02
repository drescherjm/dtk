/* @(#)dtkComposerControlsListItem.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/06/03 12:33:16
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <dtkWidgets/dtkToolBox>

class dtkComposerSceneNode;

class dtkComposerControlsListItem : public dtkToolBoxItem
{
    Q_OBJECT

public:
             dtkComposerControlsListItem(QWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItem(void);
};





