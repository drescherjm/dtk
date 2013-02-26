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

class dtkDistributedCommunicator;

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArray : public dtkDistributedContainerIndexed<T>, public dtkDistributedContainerSequence<T>
{
public:
     dtkDistributedArray(const qlonglong& count);
     dtkDistributedArray(const dtkDistributedArray<T>& other);
    ~dtkDistributedArray(void);

public:
    QString identifier(void) const;

public:
    dtkDistributedArray<T> *clone(void);

// public:
//     dtkDistributedArray<T>& operator = (const dtkDistributedArray<T>& other) { this->copy(other); return *this; }

// protected:
//    void copy(const dtkDistributedContainer<T>& other);

// public:
//     bool operator == (const dtkDistributedArray<T>& other) const;
//     bool operator != (const dtkDistributedArray<T>& other) const;

// protected:
//    bool equal(const dtkDistributedContainer<T>& other) const;

// public:
//     void   setMode(dtkDistributedMode     *mode); // register data manager to a given mode
//     void setPolicy(dtkDistributedPolicy *policy); // register data manager to a given policy

public:
    void clear(void);
    
public:
    bool empty(void) const;

public:
    qlonglong count(void) const;

// public:
//     void set(const qlonglong& global_id, const T& value);

// public:
//     T at(const qlonglong& global_id) const;

// public:
//     dtkDistributedIterator<T>& iterator(void);

private:
    qlonglong m_count;
    qlonglong m_buffer_count;

public:
    dtkDistributedArrayHandler<T> handler;
    
    friend class dtkDistributedArrayHandler<T>;

private:
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"
