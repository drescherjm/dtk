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

#ifndef DTKCOMPOSERCONTROLSLISTITEM_H
#define DTKCOMPOSERCONTROLSLISTITEM_H

#include "dtkComposerSceneNode.h"

#include <QtGui>

class dtkComposerControlsListItemPrivate;

class dtkComposerControlsListItem : public QObject, public QListWidgetItem
{
    Q_OBJECT

public:
    dtkComposerControlsListItem(QListWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItem(void);

public:
    virtual QWidget *widget(void);

public:
    dtkComposerSceneNode *node(void);

private:
    dtkComposerControlsListItemPrivate *d;
};

#endif




