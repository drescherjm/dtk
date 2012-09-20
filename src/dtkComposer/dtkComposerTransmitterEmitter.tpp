/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Sep 20 13:12:33 2012 (+0200)
 *           By: tkloczko
 *     Update #: 417
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

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::dtkComposerTransmitterEmitter(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{
    m_data = NULL;
    d->data_type = qMetaTypeId<T>(m_data);
    d->variant.setValue(m_data);
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
    m_data = NULL;
    d->object = NULL;
    d->variant.clear();
    d->container = NULL;
};

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitterEmitter<T>::setData(T *data)
{
    m_data = data;
    d->variant.setValue(m_data);
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T *dtkComposerTransmitterEmitter<T>::data(void)
{
    return m_data;
};

template <typename T> dtkAbstractObject *dtkComposerTransmitterEmitter<T>::object(void)
{
    if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
        return reinterpret_cast<dtkAbstractObject*>(m_data);
    
    return NULL;
};

template <typename T> int dtkComposerTransmitterEmitter<T>::dataType(void)
{
    return d->data_type;
};

template <typename T> QString dtkComposerTransmitterEmitter<T>::dataIdentifier(void)
{
    if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
        return reinterpret_cast<dtkAbstractObject*>(m_data)->identifier();

    if (dtkTypeInfo<T*>::dtkMatrixRealPointer)
        return reinterpret_cast<dtkMatrix<qreal>*>(m_data)->identifier();

    return QString(QMetaType::typeName(d->data_type));
};

template <typename T> QString dtkComposerTransmitterEmitter<T>::dataDescription(void)
{
    if (dtkTypeInfo<T*>::dtkAbstractObjectPointer)
        return reinterpret_cast<dtkAbstractObject*>(m_data)->description();

    if (dtkTypeInfo<T*>::dtkMatrixRealPointer)
        return reinterpret_cast<dtkMatrix<qreal>*>(m_data)->description();

    QString address;
    QTextStream addressStream (&address);
    addressStream << (static_cast<const void*>(m_data));

    return address;
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline bool dtkComposerTransmitterEmitter<T>::enableCopy(void)
{
    return (d->receivers.count() > 1);
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

template <typename T> dtkComposerTransmitter::LinkMap dtkComposerTransmitterEmitter<T>::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVector implementation
// /////////////////////////////////////////////////////////////////

template <typename T> inline dtkComposerTransmitterEmitterVector<T>::dtkComposerTransmitterEmitterVector(dtkComposerNode *parent) : dtkComposerTransmitterEmitter<T>(parent)
{
    d->data_type = qMetaTypeId<dtkAbstractContainerWrapper>(reinterpret_cast<dtkAbstractContainerWrapper*>(0));

    d->variant.setValue(d->container);
};

template <typename T> inline dtkComposerTransmitterEmitterVector<T>::~dtkComposerTransmitterEmitterVector(void)
{

};

template <typename T> void dtkComposerTransmitterEmitterVector<T>::clearData(void)
{
    m_vector = NULL;
    d->object = NULL;
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

    d->object = d->container;
};

template <typename T> inline dtkContainerVector<T> *dtkComposerTransmitterEmitterVector<T>::data(void)
{
    return m_vector;
};

template <typename T> dtkAbstractObject *dtkComposerTransmitterEmitterVector<T>::object(void)
{
    return d->container;
};

template <typename T> int dtkComposerTransmitterEmitterVector<T>::dataType(void)
{
    return d->data_type;
};

template <typename T> QString dtkComposerTransmitterEmitterVector<T>::dataIdentifier(void)
{
    return m_vector->identifier();
};

template <typename T> QString dtkComposerTransmitterEmitterVector<T>::dataDescription(void)
{
    return m_vector->description();
};

//! Returns true when the emitter is connected to more than one
//! receiver.
/*! 
 *  When several receivers are connected to the emitter, some nodes
 *  receiving the data can modify it while others only read
 *  it. According to the order of such operations, the data can be
 *  modified before it is read leading to unexpected behaviors.
 *
 *  To circumvent this issue, the emitter informs the receivers that
 *  they must copy the data if they modify it ensuring that the
 *  original data is not corrupted for the other nodes.
 */
template <typename T> inline bool dtkComposerTransmitterEmitterVector<T>::enableCopy(void)
{
    return (d->receivers.count() > 1);
};

#endif
