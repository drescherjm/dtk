/* @(#)dtkComposerControlsListItemReal.h ---
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

#include "dtkComposerControlsListItem.h"

class dtkComposerSceneNode;
class dtkComposerControlsListItemRealPrivate;

class dtkComposerControlsListItemReal: public dtkComposerControlsListItem
{

    Q_OBJECT

public:
    dtkComposerControlsListItemReal(QWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItemReal(void);

public slots:
    void onValueChanged(double value);

private:
    dtkComposerControlsListItemRealPrivate *d;
};




