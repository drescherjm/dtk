/* @(#)dtkComposerControlsListItemInteger.h ---
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

#ifndef DTKCOMPOSERCONTROLSLISTITEMINTEGER_H
#define DTKCOMPOSERCONTROLSLISTITEMINTEGER_H

#include <dtkComposerControlsListItem.h>

class dtkComposerSceneNode;
class dtkComposerControlsListItemIntegerPrivate;

class dtkComposerControlsListItemInteger: public dtkComposerControlsListItem
{

    Q_OBJECT

public:
    dtkComposerControlsListItemInteger(QListWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItemInteger(void);

public:
    QWidget *widget(void);

public slots:
    void onValueChanged(int value);

private:
    dtkComposerControlsListItemIntegerPrivate *d;
};

#endif




