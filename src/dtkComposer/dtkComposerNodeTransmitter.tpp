/* dtkComposerNodeTransmitter.tpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 10:14:36 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 28 13:07:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 83
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODETRANSMITTER_TPP
#define DTKCOMPOSERNODETRANSMITTER_TPP

#include <dtkCore/dtkLog>

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QVector>

#include <typeinfo>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeTransmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs an empty transmitter.
/*! 
 *  
 */
template <typename T> inline dtkComposerNodeTransmitter<T>::dtkComposerNodeTransmitter(void) : dtkComposerNodeAbstractTransmitter() 
{
    m_vector = 0;
    m_list = 0;
};

//! Destroys the transmitter.
/*! 
 *  It does not destroy the data.
 */
template <typename T> inline dtkComposerNodeTransmitter<T>::~dtkComposerNodeTransmitter(void)
{
    m_vector = 0;
    m_list = 0;
};

//! Sets the data with \a data.
/*! 
 *  
 */
template <typename T> inline void dtkComposerNodeTransmitter<T>::setData(const T& data)
{
    m_data = data;

    // this->setMetaData("Type", typeid(m_data).name());
};

//! Returns the data as a modifiable reference.
/*! 
 *  
 */
template <typename T> inline T& dtkComposerNodeTransmitter<T>::data(void)
{
    return m_data;
};

//! Returns the data as a non-modifiable reference.
/*! 
 *  
 */ 
template <typename T> inline const T& dtkComposerNodeTransmitter<T>::data(void) const 
{
    return m_data;
};

//! Sets the vector pointer.
/*! 
 *  
 */ 
template <typename T> inline void dtkComposerNodeTransmitter<T>::setVector(QVector<T> *vector) 
{
    if(!m_list)
        m_vector = vector;
    else
        dtkDebug() << DTK_PRETTY_FUNCTION << " Transmitter already contains a list. Vector setting failed.";
};

//! Sets the list pointer.
/*! 
 *  
 */
template <typename T> inline void dtkComposerNodeTransmitter<T>::setList(QList<T> *list)
{
    if(!m_vector)
        m_list = list;
    else
        dtkDebug() << DTK_PRETTY_FUNCTION << " Transmitter already contains a vector. List setting failed.";
};

//! Returns the pointer to the vector.
/*! 
 *  
 */
template <typename T> inline QVector<T> *dtkComposerNodeTransmitter<T>::vector(void) 
{
    return m_vector;
};

//! Returns the pointer to the list.
/*! 
 *  
 */
template <typename T> inline QList<T> *dtkComposerNodeTransmitter<T>::list(void)
{
    return m_list;
};

//! Sets the data as the item at \a index position in the vector or
//! the list.
/*! 
 *  If the vector or the list is empty, the data is set to 0.
 */
template <typename T> void dtkComposerNodeTransmitter<T>::setCurrentData(dtkxarch_int index)
{
    if (m_vector) {

        if(!m_vector->isEmpty())
            m_data = (*m_vector)[index];

    } else if (m_list) {

        if(!m_list->isEmpty())
            m_data = (*m_list)[index];

    }
};

//! Resets data, vector and list.
/*! 
 *  
 */
template <typename T> void dtkComposerNodeTransmitter<T>::clear(void)
{
    m_vector = 0;
    m_list = 0;
};

//! Returns description of the transmitter.
/*! 
 *  
 */
template <typename T> QString dtkComposerNodeTransmitter<T>::identifier(void) const
{
    QString container;

    if (m_vector)
        container = "vector";
    else if (m_list)
        container = "list";
    else
        container = "no";

    return QString("Transmitter with %1 container").arg(container);
};

#endif
