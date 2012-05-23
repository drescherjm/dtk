/* dtkContainerVector.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 16:38:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 23 09:03:28 2012 (+0200)
 *           By: tkloczko
 *     Update #: 129
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
     /* dtkContainerVector(dtkxarch_int tuple_number, dtkxarch_int tuple_size, dtkAbstractData *parent = 0); */
     /* dtkContainerVector(const QVector<T>& vector, dtkxarch_int tuple_size = 1, dtkAbstractData *parent = 0); */
     /* dtkContainerVector(T *array, dtkxarch_int tuple_size = 1, dtkAbstractData *parent = 0); */
     dtkContainerVector(const QVector<T>& vector, dtkAbstractData *parent = 0);
     dtkContainerVector(const dtkContainerVector<T>& other);
    ~dtkContainerVector(void);

public:
    dtkContainerVector<T>& operator = (const dtkContainerVector<T>& other);

public:
    dtkContainerVector<T> *clone(void) const;

public:
    void setVector(const QVector<T>& vector);

public:
          QVector<T>& vector(void);
    const QVector<T>& vector(void) const;

    /*       T *array(void); */
    /* const T *array(void) const; */

    /* const T *constArray(void) const; */

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

/* public: */
/*     dtkContainerVector<T>& operator << (const T& value); */
/*     dtkContainerVector<T>& operator << (const dtkContainerVector<T>& other); */

public:
          T& operator[] (dtkxarch_int index);
    const T& operator[] (dtkxarch_int index) const;

/* public: */
/*     void     setNumberOfTuples(dtkxarch_int tuple_number); */
/*     void setNumberOfComponents(dtkxarch_int component_number); */

/* public: */
/*     void appendTuple(const   QVector<T>& tuple); */
/*     void appendTuple(const dtkVector<T>& tuple); */
/*     void appendTuple(dtkxarch_int tuple_source_index, const dtkContainerVector<T> source); */

/*     void prependTuple(const   QVector<T>& tuple); */
/*     void prependTuple(const dtkVector<T>& tuple); */
/*     void prependTuple(dtkxarch_int tuple_source_index, const dtkContainerVector<T> source); */

/*     void insertTuple(dtkxarch_int tuple_index, const   QVector<T>& tuple); */
/*     void insertTuple(dtkxarch_int tuple_index, const dtkVector<T>& tuple); */
/*     void insertTuple(dtkxarch_int tuple_index, dtkxarch_int tuple_source_index, const dtkContainerVector<T> source); */

/*     void replaceTuple(dtkxarch_int tuple_index, const   QVector<T>& tuple); */
/*     void replaceTuple(dtkxarch_int tuple_index, const dtkVector<T>& tuple); */
/*     void replaceTuple(dtkxarch_int tuple_index, dtkxarch_int tuple_source_index, const dtkContainerVector<T> source); */

/*     void removeTuple(dtkxarch_int tuple_index); */
    
/*     void removeFirstTuple(void); */
/*     void  removeLastTuple(void); */

/* public: */
/*     void setComponentName(dtkxarch_int component_index, const QString& name); */
    
/*     void setComponentNames(const QStringList& names); */

/* public: */
/*     void setComponentFromVector(dtkxarch_int component_index, const            QVector<T>& vector); */
/*     void setComponentFromVector(dtkxarch_int component_index, const dtkContainerVector<T>& vector); */

/*     void setComponentFromVector(const QString& component_name, const            QVector<T>& vector); */
/*     void setComponentFromVector(const QString& component_name, const dtkContainerVector<T>& vector); */

/*     void setComponentFromBuffer(dtkxarch_int component_index, T *buffer); */
/*     void setComponentFromBuffer(const QString& component_name, T *buffer); */

/* public: */
/*     void setComponentValue(dtkxarch_int block_index, dtkxarch_int component_index, const T& value); */

/*     void setComponentValues(const QVector<dtkxarch_int>& tuple_indices, const QVector<dtkxarch_int>& component_indices, const   QVector<T>& component_values); */
/*     void setComponentValues(const QVector<dtkxarch_int>& tuple_indices, const QVector<dtkxarch_int>& component_indices, const dtkVector<T>& component_values); */

/* public: */
/*     dtkxarch_int     numberOfTuples(void) const; */
/*     dtkxarch_int numberOfComponents(void) const; */
    
/* public: */
/*     void tuple(dtkxarch_int tuple_index, dtkContainerVector<T> *tuple) const; */
/*     dtkContainerVector<T> tuple(dtkxarch_int tuple_index) const; */
    

/* public: */
/*     QStringList componentNames(void) const; */

/*     QString componentName(dtkxarch_int component_index) const; */

public:
    

private:
    QVector<T> m_vector;

    dtkxarch_int m_tuple_size;
    dtkxarch_int m_tuple_number;

    QStringList m_component_names;
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
