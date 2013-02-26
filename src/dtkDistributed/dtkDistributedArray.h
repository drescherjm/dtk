/* dtkDistributedArray.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Wed Feb 13 22:49:34 (+0100)
 */

/* Commentary: 
 *
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkDistributedContainerIndexed.h"
#include "dtkDistributedContainerSequence.h"
#include "dtkDistributedArrayHandler.h"

class dtkDistributedMapper;
class dtkDistributedWorker;

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArray : public dtkDistributedContainerIndexed<T>, public dtkDistributedContainerSequence<T>
{
public:
     dtkDistributedArray(const qlonglong& count, dtkDistributedWorker *worker);
    ~dtkDistributedArray(void);

public:
    void clear(void);
    
public:
    bool empty(void) const;

public:
    qlonglong count(void) const;

private:
    dtkDistributedMapper *m_mapper;
    dtkDistributedWorker *m_worker;

public:
    dtkDistributedArrayHandler<T> m_handler;
    
    friend class dtkDistributedArrayHandler<T>;

private:
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"
