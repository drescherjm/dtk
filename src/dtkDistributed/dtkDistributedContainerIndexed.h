/* dtkDistributedContainerIndexed.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Wed Feb 13 15:53:54 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkDistributedContainer.h"

template<typename T> class dtkFuture;

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainerIndexed interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedContainerIndexed : public virtual dtkDistributedContainer<T>
{
public:
             dtkDistributedContainerIndexed(void) : dtkDistributedContainer<T>() {;}
             dtkDistributedContainerIndexed(const dtkDistributedContainerIndexed<T>& other) : dtkDistributedContainer<T>(other) {;}
    virtual ~dtkDistributedContainerIndexed(void) {;}

public:
    // virtual void resize(const qlonglong& size) = 0;

    // virtual void      set(const qlonglong& global_id, const T& value) = 0;
    // virtual void localSet(const qlonglong&  local_id, const T& value) = 0;

    // virtual void      insert(const qlonglong& global_id, const T& value) = 0;
    // virtual void localInsert(const qlonglong&  local_id, const T& value) = 0;

    // virtual void removeAt(const qlonglong& global_id) = 0;

    // virtual void futureInsert(const qlonglong& global_id, const T& value) = 0;

public:
    // virtual       T       at(const qlonglong& global_id) const = 0;
    // virtual const T& localAt(const qlonglong&  local_id) const = 0;

public:
    //virtual dtkFuture<T> futureAt(const qlonglong& global_id) const = 0;
};
