/* dtkAbstractDataFactory.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Oct  5 14:23:19 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 95
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

typedef QHash<QString, QList<dtkAbstractData*> > dtkAbstractDataHash;

class dtkAbstractDataFactoryPrivate
{
public:
    dtkAbstractDataHash datas;

    dtkAbstractDataFactory::dtkAbstractDataCreatorHash       creators;
    dtkAbstractDataFactory::dtkAbstractDataReaderCreatorHash readers;
    dtkAbstractDataFactory::dtkAbstractDataWriterCreatorHash writers;
};

DTKCORE_EXPORT dtkAbstractDataFactory *dtkAbstractDataFactory::instance(void)
{
    if(!s_instance)
	s_instance = new dtkAbstractDataFactory;

    return s_instance;
}

dtkAbstractData *dtkAbstractDataFactory::create(QString type)
{
    static int count = 0;

    if(!d->creators.contains(type))
	return NULL;

    dtkAbstractData *data = d->creators[type]();

    foreach(dtkAbstractDataTypeHandler key, d->readers.keys())
	if(key.second.contains(type))
	    data->addReader(d->readers[key]());

    foreach(dtkAbstractDataTypeHandler key, d->writers.keys())
	if(key.second.contains(type))
	    data->addWriter(d->writers[key]());

    data->setObjectName(QString("data%1").arg(count++));

    d->datas[type] << data;

    emit created(data, type);

    return data;
}

dtkAbstractDataReader *dtkAbstractDataFactory::reader(QString type, QStringList handled)
{
    return d->readers[qMakePair(type, handled)]();
}

dtkAbstractDataWriter *dtkAbstractDataFactory::writer(QString type, QStringList handled)
{
    return d->writers[qMakePair(type, handled)]();
}

bool dtkAbstractDataFactory::registerDataType(QString type, dtkAbstractDataCreator func)
{
    if(!d->creators.contains(type)) {
	d->creators.insert(type, func);
	return true;
    }

    return false;
}

bool dtkAbstractDataFactory::registerDataReaderType(QString type, QStringList handled, dtkAbstractDataReaderCreator func)
{
    if(!d->readers.contains(qMakePair(type, handled))) {
	d->readers.insert(qMakePair(type, handled), func);
	return true;
    }

    return false;
}

bool dtkAbstractDataFactory::registerDataWriterType(QString type, QStringList handled, dtkAbstractDataWriterCreator func)
{
    if(!d->writers.contains(qMakePair(type, handled))) {
	d->writers.insert(qMakePair(type, handled), func);
	return true;
    }

    return false;
}

unsigned int dtkAbstractDataFactory::size(QString type)
{
    return d->datas[type].size();
}

unsigned int dtkAbstractDataFactory::count(QString type)
{
    return d->creators.keys().count();
}

unsigned int dtkAbstractDataFactory::countReaders(QString type)
{
    return d->readers.keys().count();
}

unsigned int dtkAbstractDataFactory::countWriters(QString type)
{
    return d->writers.keys().count();
}

dtkAbstractData *dtkAbstractDataFactory::get(QString type, int idx)
{
    return d->datas[type].value(idx);
}

dtkAbstractData *dtkAbstractDataFactory::get(QString type, QString name)
{
    foreach(dtkAbstractData *data, d->datas[type])
        if(data->name() == name)
            return data;

    return NULL;
}

QList<dtkAbstractDataFactory::dtkAbstractDataTypeHandler> dtkAbstractDataFactory::readers(void)
{
    return d->readers.keys();
}

QList<dtkAbstractDataFactory::dtkAbstractDataTypeHandler> dtkAbstractDataFactory::writers(void)
{
    return d->writers.keys();
}

dtkAbstractDataFactory::dtkAbstractDataFactory(void) : dtkAbstractFactory(), d(new dtkAbstractDataFactoryPrivate)
{

}

dtkAbstractDataFactory::~dtkAbstractDataFactory(void)
{
    delete d;

    d = NULL;
}

dtkAbstractDataFactory *dtkAbstractDataFactory::s_instance = NULL;
