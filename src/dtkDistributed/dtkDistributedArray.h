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
#include "dtkDistributedArrayData.h"
#include "dtkDistributedContainer.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArray : public dtkDistributedContainer
{
public:
      dtkDistributedArray(const qlonglong& size, dtkDistributedWorker *worker);
      dtkDistributedArray(const qlonglong& size, dtkDistributedWorker *worker, dtkDistributedMapper *mapper);
      dtkDistributedArray(const qlonglong& size, const T *array, dtkDistributedWorker *worker);
      dtkDistributedArray(const dtkDistributedArray& other);
     ~dtkDistributedArray(void);
    
private:
    void initialize(void);

public:
    void remap(dtkDistributedMapper *remapper);

public:
    void setAt(const qlonglong& index, const T& value);

    T at(const qlonglong& index) const;

    T first(void) const;
    T  last(void) const;

    void copyIntoArray(const qlonglong& from, T *array, qlonglong& size) const;

public:
    void  rlock(qint32 owner);
    void  wlock(qint32 owner);
    void unlock(qint32 owner);

public:
    typedef dtkDistributedArrayData<T>   Data;
    typedef dtkDistributedArrayCache<T> Cache;

    typedef typename Data::const_iterator const_iterator;
    typedef typename Data::iterator             iterator;

public:
          iterator  begin(iterator = iterator());
          iterator    end(iterator = iterator());
    const_iterator  begin(const_iterator = const_iterator()) const;
    const_iterator    end(const_iterator = const_iterator()) const;
    const_iterator cbegin(const_iterator = const_iterator()) const;
    const_iterator   cend(const_iterator = const_iterator()) const;

private:
    void freeData(Data *);

private:
            Data  *data;
    mutable Cache *cache;
}; 

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"

// 
// dtkDistributedArray.h ends here
