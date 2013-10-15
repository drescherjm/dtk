/* dtkComposerControlsListItemLeafProcess.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: jeu. oct. 10 16:19:35 2013 (+0200)
 * Version: 
 * Last-Updated: mar. oct. 15 22:48:09 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 540
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
    QFrame *frame;
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

    d->frame = NULL;
}


dtkComposerControlsListItemLeafProcess::~dtkComposerControlsListItemLeafProcess(void )
{
    delete d;
    d = NULL;
}

QWidget *dtkComposerControlsListItemLeafProcess::widget(void)
{
    if (d->frame && !(d->p_node->implementationHasChanged()))
        return d->frame;

    if (d->frame)
        delete d->frame;

    d->frame = new QFrame(d->parent);

    QVBoxLayout *layout = new QVBoxLayout(d->frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(new QLabel(d->node->title(), d->frame));

    QObject *object = d->p_node->process();
    if (object)
        layout->addWidget(new dtkObjectEditor(object, d->frame));

    return d->frame;
}


