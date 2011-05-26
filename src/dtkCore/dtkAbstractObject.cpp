/* dtkAbstractObject.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:54:04 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May 23 12:27:36 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 180
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkLog.h>

#include <QAtomicInt>

// /////////////////////////////////////////////////////////////////
// dtkAbstractObjectPrivate
// /////////////////////////////////////////////////////////////////

class dtkAbstractObjectPrivate
{
public:
    QAtomicInt count;

    QHash<QString, QStringList> values;
    QHash<QString, QString> properties;

    QHash<QString, QStringList> metadatas;
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractObject
// /////////////////////////////////////////////////////////////////

//! Constructs an object with parent \a parent
/*! 
 *  The parent of an object may be viewed as the object's owner. The
 *  destructor of a parent object destroys all child objects. Setting
 *  parent to 0 constructs an object with no parent.
 */

dtkAbstractObject::dtkAbstractObject(dtkAbstractObject *parent) : QObject(parent), d(new dtkAbstractObjectPrivate)
{
    d->count = 1;
}

//! Destroys the object, deleting all its child objects.
/*! 
 *  
 */

dtkAbstractObject::~dtkAbstractObject(void)
{
    delete d;

    d = NULL;
}

QString dtkAbstractObject::name(void) const
{
    return this->objectName();
}

//! Reference count.
/*! 
 *  Returns the current reference count.
 */

int dtkAbstractObject::count(void)
{
    return d->count;
}

//! Retain reference count.
/*! 
 *  This method increments the reference counter once.
 */

int dtkAbstractObject::retain(void)
{
    return d->count.fetchAndAddOrdered ( 1 ) + 1;
}

//! Release reference count.
/*! 
 *  This method decrements the reference counter once. Should the
 *  count be null, the object is scheduled for deletion. Note it send
 *  the destroyed signal just before beeing actually deleted.
 */

int dtkAbstractObject::release(void)
{
    int newCount = d->count.fetchAndAddOrdered ( -1 ) - 1;

    if(!(newCount))
        this->deleteLater();

    return newCount;
}

void dtkAbstractObject::addProperty(const QString& key, const QStringList& values)
{
    d->values.insert(key, values);
}

void dtkAbstractObject::addProperty(const QString& key, const QString& value)
{
    d->values.insert(key, QStringList() << value);
}

void dtkAbstractObject::setProperty(const QString& key, const QString& value)
{
    if(!d->values.contains(key)) {
    	dtkDebug() << this->metaObject()->className() << " has no such property:" << key;
    	return;
    }

    if(!d->values.value(key).contains(value)) {
    	dtkDebug() << this->metaObject()->className() << " has no such value:" << value << " for key: " << key;
    	return;
    }

    d->properties.insert(key, value);

    onPropertySet(key, value);

    emit propertySet(key, value);
}

QStringList dtkAbstractObject::propertyList(void) const
{
    return d->properties.keys();
}

QStringList dtkAbstractObject::propertyValues(const QString& key) const
{
    if(d->values.contains(key))
	return d->values[key];

    return QStringList();
}

bool dtkAbstractObject::hasProperty(const QString& key) const
{
    return d->values.contains(key);
}

QString dtkAbstractObject::property(const QString& key) const
{
    if(!d->values.contains(key)) {
	dtkDebug() << this->metaObject()->className() << "has no such property:" << key;
	return QString();
    }

    return d->properties.value(key);
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

void dtkAbstractObject::addMetaData(const QString& key, const QStringList& values)
{
    QStringList currentValues = d->metadatas.value(key);

    d->metadatas.insert(key, currentValues + values);

    foreach(QString value, values)
        onMetaDataSet(key, value);

    foreach(QString value, values)
        emit metaDataSet(key, value);
}

void dtkAbstractObject::addMetaData(const QString& key, const QString& value)
{
    QStringList currentValues = d->metadatas.value(key);

    d->metadatas.insert(key, currentValues << value);

    onMetaDataSet(key, value);

    emit metaDataSet(key, value);
}

void dtkAbstractObject::setMetaData(const QString& key, const QStringList& values)
{
    d->metadatas.insert(key, values);

    foreach(QString value, values)
        onMetaDataSet(key, value);

    foreach(QString value, values)
        emit metaDataSet(key, value);
}

void dtkAbstractObject::setMetaData(const QString& key, const QString& value)
{
    d->metadatas.insert(key, QStringList() << value);

    onMetaDataSet(key, value);

    emit metaDataSet(key, value);
}

QStringList dtkAbstractObject::metaDataList(void) const
{
    return d->metadatas.keys();
}

QStringList dtkAbstractObject::metaDataValues(const QString& key) const
{
    if(d->metadatas.contains(key))
	return d->metadatas[key];

    return QStringList();
}

bool dtkAbstractObject::hasMetaData(const QString& key) const
{
    return d->metadatas.contains(key);
}

void dtkAbstractObject::onPropertySet(const QString& key, const QString& value)
{
    DTK_UNUSED(key);
    DTK_UNUSED(value);
}

void dtkAbstractObject::onMetaDataSet(const QString& key, const QString& value)
{
    DTK_UNUSED(key);
    DTK_UNUSED(value);
}

QString dtkAbstractObject::metadata(const QString& key) const
{
    if(!d->metadatas.contains(key)) {
	dtkDebug() << this->metaObject()->className() << "has no such property:" << key;
	return QString();
    }

    return d->metadatas.value(key).first();
}

QStringList dtkAbstractObject::metadatas(const QString& key) const
{
    if(!d->metadatas.contains(key)) {
	dtkDebug() << this->metaObject()->className() << "has no such property:" << key;
	return QStringList();
    }

    return d->metadatas.value(key);
}

// /////////////////////////////////////////////////////////////////
// dtkAbstractObject documentation
// /////////////////////////////////////////////////////////////////

/*! \class dtkAbstractObject 
 *
 *  \brief The dtkAbstractObject is the base class of all dtk abstract
 *  concepts.
 *
 *  The dtkAbstractObject is the root of the data, process and view
 *  taxomonies. It provides two main functionalities: a property
 *  system and a meta data system.
 *
 *  A property is a key that can correspond to a predefined set of
 *  values. It is no possible to assign a value that has not been
 *  declared together with the property. A property has a unique
 *  value.
 * 
 *  \code
 *  object->addProperty("key", QStringList() << "value1" << "value2");
 *  object->setProperty("key", "value3");   // Wrong, "value3" has not been assigned to "key".
 *  object->setProperty("key", "value1");   // Right, "value1" has been assigned to "key".
 *  \endcode
 *
 *  The previous code snippet emits the signal propertySet and calls
 *  the virtual method onPropertySet so that one can override its
 *  behaviour when specializing any dtk concept.
 *
 *  A meta data is somehow similar to a property except that there is
 *  no constraint for the values one can assign to it. Also, a meta
 *  data is not unique, one can assign many values to it.
 *
 *  \code
 *  object->addMetaData("key", QStringList() << "value1" << "value2");
 *  object->setMetaData("key", "value3");   // Right, "value3" is now mapped to "key".
 *  object->setMetaData("key", "value4");   // Right, "value4" is now mapped to "key".
 *  object->addMetaData("key", QStringList() << "value1" << "value2");
 *   
 *  dtkOutput() << object->metaData("key"); // ("value4", "value1", "value2")
 *  \endcode
 *
 *  The previous code snippet emits the signal metaDataSet and calls
 *  the virtual method onMetaDataSet so that one can override its
 *  behaviour when specializing any dtk concept.
 */
