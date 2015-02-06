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
    virtual void *allocate(qlonglong objectSize, qlonglong capacity)   = 0;
    virtual void  deallocate() = 0;

public:
    virtual void rlock(qlonglong wid)  = 0;
    virtual void wlock(qlonglong wid)  = 0;

    virtual void unlock(qlonglong wid) = 0;

    virtual bool locked(qlonglong wid) = 0;

public:
    virtual void get(qint32 from, qlonglong position, void *array, qlonglong nelements = 1) = 0;
    virtual void put(qint32 dest, qlonglong position, void *array, qlonglong nelements = 1) = 0;
};

// 
// dtkDistributedBufferManager.h ends here
