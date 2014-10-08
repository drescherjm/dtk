/* dtkComposerControlsListItemLeafProcess.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: jeu. oct. 10 16:19:35 2013 (+0200)
 * Version: 
 * Last-Updated: lun. juin 16 16:32:08 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 613
 */

/* Change Log:
 * 
 */

#include "dtkComposerControlsListItemLeafProcess.h"

#include "dtkComposerSceneNode.h"
#include "dtkComposerNodeLeafProcess.h"

#include <dtkLog>

class dtkComposerControlsListItemLeafProcessPrivate
{
public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeLeafProcess *p_node;
};

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkComposerControlsListItemLeafProcess::dtkComposerControlsListItemLeafProcess(QWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent, node), d(new dtkComposerControlsListItemLeafProcessPrivate)
{
    d->node = node;

    if (dtkComposerNodeLeafProcess *p_node = dynamic_cast<dtkComposerNodeLeafProcess *>(d->node->wrapee())) {
        d->p_node = p_node;
    } else {
        dtkError() << Q_FUNC_INFO << "Can't create control list item of type Leaf Process.";
    }
}


dtkComposerControlsListItemLeafProcess::~dtkComposerControlsListItemLeafProcess(void )
{
    delete d;
    d = NULL;
}


