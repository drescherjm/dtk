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

#include <dtkCore/dtkCorePluginFactory>
#include <dtkMeta/dtkMeta>

// ///////////////////////////////////////////////////////////////////
// dtkComposerNodeObject implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkComposerNodeObject<T>::dtkComposerNodeObject(void) : dtkComposerNodeLeafObject(), m_implementation(QString()), m_object(0), m_factory(0)
{
    
}

template <typename T> inline dtkComposerNodeObject<T>::~dtkComposerNodeObject(void)
{
    for( T* t : m_processes.values())
      delete t;
}

template <typename T> inline void dtkComposerNodeObject<T>::setFactory(const dtkCorePluginFactory<T>& factory)
{
    m_factory = &factory;
}

template <typename T> inline QVariant dtkComposerNodeObject<T>::variant(void) const
{
    if (this->object())
        return dtkMetaType::variantFromValue(this->object());
    else
        return QVariant();
}

template <typename T> inline T *dtkComposerNodeObject<T>::object(void) const
{
    return m_object;
}

template <typename T> inline bool dtkComposerNodeObject<T>::createObject(const QString& implementation)
{
    if (implementation.isEmpty() || implementation == "Choose implementation")
        return false;
    
    if (m_processes.contains(implementation)) {
	m_object=m_processes.value(implementation);
    }
    else {    
        m_object = m_factory->create(implementation);
	if(m_object) {
	  m_processes.insert(implementation, m_object);
	}
    }
    
    if (m_object) {
      m_implementation = implementation;
    }
    
    return (m_object != NULL);
}

template <typename T> inline QStringList dtkComposerNodeObject<T>::implementations(void) const
{
    if (m_factory)
        return m_factory->keys();

    return QStringList();
}

template <typename T> inline QString dtkComposerNodeObject<T>::currentImplementation(void) const
{
    return m_implementation;
}

template <typename T> inline bool dtkComposerNodeObject<T>::implementationHasChanged(const QString& implementation) const
{
    return (m_implementation != implementation);
}

// 
// dtkComposerNodeObject.tpp ends here
