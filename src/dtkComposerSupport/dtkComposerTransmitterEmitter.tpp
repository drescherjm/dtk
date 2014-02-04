/* dtkComposerTransmitterEmitter.tpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:37:37 2012 (+0100)
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

#include "dtkComposerSupportExport.h"

#include <dtkCoreSupport/dtkGlobal.h>

#include <dtkContainerSupport/dtkContainerVectorWrapper.h>

#if defined(DTK_BUILD_PLOT) && defined(DTK_HAVE_PLOT)
#include <dtkPlot/dtkPlotCurve.h>
#endif

// /////////////////////////////////////////////////////////////////
// Forward declaration of specialized method
// /////////////////////////////////////////////////////////////////

template <> DTKCOMPOSERSUPPORT_EXPORT QString       dtkComposerTransmitterEmitter<qreal>::dataDescription(void);
template <> DTKCOMPOSERSUPPORT_EXPORT QString   dtkComposerTransmitterEmitter<qlonglong>::dataDescription(void);
template <> DTKCOMPOSERSUPPORT_EXPORT QString     dtkComposerTransmitterEmitter<QString>::dataDescription(void);
template <> DTKCOMPOSERSUPPORT_EXPORT QString dtkComposerTransmitterEmitter<QStringList>::dataDescription(void);
template <> DTKCOMPOSERSUPPORT_EXPORT QString        dtkComposerTransmitterEmitter<bool>::dataDescription(void);

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty emitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerTransmitterEmitter<T>::dtkComposerTransmitterEmitter(dtkComposerNode *parent) : dtkComposerTransmitterAbstractEmitter(parent)
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
    d->matrix = NULL;
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

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerTransmitterEmitter<T>::setData(const T *data)
{
    this->setData(const_cast<T*>(data));
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

template <typename T> dtkMatrix<double> *dtkComposerTransmitterEmitter<T>::matrix(void)
{
    if (dtkTypeInfo<T*>::dtkMatrixRealPointer)
        return reinterpret_cast<dtkMatrix<double>*>(m_data);
    
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

// #if defined(DTK_BUILD_PLOT)
//     if (dtkPlotCurve *curve = dynamic_cast<dtkPlotCurve*>(m_data))
//         return curve->description();
// #endif

    QString address;
    QTextStream addressStream (&address);
    addressStream << (static_cast<const void*>(m_data));

    return address;
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
    d->matrix = NULL;
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

template <typename T> inline void dtkComposerTransmitterEmitterVector<T>::setData(const dtkContainerVector<T> *vector)
{
    this->setData(const_cast<dtkContainerVector<T>*>(vector));
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

#endif
