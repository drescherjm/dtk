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
            ~dtkDistributedArray(void);

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
    //inline dtkDistributedItem<T> first(void);
    inline                         T  first(void) const;

    //inline dtkDistributedItem<T> last(void);
    inline                         T  last(void) const;

public:
    inline dtkDistributedItem<T> operator [] (const qlonglong& index);
    //inline                         T  operator [] (const qlonglong& index) const;

public:
    //dtkDistributedIterator<T>& constIterator(void) const;

public:
    inline dtkDistributedMapper *mapper(void);

public:
    dtkDistributedArrayHandler<T> *m_handler;
    
    friend class dtkDistributedArrayHandler<T>;

private:
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.tpp"
