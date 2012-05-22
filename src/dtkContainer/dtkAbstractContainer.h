/* dtkAbstractContainer.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 22 13:07:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 22 16:16:23 2012 (+0200)
 *           By: tkloczko
 *     Update #: 60
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

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer interface
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCONTAINER_EXPORT dtkAbstractContainer
{
public:
    enum Type {
        None,
        Ordered,
        Unordered,
        Associated
    };

public:
     dtkAbstractContainer(void);
     dtkAbstractContainer(const dtkAbstractContainer<T>& other);
    ~dtkAbstractContainer(void);

public:
    virtual QString identifier(void) const = 0;

    virtual Type type(void) const = 0;

    void setName(const QString& name) = 0;
    
    QString name(void) const = 0;

public:
    virtual void clear(void) = 0;

    virtual void add(const T& value) = 0;
    virtual void add(const dtkAbstractContainer<T>& values) = 0;
    
    virtual void remove(const T& value) = 0;
    virtual void remove(const dtkAbstractContainer<T>& values) = 0;

public:
    virtual bool  isEmpty(void) const = 0;

    virtual bool contains(const T& value) = 0;
    virtual bool contains(const dtkAbstractContainer<T>& values) = 0;

    virtual dtkxarch_int count(void) const = 0;

    virtual T* toArray(dtkxarch_int& count) = 0;

public:
    dtkAbstractContainer& operator = (const dtkAbstractContainer<T>& other);

    virtual dtkContainerVector<T> *clone(void) const = 0;

public:
    dtkAbstractContainer& operator << (const T& value);
    dtkAbstractContainer& operator << (const dtkAbstractContainer<T>& values);

public:
    bool operator == (const dtkAbstractContainer<T>& other) const;
    bool operator != (const dtkAbstractContainer<T>& other) const;

    virtual bool isEqual(const dtkAbstractContainer& other) const = 0;

public:
    dtkAbstractContainer<T>  operator +  (const dtkAbstractContainer<T>& other);

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
