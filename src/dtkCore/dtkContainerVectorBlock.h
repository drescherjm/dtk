/* dtkContainerVectorBlock.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Tue May 15 15:54:37 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 21 11:07:52 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 71
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCONTAINERVECTORBLOCK_H
#define DTKCONTAINERVECTORBLOCK_H

#include "dtkAbstractContainer.h"
#include "dtkContainerVector.h"
#include "dtkCoreExport.h"
#include "dtkGlobal.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorBlock interface
// /////////////////////////////////////////////////////////////////

template <typename T> class DTKCORE_EXPORT dtkContainerVectorBlock : public dtkContainerVector<T>
{
public:
     dtkContainerVectorBlock(dtkAbstractData *parent = 0);
     dtkContainerVectorBlock(dtkxarch_int block_number, dtkxarch_int block_size, dtkAbstractData *parent = 0);
     dtkContainerVectorBlock(const QVector<T>& vector, dtkxarch_int block_size, dtkAbstractData *parent = 0);
     dtkContainerVectorBlock(const dtkContainerVectorBlock<T>& other);
    ~dtkContainerVectorBlock(void);

public:
    dtkContainerVectorBlock<T>& operator = (const dtkContainerVectorBlock<T>& other);

public:
    dtkContainerVectorBlock<T> *clone(void) const;

public:
    Type type(void) const;

public:
    void setVector(const QVector<T>& vector, dtkxarch_int block_size);

private:
    void setVector(const QVector<T>& vector);

public:
    void clear(void);

public:
    bool operator != (const dtkContainerVectorBlock<T>& other) const;
    bool operator == (const dtkContainerVectorBlock<T>& other) const;

public:
    bool isEqual(const dtkAbstractContainer& other) const;

public:
    void setSize(dtkxarch_int block_number, dtkxarch_int block_size);

    void resize(dtkxarch_int block_number);

public:
    void append(const   QVector<T>& block);
    void append(const dtkVector<T>& block);

    void prepend(const   QVector<T>& block);
    void prepend(const dtkVector<T>& block);

    void remove(dtkxarch_int block_index);

    void removeFirst(void);
    void  removeLast(void);

    void insert(dtkxarch_int block_index, const   QVector<T>& block);
    void insert(dtkxarch_int block_index, const dtkVector<T>& block);

    void replace(dtkxarch_int block_index, const   QVector<T>& block);
    void replace(dtkxarch_int block_index, const dtkVector<T>& block);

public:
    dtkxarch_int numberOfBlocks(void) const;
    dtkxarch_int      blockSize(void) const;

    QVector<T> blockAt(dtkxarch_int block_index);

    dtkVector<T> vectorAt(dtkxarch_int block_index);

    T *pointerAt(dtkxarch_int block_index);

public:
    void setComponentName(dtkxarch_int component_index, const QString& name);

    QString componentName(dtkxarch_int component_index) const;

public:
    void setComponentVector(dtkxarch_int component_index, const QVector<T>& vector);

    QVector<T> componentVector(dtkxarch_int component_index) const;
    
public:
    void setComponentValue(dtkxarch_int block_index, dtkxarch_int component_index, const T& value);

          T& componentValue(dtkxarch_int block_index, dtkxarch_int component_index);
    const T& componentValue(dtkxarch_int block_index, dtkxarch_int component_index) const;

public:
    void setComponentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices, const   QVector<T>& component_values);
    void setComponentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices, const dtkVector<T>& component_values);

    QVector<T> componentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices) const;
    
    dtkVector<T> vectorOfComponentValues(const QVector<dtkxarch_int>& block_indices, const QVector<dtkxarch_int>& component_indices) const;

private:
    dtkxarch_int m_block_size;
    dtkxarch_int m_block_number;

    QStringList m_component_names;
};

// /////////////////////////////////////////////////////////////////
// dtkContainerVectorBlock implementation
// /////////////////////////////////////////////////////////////////

#include "dtkContainerVectorBlock.tpp"

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#include <QtCore>

typedef dtkContainerVectorBlock<qreal> dtkContainerVectorBlockReal;

Q_DECLARE_METATYPE(dtkContainerVectorBlockReal  );
Q_DECLARE_METATYPE(dtkContainerVectorBlockReal *);

#endif
