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

#ifndef DTKCOMPOSERCONTROLSLISTITEMFILE_H
#define DTKCOMPOSERCONTROLSLISTITEMFILE_H

#include <dtkComposerExport.h>
#include "dtkComposerControlsListItem.h"

#include <QtGui>

class dtkComposerSceneNode;
class dtkComposerControlsListItemFilePrivate;

class dtkComposerControlsListItemFile: public dtkComposerControlsListItem
{

    Q_OBJECT

public:
    dtkComposerControlsListItemFile(QListWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItemFile(void);

public:
    QWidget *widget(void);

public slots:
    void onValueChanged(const QString& value);
    void onBrowse(const QString& value);
    void onBrowse(void);

private:
    dtkComposerControlsListItemFilePrivate *d;
};

#endif




