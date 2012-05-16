/* dtkContainerList.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sun May  6 15:55:22 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May  7 16:24:10 2012 (+0200)
 *           By: tkloczko
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERLIST_H
#define DTKCONTAINERLIST_H

#include "dtkAbstractContainer.h"
#include "dtkCoreExport.h"
#include "dtkGlobal.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkContainerList interface
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCORE_EXPORT dtkContainerList : public dtkAbstractContainer
{
public:
     dtkContainerList(dtkAbstractData *parent = 0);
     dtkContainerList(const QList<T>& list, dtkAbstractData *parent = 0);
     dtkContainerList(const dtkContainerList<T>& other);
    ~dtkContainerList(void);

public:
    dtkContainerList<T>& operator = (const dtkContainerList<T>& other);

public:
    dtkContainerList<T> *clone(void) const;

public:
    inline void setList(const QList<T>& list);

public:
    inline QList<T>& list(void);

public:
    Type type(void) const;

public:
    void clear(void);

    void  append(const QVariant& data);
    void prepend(const QVariant& data);
    void  remove(const QVariant& data);

    void  insert(const QVariant& data, dtkxarch_int index);
    void replace(const QVariant& data, dtkxarch_int index);

    void resize(dtkxarch_int size);

public:
    bool  isEmpty(void) const;
    bool contains(const QVariant& data) const;

    dtkxarch_int   count(void) const;
    dtkxarch_int indexOf(const QVariant& data, dtkxarch_int from = 0) const;
     
    QVariant    at(dtkxarch_int index) const; 
    QVariant first(void) const;
    QVariant  last(void) const;

public:
    bool operator != (const dtkContainerList<T>& other) const;
    bool operator == (const dtkContainerList<T>& other) const;

public:
    bool isEqual(const dtkAbstractContainer& other) const;

public:
    QVariant operator[] (dtkxarch_int index) const;

private:
    QList<T> m_list;
};

// /////////////////////////////////////////////////////////////////
// dtkContainerList implementation
// /////////////////////////////////////////////////////////////////

#include "dtkContainerList.tpp"

#endif
