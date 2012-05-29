/* dtkAbstractContainer.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 13:07:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri May 25 10:00:38 2012 (+0200)
 *           By: tkloczko
 *     Update #: 77
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTCONTAINER_H
#define DTKABSTRACTCONTAINER_H

#include "dtkContainerExport.h"

#include <dtkCore/dtkGlobal>

#include <typeinfo>

enum dtkContainerType {
        dtkContainerTypeNone,
        dtkContainerTypeOrdered,
        dtkContainerTypeUnordered,
        dtkContainerTypeAssociated
    };

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer interface
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCONTAINER_EXPORT dtkAbstractContainer
{
public:
     dtkAbstractContainer(void);
     dtkAbstractContainer(const dtkAbstractContainer<T>& other);
    ~dtkAbstractContainer(void);

public:
    virtual QString identifier(void) const = 0;

    virtual dtkContainerType type(void) const = 0;

public:
    virtual void clear(void) = 0;

    virtual void add(const T& value) = 0;
    virtual void add(const dtkAbstractContainer<T>& values) = 0;
    
    virtual void remove(const T& value) = 0;
    virtual void remove(const dtkAbstractContainer<T>& values) = 0;

public:
    virtual bool  isEmpty(void) const = 0;

    virtual bool contains(const T& value) const = 0;
    virtual bool contains(const dtkAbstractContainer<T>& values) const = 0;

    virtual dtkxarch_int count(void) const = 0;

    virtual       T *toArray(dtkxarch_int& count) = 0;
    virtual const T *toArray(dtkxarch_int& count) const = 0;

public:
    dtkAbstractContainer& operator = (const dtkAbstractContainer<T>& other);

    virtual dtkAbstractContainer<T> *clone(void) const = 0;

public:
    dtkAbstractContainer& operator << (const T& value);
    dtkAbstractContainer& operator << (const dtkAbstractContainer<T>& values);

public:
    bool operator == (const dtkAbstractContainer<T>& other) const;
    bool operator != (const dtkAbstractContainer<T>& other) const;

    virtual bool isEqual(const dtkAbstractContainer& other) const = 0;

public:
    dtkAbstractContainer<T>  operator +  (const dtkAbstractContainer<T>& other) const;

    dtkAbstractContainer<T>& operator += (const dtkAbstractContainer<T>& other);
    dtkAbstractContainer<T>& operator += (const T& value);
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

template <typename T> DTKCONTAINER_EXPORT QDebug operator << (QDebug& dbg, const dtkAbstractContainer<T>& container);
template <typename T> DTKCONTAINER_EXPORT QDebug operator << (QDebug& dbg,       dtkAbstractContainer<T> *container);

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer implementation
// /////////////////////////////////////////////////////////////////

#include "dtkAbstractContainer.tpp"

#endif
