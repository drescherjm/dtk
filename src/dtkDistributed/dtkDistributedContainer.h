/* dtkDistributedContainer.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:08:23 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Fri Feb  8 16:18:41 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 123
 */

/* Change Log:
 * 
 */

#pragma once

template<typename T> class  dtkDistributedLocalIterator;
template<typename T> class dtkDistributedGlobalIterator;

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer interface
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicator;
class dtkDistributedMapper;

template<typename T> class dtkDistributedContainer
{
public:
     dtkDistributedContainer(const qlonglong& size, dtkDistributedCommunicator *communicator);

public:
    ~dtkDistributedContainer(void);

private:
    void allocate(void);

public:
    qlonglong size(void) const;

public:
    void set(const qlonglong& global_id, const T& value);
    void setLocal(const qlonglong& local_id, const T& value);

public:
    T at(const qlonglong& global_id);

    const T& localAt(const qlonglong& local_id);

public:
    dtkDistributedLocalIterator<T>&   localIterator(void);
    dtkDistributedGlobalIterator<T>& globalIterator(void);

private:
    dtkDistributedMapper *m_mapper;
    dtkDistributedCommunicator *m_comm;

private:
    T *m_buffer;
    qlonglong m_buffer_size;
    qlonglong m_buffer_id;

    qlonglong m_global_size;

    T *m_temp;

public:
    dtkDistributedLocalIterator<T>   *m_loc_it;
    dtkDistributedGlobalIterator<T> *m_glob_it;

public:
    friend class  dtkDistributedLocalIterator<T>;
    friend class dtkDistributedGlobalIterator<T>;
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedGlobalIterator 
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedGlobalIterator
{
    dtkDistributedContainer<T>& c;
    qlonglong gid;

public:
    dtkDistributedGlobalIterator(dtkDistributedContainer<T>& container) : c(container), gid(0) {;}
    ~dtkDistributedGlobalIterator(void) {;}

public:
    void            toBack(void) { gid = c.m_global_size; }
    void           toFront(void) { gid = 0; }
    bool           hasNext(void) { return ( gid < c.m_global_size ); }
    bool       hasPrevious(void) { return ( gid > 0 ); }
    T                 next(void) { return c.at(gid++); }
    T             previous(void) { return c.at(--gid); }
    T             peekNext(void) { return c.at(gid); }
    T         peekPrevious(void) { return c.at(gid-1); }
    qlonglong  globalIndex(void) { return gid; }    
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedLocalIterator
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedLocalIterator
{
    dtkDistributedContainer<T>& c;
    const T *i;

public:
     dtkDistributedLocalIterator(dtkDistributedContainer<T>& container) : c(container), i(c.m_buffer) {;}
    ~dtkDistributedLocalIterator(void) {;}

public:
    void            toBack(void) { i = c.m_buffer + c.m_buffer_size; }
    void           toFront(void) { i = c.m_buffer; }
    bool           hasNext(void) { return ( i != (c.m_buffer + c.m_buffer_size) ); }
    bool       hasPrevious(void) { return ( i != c.m_buffer ); }
    const T&          next(void) { return *(i++); }
    const T&      previous(void) { return *(--i); }
    const T&      peekNext(void) { return *i; }
    const T&  peekPrevious(void) { const T *p = i; return *(--p); }
    qlonglong   localIndex(void) { return ( i - c.m_buffer ); }
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedContainer.tpp"
