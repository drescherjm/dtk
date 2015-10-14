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

#include "dtkDistributedArrayCache.h"
#include "dtkDistributedContainer.h"
#include "dtkDistributedNavigator.h"

#include <dtkCore/dtkArray.h>
#include <dtkCore/dtkArrayData.h>

class dtkDistributedCommunicator;
class dtkDistributedMapper;
class dtkDistributedBufferManager;

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedArray : public dtkDistributedContainer
{
    typedef dtkTypedArrayData<T> Data;
    typedef dtkDistributedArrayCache<T> Cache;

public:
    typedef dtkDistributedNavigator< dtkDistributedArray<T> > navigator;

public:
    typedef typename Data::const_iterator const_iterator;
    typedef typename Data::iterator             iterator;
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;

public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef qptrdiff difference_type;
    typedef qlonglong size_type;

public:
     dtkDistributedArray(const qlonglong& size);
     dtkDistributedArray(const qlonglong& size, dtkDistributedMapper *mapper);
     dtkDistributedArray(const qlonglong& size, const T& init_value);
     dtkDistributedArray(const qlonglong& size, const T *array);
     dtkDistributedArray(const dtkArray<T> &array);
     dtkDistributedArray(const dtkDistributedArray& other);
    ~dtkDistributedArray(void);

public:
    dtkDistributedArray& operator = (const dtkDistributedArray& other);

public:
    void remap(dtkDistributedMapper *remapper);

public:
    void  rlock(qint32 owner);
    void  wlock(qint32 owner);
    void unlock(qint32 owner);

public:
    void  rlock(void);
    void  wlock(void);
    void unlock(void);

public:
    bool empty(void) const;
    qlonglong size(void) const;
    void clearCache(void) const;

public:
    void fill(const T& value);

public:
    void setAt(const qlonglong& index, const T& value);
    void setAt(const qlonglong& index, T *array, const qlonglong& size);

    T at(const qlonglong& index) const;

    T first(void) const;
    T  last(void) const;

public:
    T operator[](const qlonglong& index) const;

public:
    void addAssign(const qlonglong& index, const T& value);
    void subAssign(const qlonglong& index, const T& value);
    void mulAssign(const qlonglong& index, const T& value);
    void divAssign(const qlonglong& index, const T& value);
    bool compareAndSwap(const qlonglong& index, T& value, T& compare);

public:
    void addAssign(const qlonglong& index, T* array, const qlonglong& count);
    void subAssign(const qlonglong& index, T* array, const qlonglong& count);
    void mulAssign(const qlonglong& index, T* array, const qlonglong& count);
    void divAssign(const qlonglong& index, T* array, const qlonglong& count);

public:
    void copyIntoArray(const qlonglong& from, const qint32& owner, T *array, qlonglong& size) const;

public:
          iterator  begin(iterator = iterator());
          iterator    end(iterator = iterator());
    const_iterator  begin(const_iterator = const_iterator()) const;
    const_iterator    end(const_iterator = const_iterator()) const;
    const_iterator cbegin(const_iterator = const_iterator()) const;
    const_iterator   cend(const_iterator = const_iterator()) const;

public:
    const T *data(void) const;
          T *data(void);

    const T *constData(void) const;

public:
    navigator toNavigator(void) const;

public:
    void stats(void) const;

private:
    void allocate(dtkDistributedBufferManager *&, Data *&, qlonglong);
    void deallocate(dtkDistributedBufferManager *, Data *);
    void copyConstruct(const T *srcFrom, const T *srcTo, T *dstFrom);

private:
    Data  *d;
    mutable T val;
    mutable Cache *m_cache;
    dtkDistributedBufferManager *m_buffer_manager;
    bool locked = false;
    qlonglong firstIndex = 0;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"

// 
// dtkDistributedArray.h ends here
