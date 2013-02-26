/* dtkDistributedContainerSequence.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Thu Feb 14 08:36:47 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkDistributedContainer.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainerSequence interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedContainerSequence : public virtual dtkDistributedContainer<T>
{
public:
             dtkDistributedContainerSequence(void) : dtkDistributedContainer<T>() {;}
             dtkDistributedContainerSequence(const dtkDistributedContainerSequence<T>& other) : dtkDistributedContainer<T>(other) {;}
    virtual ~dtkDistributedContainerSequence(void) {;}

/* public: */
/*     virtual void      append(const T& value) = 0; */
/*     virtual void localAppend(const T& value) = 0; */

/*     virtual void      prepend(const T& value) = 0; */
/*     virtual void localPrepend(const T& value) = 0; */

/*     virtual void      removeFirst(void) = 0; */
/*     virtual void localRemoveFirst(void) = 0; */

/*     virtual void      removeLast(void) = 0; */
/*     virtual void localRemoveLast(void) = 0; */

/*     virtual bool      remove(const T& value) = 0; */
/*     virtual bool localRemove(const T& value) = 0; */

/* public: */
/*     virtual       T       first(void) const = 0; */
/*     virtual const T& localFirst(void) const = 0; */

/*     virtual       T       last(void) const = 0; */
/*     virtual const T& localLast(void) const = 0; */

/*     virtual T      takeFirst(void) = 0; */
/*     virtual T localTakeFirst(void) = 0; */

/*     virtual T      takeLast(void) = 0; */
/*     virtual T localTakeLast(void) = 0; */

public:
    //virtual dtkFuture<T> futureAt(const qlonglong& global_id) const = 0;
};
