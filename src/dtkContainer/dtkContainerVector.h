/* dtkContainerVector.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May 23 11:19:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jun 25 14:42:07 2012 (+0200)
 *           By: tkloczko
 *     Update #: 71
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTOR_H
#define DTKCONTAINERVECTOR_H

#include "dtkAbstractContainerOrdered.h"
#include "dtkContainerExport.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkContainerVector interface
// /////////////////////////////////////////////////////////////////


template <typename T> class dtkContainerVector : public dtkAbstractContainerOrdered<T>
{
public:
             dtkContainerVector(void);
             dtkContainerVector(qlonglong size);
             dtkContainerVector(qlonglong size, const T& value);
             dtkContainerVector(const dtkContainerVector<T>& other);
    virtual ~dtkContainerVector(void);

public:
    QString identifier(void) const;

public:
    void clear(void);
    
    void append(const T& value);
    void append(const dtkAbstractContainer<T>& values);
    void append(const   dtkContainerVector<T>& values);
    
    void prepend(const T& value);
    void prepend(const dtkAbstractContainer<T>& values);
    void prepend(const   dtkContainerVector<T>& values);
    
    void remove(const T& value);
    void remove(const dtkAbstractContainer<T>& values);
    void remove(const   dtkContainerVector<T>& values);
    
    void insert(qlonglong index, const T& value);
    void insert(qlonglong from, const dtkAbstractContainer<T>& values);
    void insert(qlonglong from, qlonglong step, const dtkAbstractContainer<T>& values);
    void insert(qlonglong *indices, const dtkAbstractContainer<T>& values);
    void insert(qlonglong from, const dtkContainerVector<T>& values);
    void insert(qlonglong from, qlonglong step, const dtkContainerVector<T>& values);
    void insert(qlonglong *indices, const dtkContainerVector<T>& values);
    
    void replace(qlonglong index, const T& value);
    void replace(qlonglong from, const dtkAbstractContainer<T>& values);
    void replace(qlonglong from, qlonglong step, const dtkAbstractContainer<T>& values);
    void replace(qlonglong *indices, const dtkAbstractContainer<T>& values);
    void replace(qlonglong from, const dtkContainerVector<T>& values);
    void replace(qlonglong from, qlonglong step, const dtkContainerVector<T>& values);
    void replace(qlonglong *indices, const dtkContainerVector<T>& values);
    
    void removeAt(qlonglong index);
    void removeAt(qlonglong from, qlonglong to, qlonglong step = 1);

    void reserve(qlonglong value);
    void resize(qlonglong size);

    void  squeeze(void);

public:
    bool  isEmpty(void) const;

    bool contains(const T& value) const; 
    bool contains(const dtkAbstractContainer<T>& values) const;
    bool contains(const   dtkContainerVector<T>& values) const;

    qlonglong capacity(void) const;
    qlonglong    count(void) const;

    qlonglong     indexOf(const T& value, qlonglong from = 0)  const;
    qlonglong lastIndexOf(const T& value, qlonglong from = -1) const;

    qlonglong *indicesOf(const T& value, qlonglong from = 0) const;

    const T& at(qlonglong index) const;

    const T& first(void) const;
    const T&  last(void) const;

    dtkContainerVector<T> *subContainer(const dtkAbstractContainerOrdered<qlonglong>& indices)  const;
    dtkContainerVector<T> *subContainer(qlonglong from, qlonglong to, qlonglong step = 1) const;

          T *toArray(qlonglong& count);
    const T *toArray(qlonglong& count) const;

          T *array(void);
    const T *array(void) const;

    const T *constArray(void) const;

public:
    const T& operator [] (qlonglong index) const;
          T& operator [] (qlonglong index)      ;

public:
    dtkContainerVector& operator = (const dtkContainerVector<T>& other);

    dtkContainerVector<T> *clone(void) const;

public:
    dtkContainerVector& operator << (const T& value);
    dtkContainerVector& operator << (const dtkContainerVector<T>& values);

public:
    bool operator == (const dtkContainerVector<T>& other) const;
    bool operator != (const dtkContainerVector<T>& other) const;

    bool isEqual(const dtkAbstractContainer<T>& other) const;

public:
    dtkContainerVector<T>  operator +  (const dtkContainerVector<T>& other);

    dtkContainerVector<T>& operator += (const dtkContainerVector<T>& other);
    dtkContainerVector<T>& operator += (const T& value);

public:
    template <typename U> friend dtkContainerVector<U> dtkContainerVectorFromQVector(const QVector<U>& vector);
    template <typename U> friend QVector<U> dtkContainerVectorToQVector(const dtkContainerVector<U>& vector);

private:
    QVector<T> m_vector;
};

// // /////////////////////////////////////////////////////////////////
// // Helper functions
// // /////////////////////////////////////////////////////////////////

template <typename T> dtkContainerVector<T> dtkContainerVectorFromQVector(const QVector<T>& vector);
template <typename T> QVector<T> dtkContainerVectorToQVector(const dtkContainerVector<T>& vector);

// /////////////////////////////////////////////////////////////////
// dtkContainerVector implementation
// /////////////////////////////////////////////////////////////////

#include "dtkContainerVector.tpp"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

typedef dtkContainerVector<qreal> dtkContainerVectorReal;

Q_DECLARE_METATYPE(dtkContainerVectorReal  );
Q_DECLARE_METATYPE(dtkContainerVectorReal *);

typedef dtkContainerVector<qlonglong> dtkContainerVectorInteger;

Q_DECLARE_METATYPE(dtkContainerVectorInteger  );
Q_DECLARE_METATYPE(dtkContainerVectorInteger *);

#endif
