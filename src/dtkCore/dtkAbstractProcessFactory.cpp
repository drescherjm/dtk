/* dtkAbstractProcessFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Sep 17 16:57:05 2010 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 85
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>

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

dtkAbstractProcess *dtkAbstractProcessFactory::create(QString type)
{
    if(!d->creators.contains(type))
        return NULL;

    dtkAbstractProcess *process = d->creators[type]();

    process->setObjectName(QString("%1%2").arg(process->metaObject()->className()).arg(d->processes[type].count()));

    d->processes[type] << process;
    
    emit created(process, type);

    return process;
}

bool dtkAbstractProcessFactory::registerProcessType(QString type, dtkAbstractProcessCreator func)
{
    if(!d->creators.contains(type)) {
	d->creators.insert(type, func);
	return true;
    }
 
    return false;
}

bool dtkAbstractProcessFactory::registerProcessType(QString type, dtkAbstractProcessCreator func, QString interface)
{
    if(!d->creators.contains(type)) {
	d->creators.insert(type, func);
        d->interfaces.insert(type, interface);
	return true;
    }
 
    return false;
}

unsigned int dtkAbstractProcessFactory::size(QString type)
{
    return d->processes[type].size();
}

dtkAbstractProcess *dtkAbstractProcessFactory::get(QString type, int idx)
{
    return d->processes[type].value(idx);
}

dtkAbstractProcess *dtkAbstractProcessFactory::get(QString type, QString name)
{
    foreach(dtkAbstractProcess *process, d->processes[type])
        if(process->name() == name)
            return process;

    return NULL;
}

bool dtkAbstractProcessFactory::exists(QString type)
{
    return d->creators.contains(type);
}

QStringList dtkAbstractProcessFactory::implementations(const QString& abstraction)
{
    QStringList implementations;

    foreach(QString interface, d->interfaces.values())
        if(interface == abstraction)
            implementations << d->interfaces.key(interface);
        
    return implementations;
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
