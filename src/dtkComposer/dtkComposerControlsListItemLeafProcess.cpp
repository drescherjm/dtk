/* dtkComposerControlsListItemLeafProcess.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: jeu. oct. 10 16:19:35 2013 (+0200)
 * Version: 
 * Last-Updated: mar. oct. 15 16:17:51 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 456
 */

/* Change Log:
 * 
 */

#include "dtkComposerControlsListItemLeafProcess.h"
#include "dtkComposerNodeLeafProcess.h"

#include "dtkComposerExport.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractProcess.h>

#include <dtkGui/dtkPropertyEditorFactory.h>
#include <dtkGui/dtkPropertyEditor.h>

#include <QObject>
#include <QVariant>
#include <QMetaProperty>

class dtkComposerControlsListItemLeafProcessPrivate
{
public:
    dtkComposerControlsListItemLeafProcess *q;

public:
    QListWidget *parent;

public:
    dtkComposerSceneNode *node;

public:
    dtkComposerNodeLeafProcess *p_node;

public:
    QObject *object;

public:
    QList<QWidget *> widgets;

public:
    QList<QMetaProperty> enum_properties;

public:
    void clear(void);
};

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtkComposerControlsListItemLeafProcessPrivate::clear(void)
{
    foreach(QWidget *widget, widgets)
        delete widget;

    widgets.clear();

    enum_properties.clear();
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkComposerControlsListItemLeafProcess::dtkComposerControlsListItemLeafProcess(QListWidget *parent, dtkComposerSceneNode *node) : dtkComposerControlsListItem(parent,node), d(new dtkComposerControlsListItemLeafProcessPrivate)
{
    d->q = this;

    d->node = node;

    if (dtkComposerNodeLeafProcess *p_node = dynamic_cast<dtkComposerNodeLeafProcess *>(d->node->wrapee()))
        d->p_node = p_node;
    else
        dtkError() << Q_FUNC_INFO << "Can't create control list item of type Leaf Process.";

    d->parent = parent;
}


dtkComposerControlsListItemLeafProcess::~dtkComposerControlsListItemLeafProcess(void )
{
    delete d;
    d = NULL;
}

QWidget *dtkComposerControlsListItemLeafProcess::widget(void)
{
    d->object = d->p_node->process();
    if (!d->object)
        return dtkComposerControlsListItem::widget();

    if (d->p_node->implementationHasChanged())
        d->clear();

    QFrame *frame = new QFrame(d->parent);

    QFormLayout *layout = new QFormLayout;
    layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addRow(new QLabel(d->node->title(), frame));

    const QMetaObject *metaobject = d->object->metaObject();
    int count = metaobject->propertyCount();

    QWidget *editor;
    qDebug() << Q_FUNC_INFO << metaobject->className();
    if (metaobject->superClass())
        qDebug() << Q_FUNC_INFO << metaobject->superClass()->className();
    else
        qDebug() << Q_FUNC_INFO << "No superclass.";

    for (int i = 1; i < count; ++i) {
        const QMetaProperty& metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = d->object->property(name);

        editor = dtkPropertyEditorFactory::instance()->create(name, d->object, frame);
        d->widgets.append(editor);

        layout->addRow(new QLabel(QString(name).append(":"), frame));
        layout->addRow(editor);
    } 

    frame->setLayout(layout);
    return frame;
}


