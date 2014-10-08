/* @(#)dtkComposerControlsListItemFile.h ---
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
class dtkComposerControlsListItemFilePrivate;

class dtkComposerControlsListItemFile: public dtkComposerControlsListItem
{

    Q_OBJECT

public:
             dtkComposerControlsListItemFile(QWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItemFile(void);

public slots:
    void onValueChanged(const QString& value);
    void onBrowse(const QString& value);
    void onBrowse(void);

private:
    dtkComposerControlsListItemFilePrivate *d;
};




