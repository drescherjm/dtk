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

class DTKDISTRIBUTED_EXPORT dtkDistributedBufferManager
{
public:
    virtual ~dtkDistributedBufferManager(void) {;}

public:
    template <typename T>    T *allocate(qlonglong capacity);
    template <typename T> void  deallocate(T *& buffer);
    
protected:
    virtual void *allocate(qlonglong objectSize, qlonglong capacity) = 0;
    virtual void  deallocate(void *buffer, qlonglong objectSize) = 0;

public:
    virtual void rlock(qlonglong wid)  = 0;
    virtual void wlock(qlonglong wid)  = 0;

    virtual void unlock(qlonglong wid) = 0;

    virtual bool locked(qlonglong wid) = 0;

public:
    virtual void get(qint32 from, qlonglong position, void *array, qlonglong nelements = 1) = 0;
    virtual void put(qint32 dest, qlonglong position, void *array, qlonglong nelements = 1) = 0;
};

template <typename T> inline T *dtkDistributedBufferManager::allocate(qlonglong capacity)
{
    return static_cast<T *>(this->allocate(sizeof(T), capacity));
}

template <typename T> inline void dtkDistributedBufferManager::deallocate(T *& buffer)
{
    this->deallocate(buffer, sizeof(T));
    buffer = NULL;
}

// 
// dtkDistributedBufferManager.h ends here
