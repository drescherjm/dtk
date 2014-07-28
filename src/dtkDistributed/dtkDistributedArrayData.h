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

#include <dtkCore/dtkArrayData>
#include <QtCore>

class dtkDistributedCommunicator;

// /////////////////////////////////////////////////////////////////
// dtkDistributedArrayData
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArrayData : public dtkTypedArrayData<T>
{
public:
    dtkDistributedArrayData(void);

public:
    void allocate(dtkDistributedCommunicator *comm, qlonglong wid, qlonglong n);

public:
    qlonglong size(void) const;
    qlonglong   id(void) const;

private:
    static dtkTypedArrayData<T> *allocateHeader(void);

private:
    qlonglong m_id;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedCommunicator.h"

template<typename T> inline dtkDistributedArrayData<T>::dtkDistributedArrayData(void) : dtkTypedArrayData<T>(*dtkDistributedArrayData<T>::allocateHeader()), m_id(-1)
{
}

template<typename T> inline void dtkDistributedArrayData<T>::allocate(dtkDistributedCommunicator *comm, qlonglong wid, qlonglong n)
{
    void *array = comm->allocate(n, sizeof(T), wid, this->m_id);

    this->dtkTypedArrayData<T>::offset = reinterpret_cast<const char *>(array) - reinterpret_cast<const char *>(this);
    this->dtkTypedArrayData<T>::size = n;
}

template<typename T> inline qlonglong dtkDistributedArrayData<T>::size(void) const
{ 
    return QTypedArrayData<T>::size; 
}

template<typename T> inline qlonglong dtkDistributedArrayData<T>::id(void) const
{ 
    return m_id;
}

template<typename T> inline dtkTypedArrayData<T> *dtkDistributedArrayData<T>::allocateHeader(void)
{ 
    return dtkTypedArrayData<T>::allocate(0, dtkArrayData::RawData); 
}

// 
// dtkDistributedArrayData.h ends here
