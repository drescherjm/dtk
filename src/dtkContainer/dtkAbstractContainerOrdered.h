/* dtkAbstractContainerOrdered.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 14:57:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 11:43:38 2012 (+0200)
 *           By: tkloczko
 *     Update #: 49
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */
 
#ifndef DTKABSTRACTCONTAINERORDERED_H
#define DTKABSTRACTCONTAINERORDERED_H

#include "dtkAbstractContainer.h"
#include "dtkContainerExport.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer interface
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCONTAINER_EXPORT dtkAbstractContainerOrdered : public dtkAbstractContainer<T>
{
public:
     dtkAbstractContainerOrdered(void);
     dtkAbstractContainerOrdered(const dtkAbstractContainerOrdered<T>& other);
    ~dtkAbstractContainerOrdered(void);

public:
    dtkContainerType type(void) const;

    void add(const T& value);
    void add(const dtkAbstractContainer<T>& values);

public:
    virtual void append(const T& value) = 0;
    virtual void append(const dtkAbstractContainer<T>& values) = 0;

    virtual void prepend(const T& value) = 0;
    virtual void prepend(const dtkAbstractContainer<T>& values) = 0;
    
    virtual void insert(dtkxarch_int index, const T& value) = 0;
    virtual void insert(dtkxarch_int from, const dtkAbstractContainer<T>& values) = 0;
    virtual void insert(dtkxarch_int from, dtkxarch_int step, const dtkAbstractContainer<T>& values) = 0;
    virtual void insert(dtkxarch_int *indices, const dtkAbstractContainer<T>& values) = 0;
    
    virtual void replace(dtkxarch_int index, const T& value) = 0;
    virtual void replace(dtkxarch_int from, const dtkAbstractContainer<T>& values) = 0;
    virtual void replace(dtkxarch_int from, dtkxarch_int step, const dtkAbstractContainer<T>& values) = 0;
    virtual void replace(dtkxarch_int *indices, const dtkAbstractContainer<T>& values) = 0;

    virtual void removeAt(dtkxarch_int index) = 0;
    virtual void removeAt(dtkxarch_int from, dtkxarch_int to, dtkxarch_int step = 1) = 0;

public:
    virtual dtkxarch_int     indexOf(const T& value, dtkxarch_int from = 0)  const = 0;
    virtual dtkxarch_int lastIndexOf(const T& value, dtkxarch_int from = -1) const = 0;

    virtual dtkxarch_int *indicesOf(const T& value, dtkxarch_int from = 0) const = 0;

    virtual const T& at(dtkxarch_int index) const = 0;

    virtual dtkAbstractContainerOrdered<T> *subContainer(const dtkAbstractContainerOrdered<dtkxarch_int>& indices)  const = 0;
    virtual dtkAbstractContainerOrdered<T> *subContainer(dtkxarch_int from, dtkxarch_int to, dtkxarch_int step = 1) const = 0;

public:
    virtual const T& operator [] (dtkxarch_int index) const = 0;
    virtual       T& operator [] (dtkxarch_int index)       = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainerOrdered implementation
// /////////////////////////////////////////////////////////////////

#include "dtkAbstractContainerOrdered.tpp"

#endif
