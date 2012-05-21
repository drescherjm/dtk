/* dtkContainerVector.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 16:38:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Sun May 20 18:53:53 2012 (+0200)
 *           By: tkloczko
 *     Update #: 67
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTOR_H
#define DTKCONTAINERVECTOR_H

#include "dtkAbstractContainer.h"
#include "dtkCoreExport.h"
#include "dtkGlobal.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkContainerVector interface
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCORE_EXPORT dtkContainerVector : public dtkAbstractContainer
{
public:
     dtkContainerVector(dtkAbstractData *parent = 0);
     dtkContainerVector(const QVector<T>& vector, dtkAbstractData *parent = 0);
     dtkContainerVector(const dtkContainerVector<T>& other);
    ~dtkContainerVector(void);

public:
    dtkContainerVector<T>& operator = (const dtkContainerVector<T>& other);

public:
    dtkContainerVector<T> *clone(void) const;

public:
    virtual void setVector(const QVector<T>& vector);

public:
          QVector<T>& vector(void);
    const QVector<T>& vector(void) const;

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
    bool operator != (const dtkContainerVector<T>& other) const;
    bool operator == (const dtkContainerVector<T>& other) const;

public:
    bool isEqual(const dtkAbstractContainer& other) const;

public:
    QVariant operator[] (dtkxarch_int index) const;

protected:
    QVector<T> m_vector;
};

// /////////////////////////////////////////////////////////////////
// dtkContainerVector implementation
// /////////////////////////////////////////////////////////////////

#include "dtkContainerVector.tpp"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#include <QtCore>

typedef dtkContainerVector<qreal> dtkContainerVectorReal;

Q_DECLARE_METATYPE(dtkContainerVectorReal  );
Q_DECLARE_METATYPE(dtkContainerVectorReal *);

#endif
