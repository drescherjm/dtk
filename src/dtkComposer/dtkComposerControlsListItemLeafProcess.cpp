/* dtkComposerControlsListItemLeafProcess.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: jeu. oct. 10 16:19:35 2013 (+0200)
 * Version: 
 * Last-Updated: ven. oct. 11 15:39:21 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 381
 */

/* Change Log:
 * 
 */

#include "dtkComposerControlsListItemLeafProcess.h"
#include "dtkComposerNodeLeafProcess.h"

#include "dtkComposerExport.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractProcess.h>

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

public:
    QWidget *createDoubleSpinBox(const QString& property_name, QWidget *parent);
    QWidget       *createSpinBox(const QString& property_name, QWidget *parent);
    QWidget      *createLineEdit(const QString& property_name, QWidget *parent);

public:
    QWidget *createEnumList(const QMetaProperty& meta_property, QWidget *parent);
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

QWidget *dtkComposerControlsListItemLeafProcessPrivate::createDoubleSpinBox(const QString& property_name, QWidget *parent)
{
    QDoubleSpinBox *spin_d = new QDoubleSpinBox(parent);
    spin_d->setObjectName(property_name);
    spin_d->setMinimum(-9999999);
    spin_d->setMaximum(+9999999);
    spin_d->setDecimals(14);
    spin_d->setSingleStep(1);
    spin_d->setEnabled(true);
    spin_d->setValue(object->property(property_name.toLatin1().constData()).toDouble());
    
    QObject::connect(spin_d, SIGNAL(valueChanged(double)), q, SLOT(onValueChanged(double)));
    
    widgets.append(spin_d);

    return spin_d;
}

QWidget *dtkComposerControlsListItemLeafProcessPrivate::createSpinBox(const QString& property_name, QWidget *parent)
{
    QSpinBox *spin = new QSpinBox(parent);
    spin->setObjectName(property_name);
    spin->setMinimum(-999999999);
    spin->setMaximum(+999999999);
    spin->setSingleStep(1);
    spin->setEnabled(true);
    spin->setValue(object->property(property_name.toLatin1().constData()).toLongLong());
    
    QObject::connect(spin, SIGNAL(valueChanged(int)), q, SLOT(onValueChanged(int)));
    
    widgets.append(spin);

    return spin;
}

QWidget *dtkComposerControlsListItemLeafProcessPrivate::createLineEdit(const QString& property_name, QWidget *parent)
{
    QLineEdit *edit = new QLineEdit(parent);
    edit->setObjectName(property_name);
    edit->setEnabled(true);
    edit->setText(object->property(property_name.toLatin1().constData()).toString());
    
    QObject::connect(edit, SIGNAL(textChanged(QString)), q, SLOT(onTextChanged(QString)));
    
    widgets.append(edit);

    return edit;
}

QWidget *dtkComposerControlsListItemLeafProcessPrivate::createEnumList(const QMetaProperty& meta_property, QWidget *parent)
{
    QComboBox *list = new QComboBox(parent);
    list->setObjectName(meta_property.name());
    list->setEnabled(true);

    QMetaEnum meta_enum = meta_property.enumerator();
    int count = meta_enum.keyCount();
    for (int i = 0; i < count; ++i) {
        list->addItem(meta_enum.key(i));
    }
    
    QObject::connect(list, SIGNAL(currentIndexChanged(int)), q, SLOT(onEnumChanged(int)));

    widgets.append(list);

    return list;
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

    for (int i = 1; i < count; ++i) {
        const QMetaProperty& metaproperty = metaobject->property(i);
        const char *name = metaproperty.name();
        QVariant value = d->object->property(name);

        if (!metaproperty.isEnumType()) {

            switch (value.type()) {

            case QMetaType::Double:
                layout->addRow(new QLabel(QString(name).append(":"), frame));
                layout->addRow(d->createDoubleSpinBox(name, frame));
                break;

            case QMetaType::LongLong:
            case QMetaType::Int:
                layout->addRow(new QLabel(QString(name).append(":"), frame));
                layout->addRow(d->createSpinBox(name, frame));
                break;
                
            case QMetaType::QString:
                layout->addRow(new QLabel(QString(name).append(":"), frame));
                layout->addRow(d->createLineEdit(name, frame));

            default:
                qDebug() << Q_FUNC_INFO << value;
                break;
            }
        } else {
            
            layout->addRow(new QLabel(QString(name).append(":"), frame));
            layout->addRow(d->createEnumList(metaproperty, frame));

        }
    } 

    frame->setLayout(layout);
    return frame;
}

void dtkComposerControlsListItemLeafProcess::onValueChanged(double value)
{
    if (!d->object)
        return;

    const char *name = QObject::sender()->objectName().toLatin1().constData();
    d->object->setProperty(name, QVariant::fromValue(value));
}

void dtkComposerControlsListItemLeafProcess::onValueChanged(int value)
{
    if (!d->object)
        return;

    const char *name = QObject::sender()->objectName().toLatin1().constData();
    d->object->setProperty(name, QVariant::fromValue(value));
}

void dtkComposerControlsListItemLeafProcess::onTextChanged(const QString& text)
{
    if (!d->object)
        return;

    const char *name = QObject::sender()->objectName().toLatin1().constData();
    d->object->setProperty(name, QVariant::fromValue(text));
}

void dtkComposerControlsListItemLeafProcess::onEnumChanged(int index)
{
    if (!d->object)
        return;

    const char *name = QObject::sender()->objectName().toLatin1().constData();

    const QMetaObject *meta_object = d->object->metaObject();
    int id = meta_object->indexOfProperty(name);
    const QMetaEnum& meta_enum = meta_object->property(id).enumerator();

    int value = meta_enum.value(index);
    d->object->setProperty(name, QVariant::fromValue(value));
}


