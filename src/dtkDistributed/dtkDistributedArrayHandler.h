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

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedArrayHandler
{
public:
    dtkDistributedArrayHandler(void) : m_wid(-1), m_count(-1), m_buffer_id(-1), m_buffer_count(-1), m_buffer(0), m_comm(0) {;}

public:
    void initialize(dtkDistributedCommunicator *communicator, const qlonglong& wid, const qlonglong& count, const qlonglong& buffer_count, const qlonglong& buffer_id); 
    
public:
    inline void  setLocalMode(void);
    inline void setGlobalMode(void);

public:
    inline void clear(void);

    inline bool empty(void) const;

    inline qlonglong count(void) const;

// /////////////////////////////////////////////////////////////////

protected:
    typedef void (dtkDistributedArrayHandler<T>::*clearMethodPointer)(void);
    typedef bool (dtkDistributedArrayHandler<T>::*emptyMethodPointer)(void) const;
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

private:
    qlonglong m_wid;
    qlonglong m_count;
    qlonglong m_buffer_id;
    qlonglong m_buffer_count;

    T *m_buffer;

// /////////////////////////////////////////////////////////////////

private:
    dtkDistributedCommunicator *m_comm;
};

// /////////////////////////////////////////////////////////////////

#include "dtkDistributedArrayHandler.tpp"
