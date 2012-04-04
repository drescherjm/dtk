/* dtkAbstractProcessFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 08:46:39 2012 (+0200)
 *           By: tkloczko
 *     Update #: 116
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkSmartPointer.h>

#include <dtkLog/dtkLog.h>

class dtkAbstractProcessFactoryPrivate
{
public:
    typedef QHash<QString, dtkAbstractProcessFactory::dtkAbstractProcessCreator> dtkAbstractProcessCreatorHash;
    typedef QHash<QString, QString> dtkAbstractProcessInterfacesHash;
    typedef QHash<QString, unsigned int> dtkAbstractProcessCountHash;

    dtkAbstractProcessInterfacesHash interfaces;
    dtkAbstractProcessCreatorHash creators;
    dtkAbstractProcessCountHash processCount;
};

dtkAbstractProcessFactory *dtkAbstractProcessFactory::instance(void)
{
    if(!s_instance)
        s_instance = new dtkAbstractProcessFactory;

    return s_instance;
}

dtkAbstractProcess *dtkAbstractProcessFactory::create(const QString& type)
{
    if(!d->creators.contains(type))
        return NULL;

    dtkAbstractProcess *process = d->creators[type]();

    process->setObjectName(QString("%1%2").arg(process->metaObject()->className()).arg(d->processCount[type]));

    d->processCount[type]++;

    emit created(process, type);

    return process;
}

dtkSmartPointer<dtkAbstractProcess> dtkAbstractProcessFactory::createSmartPointer(const QString& type)
{
    dtkSmartPointer<dtkAbstractProcess> process = this->create(type);
    return process;
}


bool dtkAbstractProcessFactory::registerProcessType(const QString& type, dtkAbstractProcessCreator func)
{
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        d->processCount[type] = 0;
        return true;
    }

    return false;
}

bool dtkAbstractProcessFactory::registerProcessType(const QString& type, dtkAbstractProcessCreator func, const QString& interface)
{
    if(!d->creators.contains(type)) {
        d->creators.insert(type, func);
        d->processCount[type] = 0;
        d->interfaces.insertMulti(interface, type);
        return true;
    }

    return false;
}

unsigned int dtkAbstractProcessFactory::size(const QString& type)
{
    return d->processCount[type];
}

bool dtkAbstractProcessFactory::exists(const QString& type)
{
    return d->creators.contains(type);
}

QStringList dtkAbstractProcessFactory::creators(void) const
{
    return d->creators.keys();
}

QStringList dtkAbstractProcessFactory::implementations(const QString& interface)
{
    QStringList implementations;

    if(d->interfaces.keys().contains(interface))
        implementations << d->interfaces.values(interface);
    else
        dtkWarn() << "There is no available implementation of " << interface ;

    return implementations;
}

QStringList dtkAbstractProcessFactory::interfaces(void)
{
    return d->interfaces.keys();
}

dtkAbstractProcessFactory::dtkAbstractProcessFactory(void) : dtkAbstractFactory(), d(new dtkAbstractProcessFactoryPrivate)
{

}

dtkAbstractProcessFactory::~dtkAbstractProcessFactory(void)
{
    delete d;

    d = NULL;
}

dtkAbstractProcessFactory *dtkAbstractProcessFactory::s_instance = NULL;
