/* dtkAbstractDataFactory.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May 23 11:46:44 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 126
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// Anonymous namespace declarations
// /////////////////////////////////////////////////////////////////

namespace {

    typedef QHash<QString, QList<dtkAbstractData*> > dtkAbstractDataHash;

    struct dtkAbstractDataReaderInfo { 
        dtkAbstractDataReaderInfo() : creator(NULL) {}
        dtkAbstractDataReaderInfo(const QStringList& _handled, dtkAbstractDataFactory::dtkAbstractDataReaderCreator _creator) : handled(_handled) , creator(_creator) {}
        QStringList handled; 
        dtkAbstractDataFactory::dtkAbstractDataReaderCreator creator; 
    };

    struct dtkAbstractDataWriterInfo { 
        dtkAbstractDataWriterInfo() : creator(NULL) {}
        dtkAbstractDataWriterInfo(const QStringList& _handled, dtkAbstractDataFactory::dtkAbstractDataWriterCreator _creator) : handled(_handled) , creator(_creator) {}
        QStringList handled; 
        dtkAbstractDataFactory::dtkAbstractDataWriterCreator creator; 
    };

    struct dtkAbstractDataConverterInfo { 
        dtkAbstractDataConverterInfo() : creator(NULL) {}
        dtkAbstractDataConverterInfo(const QStringList& _fromTypes, const QString& _toType, dtkAbstractDataFactory::dtkAbstractDataConverterCreator _creator)
            : fromTypes(_fromTypes) , toType(_toType), creator(_creator) {}
        QStringList fromTypes; 
        QString toType; 
        dtkAbstractDataFactory::dtkAbstractDataConverterCreator creator; 
    };

    typedef QHash<QString, dtkAbstractDataFactory::dtkAbstractDataCreator> dtkAbstractDataCreatorHash;
    typedef QHash<QString, dtkAbstractDataReaderInfo> dtkAbstractDataReaderCreatorHash;
    typedef QHash<QString, dtkAbstractDataWriterInfo> dtkAbstractDataWriterCreatorHash;
    typedef QHash<QString, dtkAbstractDataConverterInfo> dtkAbstractDataConverterCreatorHash;

    typedef QPair<QString, QStringList>  dtkAbstractDataTypeHandler;
    typedef QPair<QString, QPair<QStringList, QString> > dtkAbstractDataConverterTypeHandler;

}

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataFactoryPrivate
// /////////////////////////////////////////////////////////////////

class dtkAbstractDataFactoryPrivate
{
public:
    dtkAbstractDataCreatorHash          creators;
    dtkAbstractDataReaderCreatorHash    readers;
    dtkAbstractDataWriterCreatorHash    writers;
    dtkAbstractDataConverterCreatorHash converters;
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataFactory
// /////////////////////////////////////////////////////////////////

DTKCORE_EXPORT dtkAbstractDataFactory *dtkAbstractDataFactory::instance(void)
{
    if(!s_instance)
	s_instance = new dtkAbstractDataFactory;

    return s_instance;
}

dtkAbstractData *dtkAbstractDataFactory::create(const QString& type)
{
    static int count = 0;

    if(!d->creators.contains(type))
	return NULL;

    dtkAbstractData *data = d->creators[type]();

    for(dtkAbstractDataReaderCreatorHash::const_iterator it(d->readers.begin() ); it != d->readers.end(); ++it) {
        if(it.value().handled.contains(type))
            data->addReader(it.key());
    }

    for(dtkAbstractDataWriterCreatorHash::const_iterator it(d->writers.begin() ); it != d->writers.end(); ++it) {
        if(it.value().handled.contains(type))
            data->addWriter(it.key());
    }

    for(dtkAbstractDataConverterCreatorHash::const_iterator it(d->converters.begin() ); it != d->converters.end(); ++it) {
        if(it.value().fromTypes.contains(type))
            data->addConverter(it.key());
    }

    data->setObjectName(QString("%1%2").arg(data->metaObject()->className()).arg(count++));

    emit created(data, type);

    return data;
}

dtkAbstractDataReader *dtkAbstractDataFactory::reader(const QString& type)
{
    dtkAbstractDataReaderCreatorHash::const_iterator it(d->readers.find(type));

    if (it == d->readers.end()) 
        return NULL;
    else
        return it->creator();
}

dtkAbstractDataWriter *dtkAbstractDataFactory::writer(const QString& type)
{
    dtkAbstractDataWriterCreatorHash::const_iterator it(d->writers.find(type));

    if (it == d->writers.end()) 
        return NULL;
    else
        return it->creator();
}

dtkAbstractDataConverter *dtkAbstractDataFactory::converter(const QString& type)
{
    dtkAbstractDataConverterCreatorHash::const_iterator it(d->converters.find(type));

    if (it == d->converters.end())
        return NULL;
    else
        return it->creator();
}

bool dtkAbstractDataFactory::registerDataType(const QString& type, dtkAbstractDataCreator func)
{
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        return true;
    }

    return false;
}

bool dtkAbstractDataFactory::registerDataReaderType(const QString& type, const QStringList& handled, dtkAbstractDataReaderCreator func)
{
    if(!d->readers.contains(type) ) {
        d->readers.insert(type, dtkAbstractDataReaderInfo(handled, func) );
        return true;
    }

    return false;
}

bool dtkAbstractDataFactory::registerDataWriterType(const QString& type, const QStringList& handled, dtkAbstractDataWriterCreator func)
{
    if(!d->writers.contains(type) ) {
        d->writers.insert(type, dtkAbstractDataWriterInfo( handled, func) );
        return true;
    }

    return false;
}

bool dtkAbstractDataFactory::registerDataConverterType(const QString& type, const QStringList& fromTypes, const QString& toType, dtkAbstractDataConverterCreator func)
{
    if(!d->converters.contains(type) ) {
        d->converters.insert(type, dtkAbstractDataConverterInfo(fromTypes, toType, func) );
        return true;
    }

    return false;
}


unsigned int dtkAbstractDataFactory::count(const QString& type) const
{
    return d->creators.keys().count();
}

unsigned int dtkAbstractDataFactory::countReaders(const QString& type) const
{
    return d->readers.keys().count();
}

unsigned int dtkAbstractDataFactory::countWriters(const QString& type) const
{
    return d->writers.keys().count();
}

unsigned int dtkAbstractDataFactory::countConverters(const QString& type) const
{
    return d->converters.keys().count();
}

QList<QString> dtkAbstractDataFactory::creators(void) const
{
    return d->creators.keys();
}

QList<QString> dtkAbstractDataFactory::readers(void) const
{
    return d->readers.keys();
}

QList<QString> dtkAbstractDataFactory::writers(void) const
{
    return d->writers.keys();
}

QList<QString> dtkAbstractDataFactory::converters(void) const
{
    return d->converters.keys();
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
