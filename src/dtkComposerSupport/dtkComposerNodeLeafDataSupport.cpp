// Version: $Id$
// 
// 

// Commentary: 
// 
// 

// Change Log:
// 
// 

// Code:

#include "dtkComposerNodeLeafDataSupport.h"

#include <dtkCoreSupport/dtkAbstractDataFactory.h>

// ///////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafDataSupport implementation
// ///////////////////////////////////////////////////////////////////

dtkComposerNodeObject<dtkAbstractData>::dtkComposerNodeObject(void) : dtkComposerNodeLeafObject(), m_implementation_has_changed(false), m_data(0)
{
    
}

dtkComposerNodeObject<dtkAbstractData>::~dtkComposerNodeObject(void)
{
    if (m_data)
        delete m_data;

    m_data = 0;
}

bool dtkComposerNodeObject<dtkAbstractData>::createObject(const QString& implementation)
{
    m_implementation_has_changed = false;

    if (implementation.isEmpty() || implementation == "Choose implementation")
        return false;

    if (implementation == "default")
        const_cast<QString&>(implementation) = this->abstractDataType();
        
    if (!m_data) {
        m_data = dtkAbstractDataFactory::instance()->create(implementation);
        m_implementation_has_changed = true;

    } else if (m_data->identifier() != implementation) {
        delete m_data;
        m_data = dtkAbstractDataFactory::instance()->create(implementation);
        m_implementation_has_changed = true;
    }

    return (m_data != NULL);
}

dtkAbstractData *dtkComposerNodeObject<dtkAbstractData>::data(void) const
{
    return m_data;
}

QStringList dtkComposerNodeObject<dtkAbstractData>::implementations(void) const
{
    QStringList implementations = dtkAbstractDataFactory::instance()->implementations(this->abstractDataType());
    
    if (this->enableDefaultImplementation())
        implementations.prepend("default");

    return implementations;
}

QString dtkComposerNodeObject<dtkAbstractData>::currentImplementation(void) const
{
    if (m_data)
        return m_data->identifier();

    return QString();
}

bool dtkComposerNodeObject<dtkAbstractData>::implementationHasChanged(void) const
{
    return (m_implementation_has_changed);
}

bool dtkComposerNodeObject<dtkAbstractData>::implementationHasChanged(const QString& implementation) const
{
    if (m_data)
        return (m_data->identifier() != implementation);

    return true;
}

bool dtkComposerNodeObject<dtkAbstractData>::enableDefaultImplementation(void) const
{
    return false;
}

// 
// dtkComposerNodeLeafDataSupport.cpp ends here
