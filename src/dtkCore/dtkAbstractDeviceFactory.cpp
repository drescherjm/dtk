/* dtkAbstractDeviceFactory.cpp --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2009 - Jean-Christophe Lombardo, Inria
 * Created: Fri Mar 20 17:08:27 2009
 * Version: $Id$
 * Last-Updated: Sat Aug  1 00:01:12 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractDevice.h>
#include <dtkCore/dtkAbstractDeviceFactory.h>

typedef QHash<QString, dtkAbstractDevice*>    Hash;
typedef QHash<QString, Hash> dtkAbstractDeviceHash;

class dtkAbstractDeviceFactoryPrivate
{
public:
    dtkAbstractDeviceHash data;

    dtkAbstractDeviceFactory::dtkAbstractDeviceCreatorMap creators;
};

dtkAbstractDeviceFactory *dtkAbstractDeviceFactory::instance(void)
{
    if(!s_instance)
        s_instance = new dtkAbstractDeviceFactory;

    return s_instance;
}

dtkAbstractDevice *dtkAbstractDeviceFactory::create(QString type, QString name)
{
    if(!d->creators.contains(type)) return NULL;

    dtkAbstractDevice *data = d->creators[type](name);

    d->data[type][name]=data;

    return data;
}

bool dtkAbstractDeviceFactory::registerDeviceType(QString type, dtkAbstractDeviceCreator func)
{
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        return true;
    }
 
    return false;
}

QString dtkAbstractDeviceFactory::names(QString type)
{
    QString result;

    Hash::const_iterator it;
    for (it = d->data[type].begin(); it != d->data[type].end(); ++it)
        result += it.key() + " ";

    return result;
}

dtkAbstractDevice *dtkAbstractDeviceFactory::get(QString type, QString name)
{
    dtkAbstractDeviceHash::iterator it = d->data.find(type);

    if (it != d->data.end()) {
        QHash<QString, dtkAbstractDevice*>::iterator it2 = it.value().find(name);
        if (it2 != it.value().end()) return it2.value();
    }
    
    return 0l;
}

dtkAbstractDeviceFactory::dtkAbstractDeviceFactory(void) : dtkAbstractFactory(), d(new dtkAbstractDeviceFactoryPrivate)
{

}

dtkAbstractDeviceFactory::~dtkAbstractDeviceFactory(void)
{
    foreach(Hash  hash, d->data.values()) 
        foreach(dtkAbstractDevice *device, hash.values())
            delete device;

    delete d;

    d = NULL;
}

dtkAbstractDeviceFactory *dtkAbstractDeviceFactory::s_instance = NULL;
