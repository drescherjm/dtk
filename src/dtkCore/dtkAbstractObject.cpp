/* dtkAbstractObject.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:54:04 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 15:23:37 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 86
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkLog.h>

class dtkAbstractObjectPrivate
{
public:
    QHash<QString, QStringList> values;
    QHash<QString, QString> properties;

    QHash<QString, QStringList> metadatas;
};

dtkAbstractObject::dtkAbstractObject(dtkAbstractObject *parent) : QObject(parent), d(new dtkAbstractObjectPrivate)
{

}

dtkAbstractObject::~dtkAbstractObject(void)
{
    delete d;

    d = NULL;
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
        emit propertySet(key, value);
}

void dtkAbstractObject::addMetaData(QString key, QString value)
{
    QStringList currentValues = d->metadatas.value(key);

    d->metadatas.insert(key, currentValues << value);

    onMetaDataSet(key, value);

    emit propertySet(key, value);
}

void dtkAbstractObject::setMetaData(QString key, QStringList values)
{
    d->metadatas.insert(key, values);

    foreach(QString value, values)
        onMetaDataSet(key, value);

    foreach(QString value, values)
        emit propertySet(key, value);
}

void dtkAbstractObject::setMetaData(QString key, QString value)
{
    d->metadatas.insert(key, QStringList() << value);

    onMetaDataSet(key, value);

    emit propertySet(key, value);
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

QString dtkAbstractObject::name(void) const
{
    return this->objectName();
}

dtkComposerNode *dtkAbstractObject::node(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}

QWidget *dtkAbstractObject::ui(void)
{
    DTK_DEFAULT_IMPLEMENTATION;

    return NULL;
}


void dtkAbstractObject::onPropertySet(QString key, QString value)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(key);
    DTK_UNUSED(value);
}

void dtkAbstractObject::onMetaDataSet(QString key, QString value)
{
    DTK_DEFAULT_IMPLEMENTATION;
    DTK_UNUSED(key);
    DTK_UNUSED(value);
}
