/* dtkAbstractContainerOrdered.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 14:57:44 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 13 16:51:49 2012 (+0200)
 *           By: tkloczko
 *     Update #: 50
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
#include "dtkContainerSupportExport.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkAbstractContainerOrdered : public dtkAbstractContainer<T>
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

    virtual void insert(qlonglong index, const T& value) = 0;
    virtual void insert(qlonglong from, const dtkAbstractContainer<T>& values) = 0;
    virtual void insert(qlonglong from, qlonglong step, const dtkAbstractContainer<T>& values) = 0;
    virtual void insert(qlonglong *indices, const dtkAbstractContainer<T>& values) = 0;

    virtual void replace(qlonglong index, const T& value) = 0;
    virtual void replace(qlonglong from, const dtkAbstractContainer<T>& values) = 0;
    virtual void replace(qlonglong from, qlonglong step, const dtkAbstractContainer<T>& values) = 0;
    virtual void replace(qlonglong *indices, const dtkAbstractContainer<T>& values) = 0;

    virtual void removeAt(qlonglong index) = 0;
    virtual void removeAt(qlonglong from, qlonglong to, qlonglong step = 1) = 0;

public:
    virtual qlonglong     indexOf(const T& value, qlonglong from = 0)  const = 0;
    virtual qlonglong lastIndexOf(const T& value, qlonglong from = -1) const = 0;

    virtual qlonglong *indicesOf(const T& value, qlonglong from = 0) const = 0;

    virtual const T& at(qlonglong index) const = 0;

    virtual const T& first(void) const = 0;
    virtual const T&  last(void) const = 0;

    virtual dtkAbstractContainerOrdered<T> *subContainer(const dtkAbstractContainerOrdered<qlonglong>& indices)  const = 0;
    virtual dtkAbstractContainerOrdered<T> *subContainer(qlonglong from, qlonglong to, qlonglong step = 1) const = 0;

public:
    virtual const T& operator [] (qlonglong index) const = 0;
    virtual       T& operator [] (qlonglong index)       = 0;
};

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainerOrdered implementation
// /////////////////////////////////////////////////////////////////

#include "dtkAbstractContainerOrdered.tpp"

#endif
