/* dtkDistributedContainer.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Feb  5 14:08:23 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Thu Feb  7 17:13:21 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 56
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore/QVector>

// ///////////////////////////////////////////////////////////////////
// dtkDistributedContainer
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedContainer;

// ///////////////////////////////////////////////////////////////////
// dtkDistributedLocalIterator
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedGlobalIterator
{
public:
    qlonglong globalIndex(void) const {return 0;}

public:
    bool     hasNext(void) {return false;}

public:
    const T&     next(void) {return *new T();}
    
};

// ///////////////////////////////////////////////////////////////////
// dtkDistributedLocalIterator
// ///////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedLocalIterator
{
public:
     dtkDistributedLocalIterator(dtkDistributedContainer<T>& container);
    ~dtkDistributedLocalIterator(void);

public:    
    void  toBack(void);
    void toFront(void);

public:
    bool     hasNext(void);
    bool hasPrevious(void);

public:
    const T&     next(void);
    const T& previous(void);

public:
    const T&     peekNext(void);
    const T& peekPrevious(void);

public:
    qlonglong  localIndex(void) const;
    qlonglong globalIndex(void) const;

private:
    dtkDistributedContainer<T>& c;
    typedef typename QVector<T>::const_iterator const_iterator;
    const_iterator i;
    qlonglong m_index;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer interface
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicator;
class dtkDistributedMapper;

template<typename T> class dtkDistributedContainer
{
public:
     dtkDistributedContainer(void);
     dtkDistributedContainer(const qlonglong& size, dtkDistributedCommunicator *communicator);

public:
    ~dtkDistributedContainer(void);

private:
    void allocate(void);

public:
    void resize(const qlonglong& size);

    qlonglong size(void) const;

public:
    void set(const qlonglong& global_id, const T& value);
    void setLocal(const qlonglong& local_id, const T& value);

public:
    T at(const qlonglong& global_id);

    const T& localAt(const qlonglong& local_id);

public:
    dtkDistributedLocalIterator<T>& localIterator(void);
    dtkDistributedGlobalIterator<T>& globalIterator(void) { return *new dtkDistributedGlobalIterator<T>();}

private:
    dtkDistributedMapper *m_mapper;
    dtkDistributedCommunicator *m_comm;

private:
    T *m_buffer;
    qlonglong m_buffer_id;

    T *m_temp;

    QVector<T> m_array;
    dtkDistributedLocalIterator<T> *m_iterator;

public:
    friend class dtkDistributedLocalIterator<T>;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedContainer.tpp"
