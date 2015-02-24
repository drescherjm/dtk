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

#include "dtkDistributedExport.h"
#include "dtkDistributedArrayCache.h"
#include "dtkDistributedContainer.h"
#include "dtkDistributedNavigator.h"

#include <dtkCore/dtkArrayData.h>

class dtkDistributedCommunicator;
class dtkDistributedMapper;
class dtkDistributedBufferManager;

// /////////////////////////////////////////////////////////////////
// dtkDistributedStaticArray
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedStaticArray : public dtkDistributedContainer
{
    typedef dtkTypedArrayData<T> Data;
    typedef dtkDistributedArrayCache<T, dtkDistributedStaticArray<T> > Cache;

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
    typedef dtkDistributedNavigator< dtkDistributedStaticArray<T> > navigator;

public:
     dtkDistributedStaticArray(const qlonglong& size);
     dtkDistributedStaticArray(const qlonglong& size, dtkDistributedMapper *mapper);
     dtkDistributedStaticArray(const qlonglong& size, const T& init_value);
     dtkDistributedStaticArray(const qlonglong& size, const T *array);
     dtkDistributedStaticArray(const dtkDistributedStaticArray& other);
    ~dtkDistributedStaticArray(void);

public:
    void remap(dtkDistributedMapper *remapper);

public:
    void  rlock(qint32 owner);
    void  wlock(qint32 owner);
    void unlock(qint32 owner);

public:
     bool empty(void) const;
     qlonglong size(void) const;

public:
     void fill(const T& value);

public:
    void setAt(const qlonglong& index, const T& value);
    void setAt(const qlonglong& index, T *array, const qlonglong& size);

    T at(const qlonglong& index) const;

    T first(void) const;
    T  last(void) const;

public:
    T operator[](qlonglong index) const;

public:
    void copyIntoArray(const qlonglong& from, T *array, qlonglong& size) const;

public:
          iterator  begin(iterator = iterator());
          iterator    end(iterator = iterator());
    const_iterator  begin(const_iterator = const_iterator()) const;
    const_iterator    end(const_iterator = const_iterator()) const;
    const_iterator cbegin(const_iterator = const_iterator()) const;
    const_iterator   cend(const_iterator = const_iterator()) const;

public:
    navigator toNavigator(void) const;

public:
    void stats(void) const;

private:
    void allocate(dtkDistributedBufferManager *&, Data *&, qlonglong);
    void deallocate(dtkDistributedBufferManager *, Data *);

private:
    Data  *data;
    mutable Cache *m_cache;
    dtkDistributedBufferManager *m_buffer_manager;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedStaticArray.tpp"

// 
// dtkDistributedStaticArray.h ends here
