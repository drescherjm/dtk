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

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkDistributedArrayData
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArrayData : public QTypedArrayData<T>
{
public:
    dtkDistributedArrayData(void);

public:
    void setRawData(T *data, qlonglong n, qlonglong id);

public:
    qlonglong size(void) const;
    qlonglong   id(void) const;

private:
    static QTypedArrayData<T> *allocateHeader(void);

private:
    qlonglong m_id;
};

// ///////////////////////////////////////////////////////////////////
    
template<typename T> inline dtkDistributedArrayData<T>::dtkDistributedArrayData(void) : QTypedArrayData<T>(*dtkDistributedArrayData<T>::allocateHeader()), m_id(-1)
{
}

template<typename T> inline void dtkDistributedArrayData<T>::setRawData(T *data, qlonglong n, qlonglong id) 
{
    this->QTypedArrayData<T>::offset = reinterpret_cast<const char *>(data) - reinterpret_cast<const char *>(this);
    this->QTypedArrayData<T>::size = n;
    this->m_id = id;
}

template<typename T> inline qlonglong dtkDistributedArrayData<T>::size(void) const 
{ 
    return QTypedArrayData<T>::size; 
}

template<typename T> inline qlonglong dtkDistributedArrayData<T>::id(void) const
{ 
    return m_id;
}

template<typename T> inline QTypedArrayData<T> *dtkDistributedArrayData<T>::allocateHeader(void)
{ 
    return QTypedArrayData<T>::allocate(0, QArrayData::RawData); 
}

// 
// dtkDistributedArrayData.h ends here
