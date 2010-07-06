/* dtkAbstractObject.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:54:04 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  6 21:03:10 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 168
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkAbstractObjectPrivate
// /////////////////////////////////////////////////////////////////

class dtkAbstractObjectPrivate
{
public:
    int count;

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
    return d->count++;
}

//! Release reference count.
/*! 
 *  This method decrements the reference counter once. Should the
 *  count be null, the object is scheduled for deletion. Note it send
 *  the destroyed signal just before beeing actually deleted.
 */

int dtkAbstractObject::release(void)
{
    if(!(--(d->count)))
        this->deleteLater();

    return d->count;
}

void dtkAbstractObject::addProperty(QString key, QStringList values)
{
    d->values.insert(key, values);
}

void dtkAbstractObject::addProperty(QString key, QString value)
{
    d->values.insert(key, QStringList() << value);
}

void dtkAbstractObject::setProperty(QString key, QString value)
{
    if(!d->values.contains(key)) {
    	dtkDebug() << this->metaObject()->className() << "has no such property:" << key;
    	return;
    }

    if(!d->values.value(key).contains(value)) {
    	dtkDebug() << this->metaObject()->className() << "has no such value:" << value << "for key:" << key;
    	return;
    }

    d->properties.insert(key, value);

    onPropertySet(key, value);

    emit propertySet(key, value);
}

const QStringList dtkAbstractObject::propertyValues(QString key)
{
    if(d->values.contains(key))
	return d->values[key];

    return QStringList();
}

bool dtkAbstractObject::hasProperty(QString key)
{
    return d->values.contains(key);
}

QString dtkAbstractObject::property(QString key)
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

void dtkAbstractObject::addMetaData(QString key, QStringList values)
{
    QStringList currentValues = d->metadatas.value(key);

    d->metadatas.insert(key, currentValues + values);

    foreach(QString value, values)
        onMetaDataSet(key, value);

    foreach(QString value, values)
        emit metaDataSet(key, value);
}

void dtkAbstractObject::addMetaData(QString key, QString value)
{
    QStringList currentValues = d->metadatas.value(key);

    d->metadatas.insert(key, currentValues << value);

    onMetaDataSet(key, value);

    emit metaDataSet(key, value);
}

void dtkAbstractObject::setMetaData(QString key, QStringList values)
{
    d->metadatas.insert(key, values);

    foreach(QString value, values)
        onMetaDataSet(key, value);

    foreach(QString value, values)
        emit metaDataSet(key, value);
}

void dtkAbstractObject::setMetaData(QString key, QString value)
{
    d->metadatas.insert(key, QStringList() << value);

    onMetaDataSet(key, value);

    emit metaDataSet(key, value);
}

const QStringList dtkAbstractObject::metaDataValues(QString key)
{
    if(d->metadatas.contains(key))
	return d->metadatas[key];

    return QStringList();
}

bool dtkAbstractObject::hasMetaData(QString key)
{
    return d->metadatas.contains(key);
}

void dtkAbstractObject::onPropertySet(QString key, QString value)
{
    DTK_UNUSED(key);
    DTK_UNUSED(value);
}

void dtkAbstractObject::onMetaDataSet(QString key, QString value)
{
    DTK_UNUSED(key);
    DTK_UNUSED(value);
}

QString dtkAbstractObject::metadata(QString key)
{
    if(!d->metadatas.contains(key)) {
	dtkDebug() << this->metaObject()->className() << "has no such property:" << key;
	return QString();
    }

    return d->metadatas.value(key).first();
}

QStringList dtkAbstractObject::metadatas(QString key)
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
