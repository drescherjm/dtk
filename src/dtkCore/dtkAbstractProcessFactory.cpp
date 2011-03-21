/* dtkAbstractProcessFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 16 14:56:47 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 115
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkLog.h>

typedef QHash<QString, QList<dtkAbstractProcess*> > dtkAbstractProcessHash;

class dtkAbstractProcessFactoryPrivate
{
public:
    dtkAbstractProcessHash processes;

    dtkAbstractProcessFactory::dtkAbstractProcessInterfacesHash interfaces;
    dtkAbstractProcessFactory::dtkAbstractProcessCreatorHash creators;
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

    process->setObjectName(QString("%1%2").arg(process->metaObject()->className()).arg(d->processes[type].count()));

    d->processes[type] << process;
    
    emit created(process, type);

    return process;
}

bool dtkAbstractProcessFactory::registerProcessType(const QString& type, dtkAbstractProcessCreator func)
{
    if(!d->creators.contains(type)) {
	d->creators.insert(type, func);
	return true;
    }
 
    return false;
}

bool dtkAbstractProcessFactory::registerProcessType(const QString& type, dtkAbstractProcessCreator func, const QString& interface)
{
    if(!d->creators.contains(type)) {
	d->creators.insert(type, func);
        d->interfaces.insertMulti(interface, type);
	return true;
    }
 
    return false;
}

unsigned int dtkAbstractProcessFactory::size(const QString& type)
{
    return d->processes[type].size();
}

dtkAbstractProcess *dtkAbstractProcessFactory::get(const QString& type, int idx)
{
    return d->processes[type].value(idx);
}

dtkAbstractProcess *dtkAbstractProcessFactory::get(const QString& type, const QString& name)
{
    foreach(dtkAbstractProcess *process, d->processes[type])
        if(process->name() == name)
            return process;

    return NULL;
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
        dtkWarning() << "There is no avalaible implementation of " << interface ;

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
