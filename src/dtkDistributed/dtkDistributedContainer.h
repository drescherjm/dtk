/* dtkDistributedContainer.h ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:08:23 2013 (+0100)
 */

/* Change Log:
 *
 */

#pragma once

#include <dtkDistributed>

template<typename T> class       dtkDistributedIterator;
template<typename T> class  dtkDistributedLocalIterator;
template<typename T> class dtkDistributedGlobalIterator;

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer interface
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicator;
class dtkDistributedMapper;
class dtkDistributedWorker;

template<typename T> class dtkDistributedContainer
{
public:
     dtkDistributedContainer(const qlonglong& size, dtkDistributedWorker *worker);

public:
    ~dtkDistributedContainer(void);

private:
    void   allocate(void);
    void deallocate(void);

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
    dtkDistributedIterator<T>& iterator(void);

private:
    dtkDistributedMapper *m_mapper;
    dtkDistributedCommunicator *m_comm;
    dtkDistributedWorker *m_worker;

private:
    T *m_buffer;
    qlonglong m_buffer_size;
    qlonglong m_buffer_id;

    qlonglong m_global_size;

    T *m_temp;

public:
    dtkDistributedIterator<T>            *m_it;
    dtkDistributedLocalIterator<T>   *m_loc_it;
    dtkDistributedGlobalIterator<T> *m_glob_it;

public:
    friend class       dtkDistributedIterator<T>;
    friend class  dtkDistributedLocalIterator<T>;
    friend class dtkDistributedGlobalIterator<T>;

    dtkDistributedWorker *worker(void) { return m_worker; };
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
    qlonglong wid;

public:
     dtkDistributedLocalIterator(dtkDistributedContainer<T>& container) : c(container), i(c.m_buffer) { wid =  c.m_worker->wid();}
    ~dtkDistributedLocalIterator(void) {;}

public:
    void            toBack(void) { i = c.m_buffer + c.m_buffer_size; }
    void           toFront(void) { i = c.m_buffer; }
    bool           hasNext(void) { return ( i != (c.m_buffer + c.m_buffer_size) ); }
    bool       hasPrevious(void) { return ( i != c.m_buffer ); }
    const T&          next(void) { return *(++i); }
    const T&      previous(void) { return *(--i); }
    const T&      peekNext(void) { return *i; }
    const T&  peekPrevious(void) { const T *p = i; return *(--p); }
    qlonglong   localIndex(void) { return ( i - c.m_buffer ); }
    qlonglong  globalIndex(void) { return ( c.m_mapper->localToGlobal(i - c.m_buffer, wid)); }
    qlonglong        index(void) { return ( i - c.m_buffer ); }
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedIterator
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedIterator
{
    dtkDistributedContainer<T>& c;
    const T *i;
    qlonglong gid;
    qlonglong wid;
    bool master;

public:
    dtkDistributedIterator(dtkDistributedContainer<T>& container) : c(container), i(c.m_buffer), gid(0) {
           wid = c.m_worker->wid();
        master = c.worker()->master();
    }
    ~dtkDistributedIterator(void) {;}

public:
    void            toBack(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
                i = c.m_buffer + c.m_buffer_size;
                break;;
        case dtkDistributed::Global:
            if (master)
                gid = c.m_global_size;
            else
                gid = 0;
            break;;
        }
    }

    void           toFront(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
                i = c.m_buffer;
                break;;
        case dtkDistributed::Global:
                gid = 0;
                break;;
        }
    }

    bool           hasNext(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return ( i != (c.m_buffer + c.m_buffer_size) );
            break;;
        case dtkDistributed::Global:
            return (master) ?( gid < c.m_global_size ) : false;
            break;;
        }
    }

    bool       hasPrevious(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return ( i != c.m_buffer );
            break;;
        case dtkDistributed::Global:
            return (master) ?( gid > 0 ) : false;
            break;;
        }
    }

    T          next(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            ++i;
            return *i;
            break;;
        case dtkDistributed::Global:
            if (master)
                return c.at(gid++);
            else
                return *i; //FIXME
            break;;
        }
    }

    T      previous(void) {
        T empty;
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return *(--i);
            break;;
        case dtkDistributed::Global:
            return (master) ? c.at(--gid) : empty;
            break;;
        }
    }

    T      peekNext(void) {
        T empty;
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return *i;
            break;;
        case dtkDistributed::Global:
            return (master) ? c.at(gid) : empty;
            break;;
        }
    }

    T  peekPrevious(void) {
        const T *p = i;
        T empty;
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return *(--p);
            break;;
        case dtkDistributed::Global:
            return (master) ? c.at(gid-1) : empty;
            break;;
        }
 }

    qlonglong   index(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return ( i - c.m_buffer );
            break;;
        case dtkDistributed::Global:
            return (master) ? gid : -1;
            break;;
        }
    }

    qlonglong   globalIndex(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return ( c.m_mapper->localToGlobal(i - c.m_buffer, wid));
            break;;
        case dtkDistributed::Global:
            return (master) ? gid : -1;
            break;;
        }
    }

};


// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedContainer.tpp"
