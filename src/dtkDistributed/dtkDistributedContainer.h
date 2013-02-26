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

#include <dtkDistributed>

class dtkDistributedMode;
class dtkDistributedPolicy;

template<typename T> class dtkDistributedIterator;

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer interface
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicator;
class dtkDistributedMapper;

template<typename T> class dtkDistributedContainer
{
public:
             dtkDistributedContainer(void) {;}
    virtual ~dtkDistributedContainer(void) {;}

public:
    // virtual void   setMode(dtkDistributedMode     *mode) {   Q_UNUSED(mode); }
    // virtual void setPolicy(dtkDistributedPolicy *policy) { Q_UNUSED(policy); }

public:
    virtual void clear(void) = 0;

public:
    virtual bool empty(void) const = 0;
    
public:
    virtual qlonglong count(void) const = 0;
    
public:
    // virtual dtkDistributedIterator<T>& iterator(void) = 0;
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedIterator interface
// ///////////////////////////////////////////////////////////////////

// template<typename T> class dtkFuture;

template<typename T> class dtkDistributedIterator
{
public:
             dtkDistributedIterator(void) {;}
    virtual ~dtkDistributedIterator(void) {;}

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
