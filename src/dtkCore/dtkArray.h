// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkArrayData.h"

#include <QtCore>
#include <iterator>
#include <vector>
#include <string.h>


// ///////////////////////////////////////////////////////////////////
// Preallocated data area for quickly building small arrays on the stack without malloc overhead
// ///////////////////////////////////////////////////////////////////

#if defined(Q_DECL_ALIGN) && defined(Q_ALIGNOF)

#if defined(Q_CC_GNU) && (__GNUC__ >= 4 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
    typedef char __attribute__((__may_alias__)) dtkArrayAlignedChar;
#else
    typedef char dtkArrayAlignedChar;
#endif

template <typename T, qlonglong PreallocSize, size_t AlignT> struct dtkArrayAlignedPrealloc;

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 1>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(1) data[sizeof(T) * PreallocSize];
};

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 2>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(2) data[sizeof(T) * PreallocSize];
};

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 4>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(4) data[sizeof(T) * PreallocSize];
};

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 8>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(8) data[sizeof(T) * PreallocSize];
};

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 16>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(16) data[sizeof(T) * PreallocSize];
};

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 32>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(32) data[sizeof(T) * PreallocSize];
};

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 64>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(64) data[sizeof(T) * PreallocSize];
};

template <typename T, qlonglong PreallocSize> struct dtkArrayAlignedPrealloc<T, PreallocSize, 128>
{
    dtkArrayAlignedChar Q_DECL_ALIGN(128) data[sizeof(T) * PreallocSize];
};

#else

template <typename T, qlonglong PreallocSize, size_t AlignT> union dtkArrayAlignedPrealloc
{
    char data[sizeof(T) * PreallocSize];
    qint64 q_for_alignment_1;
    double q_for_alignment_2;
};

#endif

// ///////////////////////////////////////////////////////////////////
// dtkArrayPrealloc base class
// ///////////////////////////////////////////////////////////////////

template <typename T, qlonglong PreallocSize> class dtkArrayPrealloc
{
public:
#if defined(Q_ALIGNOF)
    dtkArrayAlignedPrealloc<T, PreallocSize, Q_ALIGNOF(T)> m_prealloc;
#else
    dtkArrayAlignedPrealloc<T, PreallocSize, sizeof(T)> m_prealloc;
#endif

    T *preallocData(void) { return reinterpret_cast<T *>(m_prealloc.data); }

    bool isPreallocated(const T *start) const { return start == reinterpret_cast<const T *>(m_prealloc.data); }
};

template <typename T> class dtkArrayPrealloc<T, 0>
{
public:
    T *preallocData(void) { return 0; }

    bool isPreallocated(const T *) const { return false; }
};

// ///////////////////////////////////////////////////////////////////
// dtkArray interface
// ///////////////////////////////////////////////////////////////////

template <typename T, qlonglong PreallocSize = 8> class dtkArray : private dtkArrayPrealloc<T, PreallocSize>
{
    typedef dtkTypedArrayData<T> Data;
    Data *d;
    bool isRawData;

public:
    typedef typename Data::iterator iterator;
    typedef typename Data::const_iterator const_iterator;
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef qptrdiff difference_type;
    typedef qlonglong size_type;

public:
             dtkArray(void);
    explicit dtkArray(qlonglong size);
             dtkArray(qlonglong size, const T& value);
             dtkArray(const T *values, qlonglong size);
             dtkArray(std::initializer_list<T> args);
             dtkArray(const dtkArray& other);
#ifdef Q_COMPILER_RVALUE_REFS
             dtkArray(dtkArray&& other);
#endif

public:
    ~dtkArray(void);

public:
    dtkArray& operator = (const dtkArray& other);
#ifdef Q_COMPILER_RVALUE_REFS
    dtkArray& operator = (dtkArray&& other);
#endif

    bool operator == (const dtkArray& other) const;
    bool operator != (const dtkArray& other) const;

public:
    template <qlonglong PreallocSizeOther> dtkArray(const dtkArray<T, PreallocSizeOther>& other);

    template <qlonglong PreallocSizeOther> dtkArray<T, PreallocSize>& operator = (const dtkArray<T, PreallocSizeOther>& other);

    template <qlonglong PreallocSizeOther> bool operator == (const dtkArray<T, PreallocSizeOther>& other) const;
    template <qlonglong PreallocSizeOther> bool operator != (const dtkArray<T, PreallocSizeOther>& other) const;

    template <qlonglong PreallocSizeOther> bool isSharedWith(const dtkArray<T, PreallocSizeOther>& other) const;

public:
    void swap(dtkArray& other);

public:
    bool isDetached(void) const;
    void detach(void);
    bool isSharedWith(const dtkArray& other) const;
#if QT_SUPPORTS(UNSHARABLE_CONTAINERS)
    void setSharable(bool sharable);
#endif

public:
    bool empty(void) const;
    bool isEmpty(void) const;
    bool usePreallocation(void) const;

public:
    qlonglong size(void) const;
    qlonglong count(void) const;
    qlonglong length(void) const;
    qlonglong capacity(void) const;
    qlonglong preallocatedCapacity(void) const;

public:
    void   clear(void);
    void  resize(qlonglong size);
    void reserve(qlonglong size);
    void squeeze(void);

public:
    void append(const T& value);
    void append(const T& v1, const T& v2);
    void append(const T& v1, const T& v2, const T& v3);
    void append(const T& v1, const T& v2, const T& v3, const T& v4);
    void append(const T *values, qlonglong size);
    void append(std::initializer_list<T> args);
    void append(const dtkArray& other);

    void prepend(const T& value);

    void insert(qlonglong index, const T& value);
    void insert(qlonglong index, qlonglong length, const T& value);

    iterator insert(iterator before, const T& value);
    iterator insert(iterator before, qlonglong length, const T& value);

public:
    void setAt(qlonglong index, const T& value);
    void setAt(qlonglong index, const T *values, qlonglong length);

    void replace(qlonglong index, const T& value);
    void replace(qlonglong index, const T *values, qlonglong length);

    dtkArray& fill(const T &t, qlonglong size = -1);

    void setRawData(const T *raw_data, qlonglong size);
    void setWritableRawData(T *raw_data, qlonglong size);

public:
    static dtkArray fromRawData(const T *data, qlonglong size);
    static dtkArray fromWritableRawData(T *data, qlonglong size);

public:
    iterator erase(iterator begin, iterator end);
    iterator erase(iterator pos);

    void remove(qlonglong index);
    void remove(qlonglong index, qlonglong length);

    void removeFirst(void);
    void removeLast(void);
    void removeAt(qlonglong index);

    T takeFirst(void);
    T takeLast(void);
    T takeAt(qlonglong index);

public:
    void reverse(void);
    dtkArray reversed(void) const;

public:
    dtkArray& operator += (const T& value);
    dtkArray& operator += (const dtkArray& other);
    dtkArray& operator << (const T& value);
    dtkArray& operator << (const dtkArray& other);

public:
    template <qlonglong PreallocSizeOther> void append(const dtkArray<T, PreallocSizeOther>& other);
    template <qlonglong PreallocSizeOther> dtkArray<T, PreallocSize>& operator += (const dtkArray<T, PreallocSizeOther>& other);
    template <qlonglong PreallocSizeOther> dtkArray<T, PreallocSize>& operator << (const dtkArray<T, PreallocSizeOther>& other);

public:
    const T&         at(qlonglong index) const;
    const T& operator[](qlonglong index) const;
          T& operator[](qlonglong index);

          T& first(void);
    const T& first(void) const;
          T& last(void);
    const T& last(void) const;

    T value(qlonglong index) const;
    T value(qlonglong index, const T& defaultValue) const;

public:
    bool startsWith(const T &t) const;
    bool   endsWith(const T &t) const;
    bool   contains(const T &t) const;

    qlonglong indexOf(const T &t, qlonglong from = 0) const;
    qlonglong lastIndexOf(const T &t, qlonglong from = -1) const;
    qlonglong count(const T &t) const;

    dtkArray   mid(qlonglong pos, qlonglong length = -1) const;
    dtkArray  left(qlonglong length) const;
    dtkArray right(qlonglong length) const;

public:
    void  push_back(const T &t) {  append(t); }
    void push_front(const T &t) { prepend(t); }
    void  pop_back(void) {  removeLast(); }
    void pop_front(void) { removeFirst(); }
          reference front(void)       { return first(); }
    const_reference front(void) const { return first(); }
          reference  back(void)       { return  last(); }
    const_reference  back(void) const { return  last(); }

public:
          T      *data(void)       { detach(); return d->begin(); }
    const T      *data(void) const {           return d->begin(); }
    const T *constData(void) const {           return d->begin(); }

public:
          iterator begin(iterator = iterator())                        { detach(); return d->begin(); }
    const_iterator begin(const_iterator = const_iterator()) const      { return d->constBegin(); }
    const_iterator cbegin(const_iterator = const_iterator()) const     { return d->constBegin(); }
    const_iterator constBegin(const_iterator = const_iterator()) const { return d->constBegin(); }

          iterator end(iterator = iterator())                        { detach(); return d->end(); }
    const_iterator end(const_iterator = const_iterator()) const      { return d->constEnd(); }
    const_iterator cend(const_iterator = const_iterator()) const     { return d->constEnd(); }

    const_iterator constEnd(const_iterator = const_iterator()) const { return d->constEnd(); }

private:
    template <typename, qlonglong> friend class dtkArray;

    void copyData(Data *other_d);

    void reallocData(const qlonglong size, const qlonglong alloc, dtkArrayData::AllocationOptions options = dtkArrayData::Default);
    void reallocData(const qlonglong size);
    void freeData(Data *d);

    void defaultConstruct(T *from, T *to);
    void copyConstruct(const T *srcFrom, const T *srcTo, T *dstFrom);
    void destruct(T *from, T *to);

    bool isValidIterator(const iterator &i) const;
};

// ///////////////////////////////////////////////////////////////////
// Helpers
// ///////////////////////////////////////////////////////////////////

template <typename T, qlonglong PreallocSize> QDebug& operator << (QDebug debug, const dtkArray<T, PreallocSize>& array);

template<typename T, qlonglong PreallocSize> QDataStream& operator << (QDataStream& s, const dtkArray<T, PreallocSize>& array);
template<typename T, qlonglong PreallocSize> QDataStream& operator >> (QDataStream& s,       dtkArray<T, PreallocSize>& array);

template<typename T, qlonglong PreallocSize> QDataStream& operator << (QDataStream& s, const dtkArray<T *, PreallocSize>& array);
template<typename T, qlonglong PreallocSize> QDataStream& operator >> (QDataStream& s,       dtkArray<T *, PreallocSize>& array);

// ///////////////////////////////////////////////////////////////////
// Alias when c++1 is available
// ///////////////////////////////////////////////////////////////////

#ifdef Q_COMPILER_TEMPLATE_ALIAS
template<typename T> using dtkArrayDynamic = dtkArray<T, 0>;
#endif

// ///////////////////////////////////////////////////////////////////
// Implementation
// ///////////////////////////////////////////////////////////////////

#include "dtkArray.tpp"

//
// dtkArray.h ends here
