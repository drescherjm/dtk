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
#include "dtkDistributedArrayItem.h"

class dtkDistributedMapper;
class dtkDistributedWorker;

// /////////////////////////////////////////////////////////////////
// dtkDistributedArray interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedArray : public dtkDistributedContainerIndexed<T>, public dtkDistributedContainerSequence<T>
{
public:
     inline  dtkDistributedArray(const qlonglong& count, dtkDistributedWorker *worker);
     inline ~dtkDistributedArray(void);

public:
    inline void clear(void);
    
public:
    inline bool empty(void) const;

public:
    inline qlonglong count(void) const;

public:
    inline void set(const qlonglong& index, const T& value);

public:
    inline T at(const qlonglong& index) const;

public:
    inline T first(void) const;
    inline T  last(void) const;

public:
    inline dtkDistributedItem<T> operator [] (const qlonglong& index);

public:
    inline dtkDistributedIterator<T> iterator(void);

public:
    inline qlonglong localToGlobal(const qlonglong& index);

public:
    dtkDistributedArrayHandler<T> *m_handler;
    
    friend class dtkDistributedArrayHandler<T>;

private:
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"
