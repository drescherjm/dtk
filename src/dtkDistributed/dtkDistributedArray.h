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

#include "dtkDistributedContainer.h"
#include "dtkDistributedArrayData.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArray : public dtkDistributedContainer
{
public:
    typedef dtkDistributedArrayData<T> Data;

public:
      dtkDistributedArray(const qlonglong& size, dtkDistributedWorker *worker);
      dtkDistributedArray(const qlonglong& size, dtkDistributedWorker *worker, dtkDistributedMapper *mapper);
      dtkDistributedArray(const qlonglong& size, const T *array, dtkDistributedWorker *worker);
      dtkDistributedArray(const dtkDistributedArray& other);
     ~dtkDistributedArray(void);
    
private:
    void initialize(void);

public:
    void setAt(const qlonglong& index, const T& value);

    T at(const qlonglong& index) const;

    T first(void) const;
    T  last(void) const;

public:
    typedef typename Data::const_iterator const_iterator;
    typedef typename Data::iterator             iterator;

public:
          iterator  begin(iterator = iterator())                   { return data.begin(); }
          iterator    end(iterator = iterator())                   { return data.end(); }
    const_iterator  begin(const_iterator = const_iterator()) const { return data.begin(); }
    const_iterator    end(const_iterator = const_iterator()) const { return data.end(); }
    const_iterator cbegin(const_iterator = const_iterator()) const { return data.cbegin(); }
    const_iterator   cend(const_iterator = const_iterator()) const { return data.cend(); }

public:
    void setLocalValue(const qlonglong& index, const T& value);

    const T& localValue(const qlonglong& index) const;

public:
    qlonglong dataId(void) const;

protected:
    Data data;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"

// 
// dtkDistributedArray.h ends here
