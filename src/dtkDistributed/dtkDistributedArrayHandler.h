/* dtkDistributedArrayHandler.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb 18 10:24:22 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

template <typename T> class dtkDistributedArray;
template <typename T> class dtkDistributedArrayHandler;

class dtkDistributedCommunicator;
class dtkDistributedMapper;
class dtkDistributedWorker;

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedArrayHandler
{
public:
    inline  dtkDistributedArrayHandler(dtkDistributedArray<T> *array, const qlonglong& count, dtkDistributedWorker *worker);
    inline ~dtkDistributedArrayHandler(void);

public:
    void initialize(void);
    
public:
    inline void  setLocalMode(void);
    inline void setGlobalMode(void);

public:
    inline void clear(void);

    inline bool empty(void) const;

    inline qlonglong count(void) const;

public:
    inline void set(const qlonglong& index, const T& value);

public:
    inline T at(const qlonglong& index) const;

public:
    inline T first(void) const;
    inline T  last(void) const;

public:
    inline dtkDistributedIterator<T> iterator(void);

public:
    inline qlonglong localToGlobal(const qlonglong& index);

// /////////////////////////////////////////////////////////////////

protected:
    typedef      void (dtkDistributedArrayHandler<T>::*clearMethodPointer)(void);
    typedef      bool (dtkDistributedArrayHandler<T>::*emptyMethodPointer)(void) const;
    typedef qlonglong (dtkDistributedArrayHandler<T>::*countMethodPointer)(void) const;

protected:
    clearMethodPointer clearMethod;
    emptyMethodPointer emptyMethod;
    countMethodPointer countMethod;

protected:
    void  clearLocal(void) { qDebug() << "I am  locally cleared"; }
    void clearGlobal(void) { qDebug() << "I am globally cleared"; }

    bool  emptyLocal(void) const { return !static_cast<bool>(m_buffer_count); }
    bool emptyGlobal(void) const { return !static_cast<bool>(m_count); }

    qlonglong  countLocal(void) const { return m_buffer_count; }
    qlonglong countGlobal(void) const { return m_count; }

// /////////////////////////////////////////////////////////////////

protected:
    typedef void (dtkDistributedArrayHandler<T>::*setMethodPointer)(const qlonglong& index, const T& value);
    typedef T (dtkDistributedArrayHandler<T>::*atMethodPointer)(const qlonglong& index) const;
    typedef T (dtkDistributedArrayHandler<T>::*atLimitMethodPointer)(void) const;

protected:
    setMethodPointer setMethod;
    atMethodPointer   atMethod;

    atLimitMethodPointer firstMethod;
    atLimitMethodPointer  lastMethod;

protected:
    void  setLocal(const qlonglong& index, const T& value) { m_buffer[index]= value; }
    void setGlobal(const qlonglong& index, const T& value);

    T  atLocal(const qlonglong& index) const { return m_buffer[index]; }
    T atGlobal(const qlonglong& index) const;

    T  firstLocal(void) const { return *(m_buffer); }
    T firstGlobal(void) const { return this->atGlobal(0); }

    T  lastLocal(void) const { return *(m_buffer + m_buffer_count - 1); }
    T lastGlobal(void) const { return this->atGlobal(m_count - 1); }

// /////////////////////////////////////////////////////////////////

private:
    qlonglong m_wid;
    qlonglong m_count;
    qlonglong m_buffer_id;
    qlonglong m_buffer_count;

    T *m_buffer;

// /////////////////////////////////////////////////////////////////

private:
    dtkDistributedMapper *m_mapper;
    dtkDistributedWorker *m_worker;
    dtkDistributedCommunicator *m_comm;

private:
    friend class dtkDistributedArray<T>;
    dtkDistributedArray<T> *m_array;
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedIteratorArrayLocal interface
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedIteratorArrayPrivate : public dtkDistributedIteratorPrivate<T>
{
public:
    dtkDistributedArrayHandler<T>& h;
    qlonglong id;

public:
    inline  dtkDistributedIteratorArrayPrivate(dtkDistributedArrayHandler<T>& handler) : h(handler), id(0) {;}
    inline ~dtkDistributedIteratorArrayPrivate(void) {;}

public:
    inline void    toFirst(void) { id = 0; }
    inline void     toLast(void) { id = h.count(); }
    inline void     toNext(void) { ++id; }
    inline void toPrevious(void) { --id; }
    
public:
    inline bool     hasNext(void) { return ( id < h.count() ); }
    inline bool hasPrevious(void) { return ( id > 0); }

public:
    inline qlonglong index(void) { return id; }

public:
    inline T  current(void) { return h.at(id); }
    inline T     next(void) { return h.at(id + 1); }
    inline T previous(void) { return h.at(id - 1); }

public:
    inline bool findBackward(const T& value) { while(id > 0) if (value == h.at(id--)) return true; return false; }  
    inline bool  findForward(const T& value) { qlonglong count = h.count(); while(id < count) if (value == h.at(id++)) return true; return false; }
};

// /////////////////////////////////////////////////////////////////

#include "dtkDistributedArrayHandler.tpp"
