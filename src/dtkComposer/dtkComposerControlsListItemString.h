/* @(#)dtkComposerControlsListItemString.h ---
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

#ifndef DTKCOMPOSERCONTROLSLISTITEMSTRING_H
#define DTKCOMPOSERCONTROLSLISTITEMSTRING_H

#include <dtkComposerControlsListItem.h>

class dtkComposerSceneNode;
class dtkComposerControlsListItemStringPrivate;

class dtkComposerControlsListItemString: public dtkComposerControlsListItem
{

    Q_OBJECT

public:
    dtkComposerControlsListItemString(QListWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItemString(void);

public:
    QWidget *widget(void);

public slots:
    void onValueChanged(QString value);

private:
    dtkComposerControlsListItemStringPrivate *d;
};

#endif




