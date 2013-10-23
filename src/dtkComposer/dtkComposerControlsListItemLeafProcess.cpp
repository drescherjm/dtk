/* dtkComposerControlsListItemLeafProcess.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: jeu. oct. 10 16:19:35 2013 (+0200)
 * Version: 
 * Last-Updated: mer. oct. 23 17:05:20 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 577
 */

/* Change Log:
 * 
 */

#include "dtkComposerControlsListItemLeafProcess.h"
#include "dtkComposerNodeLeafProcess.h"

#include "dtkComposerExport.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractProcess.h>

#include <dtkGui/dtkObjectEditor.h>
#include <dtkGui/dtkToolBox.h>

#include <QObject>
#include <QVariant>
#include <QMetaProperty>

class dtkComposerControlsListItemLeafProcessPrivate
{
public:
    QListWidget *parent;

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeLeafProcess *p_node;

public:
    dtkToolBox *box;
    dtkToolBoxItem *item;
};

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkComposerControlsListItemLeafProcess::dtkComposerControlsListItemLeafProcess(QListWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent,node), d(new dtkComposerControlsListItemLeafProcessPrivate)
{
    d->node = node;

    if (dtkComposerNodeLeafProcess *p_node = dynamic_cast<dtkComposerNodeLeafProcess *>(d->node->wrapee()))
        d->p_node = p_node;
    else
        dtkError() << Q_FUNC_INFO << "Can't create control list item of type Leaf Process.";

    d->parent = parent;

    d->box = new dtkToolBox(d->parent);
    d->item = NULL;
}


dtkComposerControlsListItemLeafProcess::~dtkComposerControlsListItemLeafProcess(void )
{
    delete d;
    d = NULL;
}

QWidget *dtkComposerControlsListItemLeafProcess::widget(void)
{
    if (d->item && !(d->p_node->implementationHasChanged()))
        return d->box;

    if (d->item)
        delete d->item;

    QObject *object = d->p_node->process();
    if (object) {
        d->item = dtkToolBoxItem::fromObject(object);
        d->box->appendItem(d->item);
    }

    return d->box;
}


