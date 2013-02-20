/* dtkDistributedContainer.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:08:23 2013 (+0100)
 * Version: 
 * Last-Updated: mer. févr. 20 10:43:08 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 229
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

public:
     dtkDistributedLocalIterator(dtkDistributedContainer<T>& container) : c(container), i(c.m_buffer) {;}
    ~dtkDistributedLocalIterator(void) {;}

public:
    void            toBack(void) { i = c.m_buffer + c.m_buffer_size; }
    void           toFront(void) { i = c.m_buffer; }
    bool           hasNext(void) { return ( i != (c.m_buffer + c.m_buffer_size) ); }
    bool       hasPrevious(void) { return ( i != c.m_buffer ); }
    const T&          next(void) { const T *n = i; ++i; return *n; }
    const T&      previous(void) { return *(--i); }
    const T&      peekNext(void) { return *i; }
    const T&  peekPrevious(void) { const T *p = i; return *(--p); }
    qlonglong   localIndex(void) { return ( i - c.m_buffer ); }
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedIterator
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedIterator
{
    dtkDistributedContainer<T>& c;
    const T *i;
    qlonglong gid;

public:
     dtkDistributedIterator(dtkDistributedContainer<T>& container) : c(container), i(c.m_buffer), gid(0) {;}
    ~dtkDistributedIterator(void) {;}

public:
    void            toBack(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
                i = c.m_buffer + c.m_buffer_size;
                break;;
        case dtkDistributed::Global:
            if (c.worker()->master())
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
            if (c.worker()->master())
                return ( gid < c.m_global_size );
            else
                return false;
            break;;
        }
    }

    bool       hasPrevious(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return ( i != c.m_buffer );
            break;;
        case dtkDistributed::Global:
            if (c.worker()->master())
                return ( gid > 0 );
            else
                return false;
            break;;
        }
    }

    T          next(void) {
        const T *n = i;
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            ++i;
            return *n;
            break;;
        case dtkDistributed::Global:
            if (c.worker()->master())
                return c.at(gid++);
            else
                return *n; //FIXME
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
            if (c.worker()->master())
                return c.at(--gid);
            else
                return empty;
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
            if (c.worker()->master())
                return c.at(gid);
            else
                return empty;
            break;;
        }
    }

    T  peekPrevious(void) {
        const T *p = i;
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return *(--p);
            break;;
        case dtkDistributed::Global:
            if (c.worker()->master())
                return c.at(gid-1);
            else
                return NULL;
            break;;
        }
 }

    qlonglong   index(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return ( i - c.m_buffer );
            break;;
        case dtkDistributed::Global:
            if (c.worker()->master())
                return gid;
            else
                return -1;
            break;;
        }
    }

    qlonglong   globalIndex(void) {
        switch (dtkDistributed::mode()) {
        case dtkDistributed::Local:
            return ( c.m_mapper->localToGlobal(i - c.m_buffer, c.m_worker->wid()));
            break;;
        case dtkDistributed::Global:
            if (c.worker()->master())
                return gid;
            else
                return -1;
            break;;
        }
    }

};


// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedContainer.tpp"
