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

#pragma once

// /////////////////////////////////////////////////////////////////
// dtkCorePluginTuner implementation
// /////////////////////////////////////////////////////////////////

template < typename T > inline dtkCorePluginTuner<T>::dtkCorePluginTuner(void) : m_object(nullptr)
{
}

template < typename T > inline dtkCorePluginTuner<T>::~dtkCorePluginTuner(void)
{
}

template < typename T > inline void dtkCorePluginTuner<T>::setObject(T *object)
{
    m_object = object;
}

template < typename T > inline void dtkCorePluginTuner<T>::setMap(const QVariantHash& map)
{
    m_map = map;
}

template < typename T > inline T *dtkCorePluginTuner<T>::object(void) const
{
    return m_object;
}

template < typename T > inline const QVariantHash& dtkCorePluginTuner<T>::map(void) const
{
    return m_map;
}

//
// dtkCorePluginTuner.tpp ends here
