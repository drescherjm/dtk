/* dtkContainerVectorWrapper.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri May 25 09:29:47 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Oct 10 12:11:45 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 25
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTORWRAPPER_H
#define DTKCONTAINERVECTORWRAPPER_H

#include "dtkAbstractContainerWrapper.h"
#include "dtkContainerExport.h"
#include "dtkContainerVector.h"

#include <dtkCore/dtkGlobal>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorWrapper interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkContainerVectorWrapper : public dtkAbstractContainerWrapper
{
public:
     dtkContainerVectorWrapper(void);
     dtkContainerVectorWrapper(dtkContainerVector<T> *vector);
     dtkContainerVectorWrapper(const dtkContainerVectorWrapper<T>& other);
    ~dtkContainerVectorWrapper(void);

public:
    dtkContainerVectorWrapper<T>& operator = (const dtkContainerVectorWrapper<T>& other);

public:
    dtkContainerVectorWrapper<T> *clone(void);

    dtkContainerVectorWrapper<T> *voidClone(void);

public:
    QString  identifier(void) const;
    QString description(void) const;

public:
    void setVector(dtkContainerVector<T> *vector);

public:
    dtkContainerVector<T> *vector(void);

public:
    Type type(void) const;

public:
    void clear(void);

    void  append(const QVariant& data);
    void prepend(const QVariant& data);
    void  remove(const QVariant& data);

    void  insert(const QVariant& data, qlonglong index);
    void replace(const QVariant& data, qlonglong index);

    void resize(qlonglong size);

public:
    bool  isEmpty(void) const;
    bool contains(const QVariant& data) const;

    qlonglong   count(void) const;
    qlonglong indexOf(const QVariant& data, qlonglong from = 0) const;
     
    QVariant    at(qlonglong index) const; 

public:
    bool operator != (const dtkContainerVectorWrapper<T>& other) const;
    bool operator == (const dtkContainerVectorWrapper<T>& other) const;

public:
    bool isEqual(const dtkAbstractObject& other) const;    

private:
    dtkContainerVector<T> *m_vector;
};

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorWrapper implementation
// /////////////////////////////////////////////////////////////////

#include "dtkContainerVectorWrapper.tpp"

#endif
