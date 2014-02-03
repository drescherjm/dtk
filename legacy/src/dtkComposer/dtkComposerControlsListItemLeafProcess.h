/* dtkComposerControlsListItemLeafProcess.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: jeu. oct. 10 16:18:27 2013 (+0200)
 * Version: 
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerControlsListItem.h"

class dtkComposerSceneNode;
class dtkComposerControlsListItemLeafProcessPrivate;

class dtkComposerControlsListItemLeafProcess: public dtkComposerControlsListItem
{
    Q_OBJECT

public:
             dtkComposerControlsListItemLeafProcess(QListWidget *parent = 0, dtkComposerSceneNode *node = NULL);
    virtual ~dtkComposerControlsListItemLeafProcess(void);

public:
    QWidget *widget(void);

private:
    dtkComposerControlsListItemLeafProcessPrivate *d;
};





