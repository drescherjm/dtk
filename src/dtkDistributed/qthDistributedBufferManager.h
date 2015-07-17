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

#include "dtkDistributedBufferManager.h"
#include "dtkDistributedCommunicator.h"

#include <dtkCore/dtkArray.h>
#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// qthDistributedBufferManagerPrivate
// ///////////////////////////////////////////////////////////////////

class qthDistributedBufferManagerPrivate
{
public:
    dtkDistributedCommunicator *comm;

public:
    qlonglong size; // size = # of threads
    qlonglong object_size;
    QVarLengthArray<char *, 64> buffers;
    QVarLengthArray<QReadWriteLock *, 64> locks;
    QVarLengthArray<QAtomicInt, 64> locked;
};

// ///////////////////////////////////////////////////////////////////
// qthDistributedBufferManager
// ///////////////////////////////////////////////////////////////////

class qthDistributedBufferManager : public dtkDistributedBufferManager
{
public:
     qthDistributedBufferManager(dtkDistributedCommunicator *comm);
    ~qthDistributedBufferManager(void);

protected:
    void *allocate(qlonglong objectSize, qlonglong capacity, int metatype_id);
    void  deallocate(void *buffer, qlonglong objectSize);

public:
    bool shouldCache(const qint32& owner);

public:
    void rlock(qlonglong wid);
    void rlock(void);
    void wlock(qlonglong wid);
    void wlock(void);

    void unlock(qlonglong wid);
    void unlock(void);

    bool locked(qlonglong wid);

public:
    void get(qint32 from, qlonglong position, void *array, qlonglong nelements = 1);
    void put(qint32 dest, qlonglong position, void *array, qlonglong nelements = 1);
    void addAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements = 1);
    void subAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements = 1);
    void mulAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements = 1);
    void divAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements = 1);

public:
    bool canHandleOperationManager(void);

public:
    qthDistributedBufferManagerPrivate *d;
};

// ///////////////////////////////////////////////////////////////////

inline qthDistributedBufferManager::qthDistributedBufferManager(dtkDistributedCommunicator *comm) : d(new qthDistributedBufferManagerPrivate)
{
    d->comm = comm;
    d->size = d->comm->size();
    d->buffers.resize(d->size);
    d->locks.resize(d->size);
    d->locked.resize(d->size);

    for(qlonglong i = 0; i < d->size; ++i) {
        d->locks[i] = new QReadWriteLock;
        d->locked[i].store(0);
    }
}

inline qthDistributedBufferManager::~qthDistributedBufferManager(void)
{
    for(qlonglong i = 0; i < d->size; ++i) {
        delete d->locks[i];
    }
    delete d;
    d = 0;
}

inline void *qthDistributedBufferManager::allocate(qlonglong objectSize, qlonglong capacity, int metatype_id)
{
    Q_UNUSED(metatype_id);

    if (capacity == 0)
        return NULL;

    char *buffer;
    d->comm->barrier();
    d->object_size = objectSize;
    qlonglong wid = d->comm->wid();
    d->locks[wid]->lockForWrite();
    d->buffers[wid] = static_cast<char*>(::malloc(objectSize * capacity));
    buffer = d->buffers[wid];
    d->locks[wid]->unlock();
    d->comm->barrier();

    return buffer;
}

inline void qthDistributedBufferManager::deallocate(void *buffer, qlonglong objectSize)
{
    Q_ASSERT(d->object_size == objectSize);

    if (!buffer)
        return;

    d->comm->barrier();
    qlonglong wid = d->comm->wid();
    if (d->buffers[wid] == buffer) {
        d->locks[wid]->lockForWrite();
        ::free(d->buffers[wid]);
        d->locks[wid]->unlock();
        d->object_size = 0;
    }
    d->comm->barrier();
}

inline bool qthDistributedBufferManager::shouldCache(const qint32& owner)
{
    return false;
}

inline void qthDistributedBufferManager::rlock(void)
{
    d->comm->barrier();
    qlonglong wid = d->comm->wid();
    if (d->locked[wid].testAndSetRelaxed(0,1)) {
        d->locks[wid]->lockForRead();
    }
    d->comm->barrier();
}

inline void qthDistributedBufferManager::rlock(qlonglong wid)
{
    if (d->locked[wid].testAndSetRelaxed(0,1)) {
        d->locks[wid]->lockForRead();
    }
}


inline void qthDistributedBufferManager::wlock(void)
{
    d->comm->barrier();
    qlonglong wid = d->comm->wid();
    if (d->locked[wid].testAndSetRelaxed(0,1)) {
        d->locks[wid]->lockForWrite();
    }
    d->comm->barrier();
}

inline void qthDistributedBufferManager::wlock(qlonglong wid)
{
    d->locked[wid].store(1);
    d->locks[wid]->lockForWrite();
}

inline void qthDistributedBufferManager::unlock(qlonglong wid)
{
    d->locks[wid]->unlock();
    d->locked[wid].store(0);
}

inline void qthDistributedBufferManager::unlock(void)
{
    d->comm->barrier();
    qlonglong wid = d->comm->wid();
    if (d->locked[wid].testAndSetRelaxed(1,0)) {
        d->locks[wid]->unlock();
    }
    d->comm->barrier();
}

inline bool qthDistributedBufferManager::locked(qlonglong wid)
{
    return (d->locked[wid].load() == 1);
}

inline void qthDistributedBufferManager::get(qint32 from, qlonglong position, void *array, qlonglong nelements)
{
    Q_ASSERT((from >= 0 || from < d->comm->size()));

    char *buffer = d->buffers[from];
    int locked = d->locked[from].load();

    if (!locked) {
        QReadWriteLock *lock = d->locks[from];
        lock->lockForRead();
        memcpy(array, buffer + position * d->object_size, d->object_size * nelements);
        lock->unlock();
    } else {
        memcpy(array, buffer + position * d->object_size, d->object_size * nelements);
    }
}

inline void qthDistributedBufferManager::put(qint32 dest, qlonglong position, void *array, qlonglong nelements)
{
    Q_ASSERT((dest >= 0 || dest < d->comm->size()));
    char *buffer = d->buffers[dest];
    int locked = d->locked[dest].load();

    if (!locked) {
        QReadWriteLock *lock = d->locks[dest];
        lock->lockForWrite();
        memcpy(buffer + position * d->object_size, array, d->object_size * nelements);
        lock->unlock();
    } else {
        memcpy(buffer + position * d->object_size, array, d->object_size * nelements);
    }
}

inline void qthDistributedBufferManager::addAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements)
{
    Q_ASSERT((dest >= 0 || dest < d->comm->size()));
    char *buffer = d->buffers[dest];
    int locked = d->locked[dest].load();

    if (!locked) {
        QReadWriteLock *lock = d->locks[dest];
        lock->lockForWrite();
        this->operation_manager->addAssign(buffer + position * d->object_size, array, nelements);
        lock->unlock();
    } else {
        this->operation_manager->addAssign(buffer + position * d->object_size, array, nelements);
    }
}

inline void qthDistributedBufferManager::subAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements)
{
    Q_ASSERT((dest >= 0 || dest < d->comm->size()));
    char *buffer = d->buffers[dest];
    int locked = d->locked[dest].load();

    if (!locked) {
        QReadWriteLock *lock = d->locks[dest];
        lock->lockForWrite();
        this->operation_manager->subAssign(buffer + position * d->object_size, array, nelements);
        lock->unlock();
    } else {
        this->operation_manager->subAssign(buffer + position * d->object_size, array, nelements);
    }
}

inline void qthDistributedBufferManager::mulAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements)
{
    Q_ASSERT((dest >= 0 || dest < d->comm->size()));
    char *buffer = d->buffers[dest];
    int locked = d->locked[dest].load();

    if (!locked) {
        QReadWriteLock *lock = d->locks[dest];
        lock->lockForWrite();
        this->operation_manager->mulAssign(buffer + position * d->object_size, array, nelements);
        lock->unlock();
    } else {
        this->operation_manager->mulAssign(buffer + position * d->object_size, array, nelements);
    }
}

inline void qthDistributedBufferManager::divAssign(qint32 dest, qlonglong position, void *array, qlonglong nelements)
{
    Q_ASSERT((dest >= 0 || dest < d->comm->size()));
    char *buffer = d->buffers[dest];
    int locked = d->locked[dest].load();

    if (!locked) {
        QReadWriteLock *lock = d->locks[dest];
        lock->lockForWrite();
        this->operation_manager->divAssign(buffer + position * d->object_size, array, nelements);
        lock->unlock();
    } else {
        this->operation_manager->divAssign(buffer + position * d->object_size, array, nelements);
    }
}

inline bool qthDistributedBufferManager::canHandleOperationManager(void)
{    
    return (d->comm->wid() == 0);
}

// 
// qthDistributedBufferManager.h ends here
