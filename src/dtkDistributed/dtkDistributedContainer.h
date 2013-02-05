/* dtkDistributedContainer.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb  4 15:59:05 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTAINER_H
#define DTKDISTRIBUTEDCONTAINER_H

template<typename T> class dtkDistributedContainer;

// /////////////////////////////////////////////////////////////////
// dtkDistributedLocalIterator interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedLocalIterator
{
public:
     dtkDistributedLocalIterator(dtkDistributedContainer<T> *container);
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
    dtkDistributedContainer<T> *c;
    typedef typename QVector<T>::const_iterator const_iterator;
    const_iterator i;
    qlonglong m_index;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer interface
// /////////////////////////////////////////////////////////////////

template<typename T> class dtkDistributedContainer
{
public:
     dtkDistributedContainer(void);
    ~dtkDistributedContainer(void);

public:
    void resize(const qlonglong& size);

    qlonglong size(void) const;

public:
    void set(const qlonglong& index, const T& value);

public:
    const T& at(const qlonglong& index);

public:
    dtkDistributedLocalIterator<T> *localIterator(void);

private:
    QVector<T> m_array;    
    dtkDistributedLocalIterator<T> *m_iterator;

public:
    friend class dtkDistributedLocalIterator<T>;
};

// /////////////////////////////////////////////////////////////////
// Implementations
// /////////////////////////////////////////////////////////////////

#include "dtkDistributedContainer.tpp"

#endif
