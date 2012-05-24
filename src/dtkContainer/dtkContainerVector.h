/* dtkContainerVector.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May 23 11:19:32 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu May 24 12:35:21 2012 (+0200)
 *           By: tkloczko
 *     Update #: 65
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

template <typename T> class DTKCONTAINER_EXPORT dtkContainerVector : public dtkAbstractContainerOrdered<T>
{
public:
     dtkContainerVector(void);
     dtkContainerVector(dtkxarch_int size);
     dtkContainerVector(dtkxarch_int size, const T& value);
     dtkContainerVector(const dtkContainerVector<T>& other);
    ~dtkContainerVector(void);

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
    
    void insert(dtkxarch_int index, const T& value);
    void insert(dtkxarch_int from, const dtkAbstractContainer<T>& values);
    void insert(dtkxarch_int from, dtkxarch_int step, const dtkAbstractContainer<T>& values);
    void insert(dtkxarch_int *indices, const dtkAbstractContainer<T>& values);
    void insert(dtkxarch_int from, const dtkContainerVector<T>& values);
    void insert(dtkxarch_int from, dtkxarch_int step, const dtkContainerVector<T>& values);
    void insert(dtkxarch_int *indices, const dtkContainerVector<T>& values);
    
    void replace(dtkxarch_int index, const T& value);
    void replace(dtkxarch_int from, const dtkAbstractContainer<T>& values);
    void replace(dtkxarch_int from, dtkxarch_int step, const dtkAbstractContainer<T>& values);
    void replace(dtkxarch_int *indices, const dtkAbstractContainer<T>& values);
    void replace(dtkxarch_int from, const dtkContainerVector<T>& values);
    void replace(dtkxarch_int from, dtkxarch_int step, const dtkContainerVector<T>& values);
    void replace(dtkxarch_int *indices, const dtkContainerVector<T>& values);
    
    void removeAt(dtkxarch_int index);
    void removeAt(dtkxarch_int from, dtkxarch_int to, dtkxarch_int step = 1);

    void reserve(dtkxarch_int value);
    void  resize(dtkxarch_int size);

    void  sqeeze(void);

public:
    bool  isEmpty(void) const;

    bool contains(const T& value);
    bool contains(const dtkAbstractContainer<T>& values);
    bool contains(const   dtkContainerVector<T>& values);

    dtkxarch_int capacity(void) const;
    dtkxarch_int    count(void) const;

    dtkxarch_int     indexOf(const T& value, dtkxarch_int from = 0)  const;
    dtkxarch_int lastIndexOf(const T& value, dtkxarch_int from = -1) const;

    dtkxarch_int *indicesOf(const T& value, dtkxarch_int from = 0) const;

    const T& at(dtkxarch_int index) const;

    dtkContainerVector<T> *subContainer(const dtkAbstractContainerOrdered<dtkxarch_int>& indices)  const;
    dtkContainerVector<T> *subContainer(dtkxarch_int from, dtkxarch_int to, dtkxarch_int step = 1) const;

          T *toArray(dtkxarch_int& count);
    const T *toArray(dtkxarch_int& count) const;

          T *array(void);
    const T *array(void) const;

    const T *constArray(void) const;

public:
    const T& operator [] (dtkxarch_int index) const;
          T& operator [] (dtkxarch_int index)      ;

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

// template <typename T> DTKCONTAINER_EXPORT dtkContainerVector<T> dtkContainerVectorFromQVector(const QVector<T>& vector);
// template <typename T> DTKCONTAINER_EXPORT QVector<T> dtkContainerVectorToQVector(const dtkContainerVector<T>& vector);

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

#endif
