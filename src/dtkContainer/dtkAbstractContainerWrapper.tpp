/* dtkAbstractContainerWrapper.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Aug  9 14:48:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 19 11:35:08 2012 (+0200)
 *           By: tkloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINERWRAPPER_TPP
#define DTKABSTRACTCONTAINERWRAPPER_TPP

class dtkAbstractContainerWrapper;
template <typename T> class dtkContainerVectorWrapper;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkAbstractContainerWrapper::setVector(dtkContainerVector<T> *vector)
{
    if (this->type() != Vector)
        return;

    dtkContainerVectorWrapper<T> *wrapper = reinterpret_cast<dtkContainerVectorWrapper<T> *>(m_container);

    wrapper->setVector(vector);
}

template <typename T> dtkContainerVector<T> *dtkAbstractContainerWrapper::vector(void)
{
    if (this->type() != Vector)
        return NULL;

    dtkContainerVectorWrapper<T> *wrapper = reinterpret_cast<dtkContainerVectorWrapper<T> *>(m_container);

    return wrapper->vector();
}

#endif
