/* dtkDistributedContainer.h ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:08:23 2013 (+0100)
 */

/* Commentary: 
 *
 */

/* Change Log:
 *
 */

#pragma once

#include "dtkDistributedWorker.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainerBase interface
// /////////////////////////////////////////////////////////////////

class dtkDistributedContainerBase
{
public:
    virtual ~dtkDistributedContainerBase(void) { ; }

public:
    //virtual void setMode(const dtkDistributed::Mode& mode) = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedIterator;

template<typename T> class dtkDistributedContainer : public dtkDistributedContainerBase
{
public:
             dtkDistributedContainer(void) {;}
    virtual ~dtkDistributedContainer(void) {;}

public:
    virtual void clear(void) = 0;

public:
    virtual bool empty(void) const = 0;

public:
    // virtual bool contains(const T& value) const = 0;
    
public:
    virtual qlonglong count(void) const = 0;
    // virtual qlonglong count(const T& value) const = 0;
    
public:
    virtual dtkDistributedIterator<T> iterator(void) = 0;
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedIterator interface
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedIteratorPrivate
{
public:
    virtual ~dtkDistributedIteratorPrivate(void) {;}

public:
    virtual void    toFirst(void) = 0;
    virtual void     toLast(void) = 0;
    virtual void     toNext(void) = 0;
    virtual void toPrevious(void) = 0;
    
public:
    virtual bool     hasNext(void) = 0;
    virtual bool hasPrevious(void) = 0;

public:
    virtual qlonglong index(void) = 0;

public:
    virtual T  current(void) = 0;
    virtual T     next(void) = 0;
    virtual T previous(void) = 0;

public:
    virtual bool findBackward(const T& value) { return false; }  
    virtual bool  findForward(const T& value) { return false; }
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedIterator interface
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedIterator
{
public:
    inline dtkDistributedIterator(dtkDistributedIteratorPrivate<T> *d_ptr) : d(d_ptr) {;}

public:
    inline ~dtkDistributedIterator(void) { delete d; d = NULL; }

public:
    inline void    toFirst(void) { d->toFirst(); }
    inline void     toLast(void) { d->toLast(); }
    inline void     toNext(void) { d->toNext(); }
    inline void toPrevious(void) { d->toPrevious(); }
    
public:
    inline bool     hasNext(void) { return d->hasNext(); }
    inline bool hasPrevious(void) { return d->hasPrevious(); }

public:
    inline qlonglong index(void) { return d->index(); }

public:
    inline T  current(void) { return d->current(); }
    inline T     next(void) { return d->next(); }
    inline T previous(void) { return d->previous(); }

public:
    inline bool findBackward(const T& value) { return d->findBackward(); }
    inline bool  findForward(const T& value) { return d->findForward(); }

private:
    dtkDistributedIteratorPrivate<T> *d;
};
