/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: 2012 Wed Dec 12 21:35:35 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 312
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTEREMITTER_TPP
#define DTKCOMPOSERTRANSMITTEREMITTER_TPP

#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"



#include <dtkCore/dtkGlobal.h>

#include <dtkContainer/dtkContainerVectorWrapper.h>

#if defined(DTK_HAVE_PLOT)
#include <dtkPlot/dtkPlotCurve.h>
#endif

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::dtkComposerTransmitterEmitter(dtkComposerNode *parent) : dtkComposerTransmitterAbstractEmitter(parent)
{
    m_data = T();
    d->data_type = dtkComposerTypeInfo<T>::type();
};

//! Destroys the emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::~dtkComposerTransmitterEmitter(void)
{

};

template <typename T> void dtkComposerTransmitterEmitter<T>::clearData(void)
{
    m_data = T();
    d->variant.clear();
};

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitterEmitter<T>::setData(T& data)
{
    m_data = data;
    d->variant.setValue(m_data);
};

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitterEmitter<T>::setData(const T& data)
{
    this->setData(const_cast<T&>(data));
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerTransmitterEmitter<T>::data(void)
{
    return m_data;
};

//! Returns.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitter::Kind dtkComposerTransmitterEmitter<T>::kind(void) const
{
    return dtkComposerTransmitter::Emitter;
};

template <typename T> inline QString dtkComposerTransmitterEmitter<T>::kindName(void) const
{
    return "Emitter";
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVector implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkComposerTransmitterEmitterVector<T>::dtkComposerTransmitterEmitterVector(dtkComposerNode *parent) : dtkComposerTransmitterAbstractEmitter(parent)
{
    m_vector = NULL;
    d->data_type = dtkComposerTypeInfo<dtkContainerVector<T>*>::type();
};

template <typename T> inline dtkComposerTransmitterEmitterVector<T>::~dtkComposerTransmitterEmitterVector(void)
{

};

template <typename T> void dtkComposerTransmitterEmitterVector<T>::clearData(void)
{
    m_vector = NULL;
    d->variant.clear();
    if (d->container)
        delete d->container;
    d->container = NULL;
};

template <typename T> inline dtkComposerTransmitter::Kind dtkComposerTransmitterEmitterVector<T>::kind(void) const
{
    return dtkComposerTransmitter::EmitterVector;
};

template <typename T> inline QString dtkComposerTransmitterEmitterVector<T>::kindName(void) const
{
    return "EmitterContainer";
};

template <typename T> inline void dtkComposerTransmitterEmitterVector<T>::setData(dtkContainerVector<T> *vector)
{
    m_vector = vector;
    if (!d->container)
        d->container = new dtkContainerVectorWrapper<T>(m_vector);
    else
         d->container->setVector(m_vector);
    d->variant.setValue(d->container);
};

template <typename T> inline void dtkComposerTransmitterEmitterVector<T>::setData(const dtkContainerVector<T> *vector)
{
    this->setData(const_cast<dtkContainerVector<T>*>(vector));
};

template <typename T> inline dtkContainerVector<T> *dtkComposerTransmitterEmitterVector<T>::data(void)
{
    return m_vector;
};

#endif
