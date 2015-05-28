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

// ///////////////////////////////////////////////////////////////////
// dtkComposerNodeObject implementation
// ///////////////////////////////////////////////////////////////////

template <typename T> inline dtkComposerNodeObject<T>::dtkComposerNodeObject(void) : dtkComposerNodeLeafObject(), m_implementation(QString()), m_object(0), m_factory(0)
{
    
}

template <typename T> inline dtkComposerNodeObject<T>::~dtkComposerNodeObject(void)
{
    if (m_object)
        delete m_object;

    m_object = 0;
    m_factory = 0;
}

template <typename T> inline void dtkComposerNodeObject<T>::setFactory(const dtkCorePluginFactory<T>& factory)
{
    m_factory = &factory;
}

template <typename T> inline T *dtkComposerNodeObject<T>::object(void) const
{
    return m_object;
}

template <typename T> inline bool dtkComposerNodeObject<T>::createObject(const QString& implementation)
{
    if (implementation.isEmpty() || implementation == "Choose implementation")
        return false;
    
    if (!m_object) {
        m_object = m_factory->create(implementation);
        if (m_object)
            m_implementation = implementation;

    } else if (m_implementation != implementation) {
        if (m_object)
            delete m_object;

        m_object = m_factory->create(implementation);
        if (m_object)
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
