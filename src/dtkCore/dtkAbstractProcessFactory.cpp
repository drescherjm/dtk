/* dtkAbstractProcessFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 12:44:29 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 46
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

    process->setObjectName(QString("process%1").arg(d->processes.count()));

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

dtkAbstractProcessFactory::dtkAbstractProcessFactory(void) : dtkAbstractFactory(), d(new dtkAbstractProcessFactoryPrivate)
{

}

dtkAbstractProcessFactory::~dtkAbstractProcessFactory(void)
{
    delete d;

    d = NULL;
}

dtkAbstractProcessFactory *dtkAbstractProcessFactory::s_instance = NULL;
