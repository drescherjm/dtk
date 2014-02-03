/* dtkPropertyEditorFactory.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: mar. oct. 15 10:30:09 2013 (+0200)
 * Version: 
 * Last-Updated: lun. févr.  3 14:33:32 2014 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 256
 */

/* Change Log:
 * 
 */

#include "dtkPropertyEditorFactory.h"

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditorFactoryPrivate declaration
// ///////////////////////////////////////////////////////////////////

class dtkPropertyEditorFactoryPrivate
{
public:
    typedef QHash<int, dtkPropertyEditorFactory::dtkPropertyEditorCreator> dtkPropertyEditorCreatorHash;

public:
    dtkPropertyEditorCreatorHash creators;
};

// ///////////////////////////////////////////////////////////////////
// Forward declarations of creators (see dtkPropertyEditor.cpp for implementations).
// ///////////////////////////////////////////////////////////////////

dtkPropertyEditor DTKGUISUPPORT_EXPORT  *createDtkPropertyEditorDouble(const QString& property_name, QObject *object, QWidget *parent = 0);
dtkPropertyEditor DTKGUISUPPORT_EXPORT *createDtkPropertyEditorInteger(const QString& property_name, QObject *object, QWidget *parent = 0);
dtkPropertyEditor DTKGUISUPPORT_EXPORT  *createDtkPropertyEditorString(const QString& property_name, QObject *object, QWidget *parent = 0);
dtkPropertyEditor DTKGUISUPPORT_EXPORT    *createDtkPropertyEditorEnum(const QString& property_name, QObject *object, QWidget *parent = 0);

// ///////////////////////////////////////////////////////////////////
// dtkPropertyEditorFactory implementation
// ///////////////////////////////////////////////////////////////////

DTKGUISUPPORT_EXPORT dtkPropertyEditorFactory *dtkPropertyEditorFactory::instance(void)
{
    if(!s_instance) {
        s_instance = new dtkPropertyEditorFactory;
        
        s_instance->registerCreator(QMetaType::Double, createDtkPropertyEditorDouble);
        s_instance->registerCreator(QMetaType::Int, createDtkPropertyEditorInteger);
        s_instance->registerCreator(QMetaType::QString, createDtkPropertyEditorString);
        s_instance->registerCreator(-1 * static_cast<int>(QMetaType::Int), createDtkPropertyEditorEnum);
    }

    return s_instance;
}

dtkPropertyEditor *dtkPropertyEditorFactory::create(const QString& property_name, QObject *object, QWidget *parent)
{
    if (!object) {
        qDebug() << Q_FUNC_INFO << "Cannot create any dtkPropertyEditor for null object.";
        return NULL;
    }

    const QMetaObject *meta_object = object->metaObject();
    int id = meta_object->indexOfProperty(qPrintable(property_name));
    const QMetaProperty& meta_property = meta_object->property(id);
    int type = meta_property.userType();
    if (meta_property.isEnumType())
        type *= -1;

    if(!d->creators.contains(type))
        return NULL;

    return d->creators[type](property_name, object, parent);
}

QList<QWidget *> dtkPropertyEditorFactory::createObjectProperties(QObject *object, int hierarchy_level)
{    
    QList<QWidget *> list;

    if (!object) {
        qDebug() << Q_FUNC_INFO << "Cannot create any dtkPropertyEditor for null object.";
        return list;
    }

    const QMetaObject *meta_object = object->metaObject();

    int limit_level = 0;
    int offset = 0;
    while(meta_object && limit_level <= hierarchy_level) {
        meta_object = meta_object->superClass();
        ++limit_level;
        offset = meta_object->propertyCount();
    }

    meta_object = object->metaObject();
    int count = meta_object->propertyCount();
    QString name;
    for (int i = offset; i < count; ++i) {
        name = QString(meta_object->property(i).name());
        list << reinterpret_cast<QWidget *>(dtkPropertyEditorFactory::instance()->create(name, object, NULL));
    }

    return list;
}

bool dtkPropertyEditorFactory::registerCreator(int type, dtkPropertyEditorCreator func)
{
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        return true;
    }

    qDebug() << Q_FUNC_INFO << QString("Unable to create dtkPropertyEditor of type %1").arg(QMetaType::typeName(type));
    return false;
}

// ///////////////////////////////////////////////////////////////////

dtkPropertyEditorFactory::dtkPropertyEditorFactory(void) : QObject(), d(new dtkPropertyEditorFactoryPrivate)
{
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(clear()));
}

dtkPropertyEditorFactory::~dtkPropertyEditorFactory(void)
{
    delete d;

    d = NULL;
}

DTKGUISUPPORT_EXPORT dtkPropertyEditorFactory *dtkPropertyEditorFactory::s_instance = NULL;
