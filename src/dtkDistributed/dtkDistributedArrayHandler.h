/* dtkDistributedArrayHandler.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb 18 10:24:22 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

template <typename T> class dtkDistributedArray;
template <typename T> class dtkDistributedArrayHandler;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedArrayHandler : public QObject
{
public:
    void setArray(dtkDistributedArray<T> *array) { m_array = array; } 

    
public:
    void  setLocalMode(void) {
        countMethod = &dtkDistributedArrayHandler<T>::countLocal;
    }

    void setGlobalMode(void) {
        countMethod = &dtkDistributedArrayHandler<T>::countGlobal;
    }

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

public:
    qlonglong count(void) const { return (this->*countMethod)(); }

protected:
    qlonglong  countLocal(void) const { return m_array->m_buffer_count; }
    qlonglong countGlobal(void) const { return m_array->m_count; }

protected:
    typedef qlonglong (dtkDistributedArrayHandler<T>::*countMethodPointer)(void) const;

protected:
    countMethodPointer countMethod;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

private:
    dtkDistributedArray<T> *m_array;
};
