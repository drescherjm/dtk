/* dtkAbstractProcessFactory.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:54:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  7 11:34:14 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>

dtkAbstractProcessFactory * dtkAbstractProcessFactory::instance(void)
{
    if(!m_instance)
	m_instance = new dtkAbstractProcessFactory;

    return m_instance;
}

dtkAbstractProcess * dtkAbstractProcessFactory::create(QString type)
{
    if(m_creators.contains(type))
	return m_creators[type]();

    return NULL;
}

bool dtkAbstractProcessFactory::registerProcessType(QString type, dtkAbstractProcessCreator func)
{
    if(!m_creators.contains(type)) {
	m_creators.insert(type, func);
	return true;
    }
 
    return false;
}

dtkAbstractProcessFactory::dtkAbstractProcessFactory(void) : dtkAbstractFactory()
{

}

dtkAbstractProcessFactory * dtkAbstractProcessFactory::m_instance = NULL;
