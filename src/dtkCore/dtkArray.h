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

public:
    enum RawDataType {
	ReadOnly = 0x001,
	Writable = 0x002
    };

public:
    typedef typename Data::iterator iterator;
    typedef typename Data::const_iterator const_iterator;
    typedef iterator Iterator;
    typedef const_iterator ConstIterator;

public:
             dtkArray(void);
    explicit dtkArray(qlonglong size);
             dtkArray(qlonglong size, const T& value);
             dtkArray(const T *values, qlonglong size);
             dtkArray(const dtkArray& other);

// #ifdef Q_COMPILER_RVALUE_REFS
//     dtkArray(dtkArray<T, PreallocSizeOther> &&other);
//     dtkArray<T, PreallocSizeOther> operator = (dtkArray<T, PreallocSizeOther> &&other);
// #endif

public:
    ~dtkArray(void);

public:
    void swap(dtkArray& other);
    bool isSharedWith(const dtkArray& other) const;

public:
    dtkArray<T, PreallocSize>& operator = (const dtkArray& other);

public:
    template <qlonglong PreallocSizeOther> dtkArray(const dtkArray<T, PreallocSizeOther>& other);

    template <qlonglong PreallocSizeOther> bool isSharedWith(const dtkArray<T, PreallocSizeOther>& other) const;

    template <qlonglong PreallocSizeOther> dtkArray<T, PreallocSize>& operator = (const dtkArray<T, PreallocSizeOther>& other);

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
    bool isDetached(void) const;
    void detach(void);

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
    void append(const dtkArray& other);

    void prepend(const T& value);

    void insert(qlonglong index, const T& value);
    void insert(qlonglong index, qlonglong length, const T& value);
    iterator insert(iterator before, const T& value);
    iterator insert(iterator before, qlonglong length, const T& value);

    void setAt(qlonglong index, const T& value);
    void setAt(qlonglong index, const T *values, qlonglong length);

    void replace(qlonglong index, const T& value);
    void replace(qlonglong index, const T *values, qlonglong length);

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
    dtkArray<T, PreallocSize>& operator += (const T& value);
    dtkArray<T, PreallocSize>& operator += (const dtkArray& other);
    dtkArray<T, PreallocSize>& operator << (const T& value);
    dtkArray<T, PreallocSize>& operator << (const dtkArray& other);

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

    void reallocData(const qlonglong size, const qlonglong alloc, dtkArrayData::AllocationOptions options = dtkArrayData::Default);
    void reallocData(const qlonglong size);
    void freeData(Data *d);

    void defaultConstruct(T *from, T *to);
    void copyConstruct(const T *srcFrom, const T *srcTo, T *dstFrom);
    void destruct(T *from, T *to);

    bool isValidIterator(const iterator &i) const;
};

// ///////////////////////////////////////////////////////////////////

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::reallocData(const qlonglong asize, const qlonglong aalloc, dtkArrayData::AllocationOptions options)
{
    Q_ASSERT(asize >= 0 && asize <= aalloc);
    Data *x = d;

    const bool isShared = d->ref.isShared();

    if (aalloc != 0) {
        if (aalloc != qlonglong(d->alloc) || isShared) {
            QT_TRY {
                if (aalloc > PreallocSize) {
                    // allocate memory
                    x = Data::allocate(aalloc, options);
                    x->size = asize;
                    x->capacityReserved = d->capacityReserved;

                } else {
                    x = Data::fromRawData(this->preallocData(), asize);
                    x->capacityReserved = true;
                    x->alloc = PreallocSize;
                }

                Q_CHECK_PTR(x);
                // aalloc is bigger then 0 so it is not [un]sharedEmpty
#if QT_SUPPORTS(UNSHARABLE_CONTAINERS)
                Q_ASSERT(x->ref.isSharable() || options.testFlag(dtkArrayData::Unsharable));
#endif
                Q_ASSERT(!x->ref.isStatic());

                T *srcBegin = d->begin();
                T *srcEnd = asize > d->size ? d->end() : d->begin() + asize;
                T *dst = x->begin();

                if (QTypeInfo<T>::isStatic || (isShared && QTypeInfo<T>::isComplex)) {
                    // we can not move the data, we need to copy construct it
                    while (srcBegin != srcEnd) {
                        new (dst++) T(*srcBegin++);
                    }
                } else {
                    ::memcpy(static_cast<void *>(dst), static_cast<void *>(srcBegin), (srcEnd - srcBegin) * sizeof(T));
                    dst += srcEnd - srcBegin;

                    // destruct unused / not moved data
                    if (asize < d->size)
                        destruct(d->begin() + asize, d->end());
                }

                if (asize > d->size) {
                    // construct all new objects when growing
                    QT_TRY {
                        defaultConstruct(dst, x->end());
                    } QT_CATCH (...) {
                        // destruct already copied objects
                        destruct(x->begin(), dst);
                        QT_RETHROW;
                    }
                }
            } QT_CATCH (...) {
                Data::deallocate(x);
                QT_RETHROW;
            }
        } else {
            Q_ASSERT(qlonglong(d->alloc) == aalloc); // resize, without changing allocation size
            Q_ASSERT(isDetached());       // can be done only on detached d
            Q_ASSERT(x == d);             // in this case we do not need to allocate anything
            if (asize <= d->size) {
                destruct(x->begin() + asize, x->end()); // from future end to current end
            } else {
                defaultConstruct(x->end(), x->begin() + asize); // from current end to future end
            }
            x->size = asize;
        }
    } else {
        x = Data::fromRawData(this->preallocData(), 0);
        x->capacityReserved = true;
        x->alloc = PreallocSize;
    }
    if (d != x) {
        if (!d->ref.deref()) {
            if (QTypeInfo<T>::isStatic || !aalloc || (isShared && QTypeInfo<T>::isComplex)) {
                // data was copy constructed, we need to call destructors
                // or if !alloc we did nothing to the old 'd'.
                freeData(d);
            } else {
                Data::deallocate(d);
            }
        }
        d = x;
    }

    Q_ASSERT(d->data());
    Q_ASSERT(quintptr(d->size) <= d->alloc);
#if QT_SUPPORTS(UNSHARABLE_CONTAINERS)
    Q_ASSERT(d != Data::unsharableEmpty());
#endif
    //Q_ASSERT(aalloc ? d != Data::sharedNull() : d == Data::sharedNull());
    Q_ASSERT(d->alloc >= quintptr(aalloc));
    Q_ASSERT(d->size == asize);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::reallocData(const qlonglong size)
{
    return this->reallocData(size, d->alloc);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::freeData(Data *x)
{
    destruct(x->begin(), x->end());
    Data::deallocate(x);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::defaultConstruct(T *from, T *to)
{
    if (QTypeInfo<T>::isComplex) {
        while (from != to) {
            new (from++) T();
        }
    } else {
        ::memset(static_cast<void *>(from), 0, (to - from) * sizeof(T));
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::copyConstruct(const T *srcFrom, const T *srcTo, T *dstFrom)
{
    if (QTypeInfo<T>::isComplex) {
        while (srcFrom != srcTo)
            new (dstFrom++) T(*srcFrom++);
    } else {
        ::memcpy(static_cast<void *>(dstFrom), static_cast<const void *>(srcFrom), (srcTo - srcFrom) * sizeof(T));
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::destruct(T *from, T *to)
{
    if (QTypeInfo<T>::isComplex) {
        while (from != to) {
            from++->~T();
        }
    }
}

template <typename T, qlonglong PreallocSize> inline bool dtkArray<T, PreallocSize>::isValidIterator(const iterator &i) const 
{ 
    return (i <= d->end()) && (d->begin() <= i);
}

// ///////////////////////////////////////////////////////////////////

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>::dtkArray(void)
{
    Q_STATIC_ASSERT_X(PreallocSize > 0, "dtkArray PreallocSize must be greater than 0.");
    d = Data::fromRawData(this->preallocData(), 0);
    d->capacityReserved = true;
    d->alloc = PreallocSize;
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>::dtkArray(qlonglong size)
{
    Q_STATIC_ASSERT_X(PreallocSize > 0, "dtkArray PreallocSize must be greater than 0.");
    Q_ASSERT_X(size >= 0, "dtkArray::dtkArray", "Size must be greater than or equal to 0.");
    if (size > PreallocSize) {
        d = Data::allocate(size);
        d->size = size;
    } else {
        d = Data::fromRawData(this->preallocData(), size);
        d->capacityReserved = true;
        d->alloc = PreallocSize;
    }
    defaultConstruct(d->begin(), d->end());
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>::dtkArray(qlonglong size, const T& value)
{
    Q_STATIC_ASSERT_X(PreallocSize > 0, "dtkArray PreallocSize must be greater than 0.");
    Q_ASSERT_X(size >= 0, "dtkArray::dtkArray", "Size must be greater than or equal to 0.");
    if (size > PreallocSize) {
        d = Data::allocate(size);
        d->size = size;
    } else {
        d = Data::fromRawData(this->preallocData(), size);
        d->capacityReserved = true;
        d->alloc = PreallocSize;
    }  
    T* i = d->end();
    while (i != d->begin())
        new (--i) T(value); 
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>::dtkArray(const T *values, qlonglong size)
{
    Q_STATIC_ASSERT_X(PreallocSize > 0, "dtkArray PreallocSize must be greater than 0.");
    Q_ASSERT_X(size >= 0, "dtkArray::dtkArray", "Size must be greater than or equal to 0.");
    if (size > PreallocSize) {
        d = Data::allocate(size);
        d->size = size;
    } else {
        d = Data::fromRawData(this->preallocData(), size);
        d->capacityReserved = true;
        d->alloc = PreallocSize;
    } 
    T *i = d->end();
    const T *value = values + size;
    while (i != d->begin())
        new (--i) T(*(--value));  
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>::dtkArray(const dtkArray& other)
{
    if (other.d->ref.ref()) {
        d = other.d;

    } else {
        if (other.d->capacityReserved) {
            if (other.d->alloc > PreallocSize) {
                d = Data::allocate(other.d->alloc);
                d->capacityReserved = true;
            } else {
                d = Data::fromRawData(this->preallocData(), other.d->size);
                d->capacityReserved = true;
                d->alloc = PreallocSize;
            }
        } else {
            d = Data::allocate(other.d->size);
        }
        if (d->alloc) {
            copyConstruct(other.d->begin(), other.d->end(), d->begin());
            d->size = other.d->size;
        }
    }
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>::~dtkArray(void)
{
    if (!d->ref.deref()) 
        freeData(d);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::swap(dtkArray& other)
{
    if (other.isPreallocated(other.d->data())) {
        qSwap(d, other.d);
        copyConstruct(other.preallocData(), other.preallocData() + d->size, d->begin());
    } else {
        qSwap(d, other.d);
    }    
}

template <typename T, qlonglong PreallocSize> inline bool dtkArray<T, PreallocSize>::isSharedWith(const dtkArray& other) const
{
    return d == other.d;
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator = (const dtkArray& other)
{
    if (other.d != d) {
        dtkArray<T, PreallocSize> tmp(other);
        tmp.swap(*this);
    }
    return *this;
}

template <typename T, qlonglong PreallocSize> template <qlonglong PreallocSizeOther> inline dtkArray<T, PreallocSize>::dtkArray(const dtkArray<T, PreallocSizeOther>& other)
{
    if (other.d->ref.ref()) {
        d = other.d;

    } else {
        if (other.d->capacityReserved) {
            if (other.d->alloc > PreallocSize) {
                d = Data::allocate(other.d->alloc);
                d->capacityReserved = true;
            } else {
                d = Data::fromRawData(this->preallocData(), other.d->size);
                d->capacityReserved = true;
                d->alloc = PreallocSize;
            }
        } else {
            d = Data::allocate(other.d->size);
        }
        if (d->alloc) {
            copyConstruct(other.d->begin(), other.d->end(), d->begin());
            d->size = other.d->size;
        }
    }
}

template <typename T, qlonglong PreallocSize> template <qlonglong PreallocSizeOther> inline bool dtkArray<T, PreallocSize>::isSharedWith(const dtkArray<T, PreallocSizeOther>& other) const
{
    return d == other.d;
}

template <typename T, qlonglong PreallocSize> template <qlonglong PreallocSizeOther> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator = (const dtkArray<T, PreallocSizeOther>& other)
{
    if (other.d != d) {
        dtkArray<T, PreallocSize> tmp(other);
        tmp.swap(*this);
    }
    return *this;
}

template <typename T, qlonglong PreallocSize> inline bool dtkArray<T, PreallocSize>::empty(void) const
{
    return (d->size == 0);
}

template <typename T, qlonglong PreallocSize> inline bool dtkArray<T, PreallocSize>::isEmpty(void) const
{
    return (d->size == 0);
}

template <typename T, qlonglong PreallocSize> inline bool dtkArray<T, PreallocSize>::usePreallocation(void) const
{
    return this->dtkArrayPrealloc<T, PreallocSize>::isPreallocated(d->data());
}

template <typename T, qlonglong PreallocSize> inline qlonglong dtkArray<T, PreallocSize>::size(void) const
{
    return d->size;
}

template <typename T, qlonglong PreallocSize> inline qlonglong dtkArray<T, PreallocSize>::count(void) const
{
    return d->size;
}

template <typename T, qlonglong PreallocSize> inline qlonglong dtkArray<T, PreallocSize>::length(void) const
{
    return d->size;
}

template <typename T, qlonglong PreallocSize> inline qlonglong dtkArray<T, PreallocSize>::capacity(void) const
{
    return qlonglong(d->alloc);
}

template <typename T, qlonglong PreallocSize> inline qlonglong dtkArray<T, PreallocSize>::preallocatedCapacity(void) const
{
    return PreallocSize;
}

template <typename T, qlonglong PreallocSize> inline bool dtkArray<T, PreallocSize>::isDetached(void) const
{
    return !d->ref.isShared();
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::detach(void)
{
    if (!isDetached()) {
#if QT_SUPPORTS(UNSHARABLE_CONTAINERS)
        if (!d->alloc)
            d = Data::unsharableEmpty();
        else
#endif
            reallocData(d->size, qlonglong(d->alloc));
    }
    Q_ASSERT(isDetached());
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::clear(void)
{
    *this = dtkArray<T, PreallocSize>();
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::resize(qlonglong asize)
{
    if (asize < 0)
        asize = 0;

    qlonglong newAlloc;
    const qlonglong oldAlloc = qlonglong(d->alloc);
    dtkArrayData::AllocationOptions opt;

    if (asize > oldAlloc) { // there is not enough space
        newAlloc = asize;
        opt = dtkArrayData::Grow;
    } else if (!d->capacityReserved && asize < d->size && asize < (oldAlloc >> 1)) { // we want to shrink
        newAlloc = asize;
        opt = dtkArrayData::Grow;
    } else {
        newAlloc = oldAlloc;
    }
    reallocData(asize, newAlloc, opt);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::reserve(qlonglong asize)
{
    if (asize > qlonglong(d->alloc))
        reallocData(d->size, asize);
    if (isDetached())
        d->capacityReserved = 1;
    Q_ASSERT(capacity() >= asize);

}
template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::squeeze(void)
{
    reallocData(d->size, d->size);
    if (d->capacityReserved && d->size > PreallocSize) {
        // capacity reserved in a read only memory would be useless
        // this checks avoid writing to such memory.
        d->capacityReserved = 0;
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::append(const T& value)
{
    const bool isTooSmall = quintptr(d->size + 1) > d->alloc;
    if (!isDetached() || isTooSmall) {
        dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
        reallocData(d->size, isTooSmall ? d->size + 1 : d->alloc, opt);
    }
    if (QTypeInfo<T>::isComplex) {
        new (d->end()) T(value);
    } else {
        *d->end() = T(value);
    }
    ++d->size;
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::append(const T& v1, const T& v2)
{
    quintptr newSize = d->size + 2;
    const bool isTooSmall = newSize > d->alloc;
    if (!isDetached() || isTooSmall) {
        dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
        reallocData(d->size, isTooSmall ? newSize : d->alloc, opt);
    }
    
    if (d->alloc) {        
        T *w = d->begin() + newSize - 1;
        if (QTypeInfo<T>::isComplex) {
            new (w) T(v2); --w;
            new (w) T(v1);
        } else {
            *w = T(v2); --w;
            *w = T(v1);
        }
        d->size = newSize;
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::append(const T& v1, const T& v2, const T& v3)
{
    quintptr newSize = d->size + 3;
    const bool isTooSmall = newSize > d->alloc;
    if (!isDetached() || isTooSmall) {
        dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
        reallocData(d->size, isTooSmall ? newSize : d->alloc, opt);
    }
    
    if (d->alloc) {        
        T *w = d->begin() + newSize - 1;
        if (QTypeInfo<T>::isComplex) {
            new (w) T(v3); --w;
            new (w) T(v2); --w;
            new (w) T(v1);
        } else {
            *w = T(v3); --w;
            *w = T(v2); --w;
            *w = T(v1);
        }
        d->size = newSize;
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::append(const T& v1, const T& v2, const T& v3, const T& v4)
{
    quintptr newSize = d->size + 4;
    const bool isTooSmall = newSize > d->alloc;
    if (!isDetached() || isTooSmall) {
        dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
        reallocData(d->size, isTooSmall ? newSize : d->alloc, opt);
    }
    
    if (d->alloc) {        
        T *w = d->begin() + newSize - 1;
        if (QTypeInfo<T>::isComplex) {
            new (w) T(v4); --w;
            new (w) T(v3); --w;
            new (w) T(v2); --w;
            new (w) T(v1);
        } else {
            *w = T(v4); --w;
            *w = T(v3); --w;
            *w = T(v2); --w;
            *w = T(v1);
        }
        d->size = newSize;
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::append(const T *values, qlonglong size)
{
    quintptr newSize = d->size + size;
    const bool isTooSmall = newSize > d->alloc;
    if (!isDetached() || isTooSmall) {
        dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
        reallocData(d->size, isTooSmall ? newSize : d->alloc, opt);
    }

    if (d->alloc) {
        T *w = d->begin() + newSize;
        const T *i = values + size;
        const T *b = values; 
        while (i != b) {
            if (QTypeInfo<T>::isComplex)
                new (--w) T(*--i);
            else
                *--w = *--i;
        }
        d->size = newSize;
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::append(const dtkArray& other)
{
    quintptr newSize = d->size + other.d->size;
    const bool isTooSmall = newSize > d->alloc;
    if (!isDetached() || isTooSmall) {
        dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
        reallocData(d->size, isTooSmall ? newSize : d->alloc, opt);
    }

    if (d->alloc) {
        T *w = d->begin() + newSize;
        T *i = other.d->end();
        T *b = other.d->begin();
        while (i != b) {
            if (QTypeInfo<T>::isComplex)
                new (--w) T(*--i);
            else
                *--w = *--i;
        }
        d->size = newSize;
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::prepend(const T& value)
{
    insert(begin(), 1, value);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::insert(qlonglong index, const T& value)
{
    Q_ASSERT_X(index >= 0 && index <= d->size, "dtkArray<T, PreallocSize>::insert", "index out of range");

    insert(begin() + index, 1, value);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::insert(qlonglong index, qlonglong length, const T& value)
{
    Q_ASSERT_X(index >= 0 && index <= d->size, "dtkArray<T, PreallocSize>::insert", "index out of range");

    insert(begin() + index, length, value);
}

template <typename T, qlonglong PreallocSize> inline typename dtkArray<T, PreallocSize>::iterator dtkArray<T, PreallocSize>::insert(iterator before, const T& value)
{
    return insert(before, 1, value);
}

template <typename T, qlonglong PreallocSize> inline typename dtkArray<T, PreallocSize>::iterator dtkArray<T, PreallocSize>::insert(iterator before, qlonglong n, const T& t)
{
    Q_ASSERT_X(isValidIterator(before), "dtkArray<T, PreallocSize>::insert", "The specified iterator argument 'before' is invalid");

    qlonglong offset = std::distance(d->begin(), before);
    if (n > 0) {
        const T copy(t);
        if (!isDetached() || d->size + n > qlonglong(d->alloc))
            reallocData(d->size, d->size + n, dtkArrayData::Grow);
        if (QTypeInfo<T>::isStatic) {
            T *b = d->end();
            T *i = d->end() + n;
            while (i != b)
                new (--i) T;
            i = d->end();
            T *j = i + n;
            b = d->begin() + offset;
            while (i != b)
                *--j = *--i;
            i = b+n;
            while (i != b)
                *--i = copy;
        } else {
            T *b = d->begin() + offset;
            T *i = b + n;
            ::memmove(i, b, (d->size - offset) * sizeof(T));
            while (i != b)
                new (--i) T(copy);
        }
        d->size += n;
    }
    return d->begin() + offset;
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::setAt(qlonglong index, const T& value)
{
    Q_ASSERT_X(index >= 0 && index < d->size, "dtkArray<T, PreallocSize>::setAt", "index out of range");
    data()[index] = value;
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::setAt(qlonglong index, const T *values, qlonglong length)
{
    Q_ASSERT_X(index >= 0 && length >= 0, "dtkArray<T, PreallocSize>::setAt", "index out of range or negative length");

    if (length != 0) {
        quintptr newSize = qMax(d->size, index + length);
        const bool isTooSmall = newSize > d->alloc;
        if (!isDetached() || isTooSmall) {
            dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
            reallocData(d->size, isTooSmall ? newSize : d->alloc, opt);
        }

        if (QTypeInfo<T>::isStatic) {
            if (index >= d->size) {
                T *b = d->end();
                T *i = d->begin() + index;
                while (i != b)
                    new (--i) T;
            }
            T *w = d->begin() + index + length;
            const T *b = values;
            const T *i = b + length;
            while (i != b)
                new (--w) T(*--i);

        } else {
            if (index >= d->size) {
                T *b = d->end();
                T *i = d->begin() + index;
                while (i != b) {
                    new (--i) T();
                }
            }
            T *src = const_cast<T *>(values);
            T *dst = d->begin() + index;
            ::memmove(dst, src, length * sizeof(T));
        }
        d->size = newSize;
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::replace(qlonglong index, const T& value)
{
    this->setAt(index, value);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::replace(qlonglong index, const T *values, qlonglong length)
{
    this->setAt(index, values, length);
}

template <typename T, qlonglong PreallocSize> inline typename dtkArray<T, PreallocSize>::iterator dtkArray<T, PreallocSize>::erase(iterator abegin, iterator aend)
{
    Q_ASSERT_X(isValidIterator(abegin), "dtkArray<T, PreallocSize>::erase", "The specified iterator argument 'begin' is invalid");
    Q_ASSERT_X(isValidIterator(aend), "dtkArray<T, PreallocSize>::erase", "The specified iterator argument 'end' is invalid");

    const int itemsToErase = aend - abegin;

    if (!itemsToErase)
        return abegin;

    Q_ASSERT(abegin >= d->begin());
    Q_ASSERT(aend <= d->end());
    Q_ASSERT(abegin <= aend);

    const int itemsUntouched = abegin - d->begin();

    // FIXME we could do a proper realloc, which copy constructs only needed data.
    // FIXME we ara about to delete data maybe it is good time to shrink?
    // FIXME the shrink is also an issue in removeLast, that is just a copy + reduce of this.
    if (d->alloc) {
        detach();
        abegin = d->begin() + itemsUntouched;
        aend = abegin + itemsToErase;
        if (QTypeInfo<T>::isStatic) {
            iterator moveBegin = abegin + itemsToErase;
            iterator moveEnd = d->end();
            while (moveBegin != moveEnd) {
                if (QTypeInfo<T>::isComplex)
                    static_cast<T *>(abegin)->~T();
                new (abegin++) T(*moveBegin++);
            }
            if (abegin < d->end()) {
                // destroy rest of instances
                destruct(abegin, d->end());
            }
        } else {
            destruct(abegin, aend);
            memmove(abegin, aend, (d->size - itemsToErase - itemsUntouched) * sizeof(T));
        }
        d->size -= itemsToErase;
    }
    return d->begin() + itemsUntouched;
}

template <typename T, qlonglong PreallocSize> inline typename dtkArray<T, PreallocSize>::iterator dtkArray<T, PreallocSize>::erase(iterator pos)
{
    return erase(pos, pos+1);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::remove(qlonglong index)
{
    Q_ASSERT_X(index >= 0 && index <= d->size, "dtkArray<T, PreallocSize>::remove", "index out of range");
    
    erase(d->begin() + index, d->begin() + index + 1);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::remove(qlonglong index, qlonglong length)
{
    Q_ASSERT_X(index >= 0 && length >= 0 && index + length <= d->size, "dtkArray<T, PreallocSize>::remove", "index out of range");

    erase(d->begin() + index, d->begin() + index + length);
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::removeFirst(void)
{
    Q_ASSERT(!isEmpty());

    erase(d->begin());
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::removeLast(void)
{
    Q_ASSERT(!isEmpty());
    Q_ASSERT(d->alloc);

    if (!d->ref.isShared()) {
        --d->size;
        if (QTypeInfo<T>::isComplex)
            (d->data() + d->size)->~T();
    } else {
        reallocData(d->size - 1);
    }
}

template <typename T, qlonglong PreallocSize> inline void dtkArray<T, PreallocSize>::removeAt(qlonglong index)
{
    Q_ASSERT_X(index >= 0 && index <= d->size, "dtkArray<T, PreallocSize>::removeAt", "index out of range");
    
    erase(d->begin() + index, d->begin() + index + 1);    
}

template <typename T, qlonglong PreallocSize> inline T dtkArray<T, PreallocSize>::takeFirst(void)
{
    Q_ASSERT(!isEmpty()); T r = first(); removeFirst(); return r;
}

template <typename T, qlonglong PreallocSize> inline T dtkArray<T, PreallocSize>::takeLast(void)
{
    Q_ASSERT(!isEmpty()); T r = last(); removeLast(); return r;
}

template <typename T, qlonglong PreallocSize> inline T dtkArray<T, PreallocSize>::takeAt(qlonglong index)
{
    T t = at(index); remove(index); return t;
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator += (const T& value)
{
    this->append(value);
    return *this;
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator += (const dtkArray& other)
{
    this->append(other);
    return *this;
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator << (const T& value)
{
    this->append(value);
    return *this;
}

template <typename T, qlonglong PreallocSize> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator << (const dtkArray& other)
{
    *this += other;
    return *this;
}

template <typename T, qlonglong PreallocSize> template <qlonglong PreallocSizeOther> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator += (const dtkArray<T, PreallocSizeOther>& other)
{
    quintptr newSize = d->size + other.d->size;
    const bool isTooSmall = newSize > d->alloc;
    if (!isDetached() || isTooSmall) {
        dtkArrayData::AllocationOptions opt(isTooSmall ? dtkArrayData::Grow : dtkArrayData::Default);
        reallocData(d->size, isTooSmall ? newSize : d->alloc, opt);
    }

    if (d->alloc) {
        T *w = d->begin() + newSize;
        T *i = other.d->end();
        T *b = other.d->begin();
        while (i != b) {
            if (QTypeInfo<T>::isComplex)
                new (--w) T(*--i);
            else
                *--w = *--i;
        }
        d->size = newSize;
    }
    return *this;
}

template <typename T, qlonglong PreallocSize> template <qlonglong PreallocSizeOther> inline dtkArray<T, PreallocSize>& dtkArray<T, PreallocSize>::operator << (const dtkArray<T, PreallocSizeOther>& other)
{
    *this += other; 
    return *this;
}

template <typename T, qlonglong PreallocSize> inline const T& dtkArray<T, PreallocSize>::at(qlonglong i) const
{
    Q_ASSERT_X(i >= 0 && i < d->size, "dtkArray<T, PreallocSize>::at", "index out of range");
    return d->begin()[i];
}

template <typename T, qlonglong PreallocSize> inline const T& dtkArray<T, PreallocSize>::operator[](qlonglong i) const
{
    Q_ASSERT_X(i >= 0 && i < d->size, "dtkArray<T, PreallocSize>::operator[]", "index out of range");
    return d->begin()[i];
}

template <typename T, qlonglong PreallocSize> inline T& dtkArray<T, PreallocSize>::operator[](qlonglong i)
{ 
    Q_ASSERT_X(i >= 0 && i < d->size, "dtkArray<T, PreallocSize>::operator[]", "index out of range");
    return data()[i];
}

template <typename T, qlonglong PreallocSize> inline T& dtkArray<T, PreallocSize>::first(void) 
{
    Q_ASSERT(!isEmpty()); return *begin(); 
}

template <typename T, qlonglong PreallocSize> inline const T& dtkArray<T, PreallocSize>::first(void) const
{
    Q_ASSERT(!isEmpty()); return *begin();
}

template <typename T, qlonglong PreallocSize> inline T& dtkArray<T, PreallocSize>::last(void)
{
    Q_ASSERT(!isEmpty()); return *(end()-1);
}

template <typename T, qlonglong PreallocSize> inline const T& dtkArray<T, PreallocSize>::last(void) const
{
    Q_ASSERT(!isEmpty()); return *(end()-1);
}

template <typename T, qlonglong PreallocSize> Q_OUTOFLINE_TEMPLATE T dtkArray<T, PreallocSize>::value(qlonglong index) const
{
    return quintptr(index) >= quintptr(d->size) ? T() : d->begin()[index];    
}

template <typename T, qlonglong PreallocSize> Q_OUTOFLINE_TEMPLATE T dtkArray<T, PreallocSize>::value(qlonglong index, const T& defaultValue) const
{
    return quintptr(index) >= quintptr(d->size) ? defaultValue : d->begin()[index];
}


// 
// dtkArray.h ends here
