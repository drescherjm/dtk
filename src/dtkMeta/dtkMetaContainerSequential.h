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

#include "dtkMeta.h"
#include "dtkMetaContainerSequential_p.h"
#include "dtkMetaExport.h"

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential definition
// /////////////////////////////////////////////////////////////////

class DTKMETA_EXPORT dtkMetaContainerSequential
{
public:
    struct iterator;
    struct item
    {
    private:
        friend struct iterator;
        iterator *m_iterator;
        dtkMetaContainerSequentialPrivate::handler& m_h;
        QAtomicInt *m_ref;

    public:
        explicit item(iterator *iter);
                 item(const item& o) = delete;
                ~item(void);

    public:
        item& operator = (const item& o);

    public:
        const QVariant operator * (void) const;

    public:
        template <typename T> T value(void) const;

    public:
        template <typename T> item& operator  = (const T& value);
        template <typename T> item& operator += (const T& value);
        template <typename T> item& operator -= (const T& value);
        template <typename T> item& operator *= (const T& value);
        template <typename T> item& operator /= (const T& value);

    public:
        template <typename T> bool operator == (const T& value);
        template <typename T> bool operator != (const T& value);
    };
    friend struct item;

public:
    struct iterator
    {
    private:
        friend struct const_iterator;
        friend class dtkMetaContainerSequential;
        dtkMetaContainerSequentialPrivate::handler m_h;
        friend struct item;
        item *m_item;
        QAtomicInt *m_ref;

    private:
        explicit iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref);
        explicit iterator(const dtkMetaContainerSequentialPrivate::handler& h,  QAtomicInt *ref);

    public:
         iterator(const iterator& o);
        ~iterator(void);

    public:
        iterator& operator = (const iterator& o);

    public:
        item& operator *  (void)  const;
        item& operator [] (int j) const;

    public:
        bool operator == (const iterator& o) const;
        bool operator != (const iterator& o) const;

    public:
        iterator& operator ++ (void);
        iterator  operator ++ (int);
        iterator& operator -- (void);
        iterator  operator -- (int);
        iterator& operator += (int j);
        iterator& operator -= (int j);
        iterator  operator +  (int j) const;
        iterator  operator -  (int j) const;
    };
    friend struct iterator;

public:
    struct const_iterator
    {
    private:
        friend class dtkMetaContainerSequential;
        dtkMetaContainerSequentialPrivate::handler m_h;
        QAtomicInt *m_ref;

    private:
        explicit const_iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref);
        explicit const_iterator(const dtkMetaContainerSequentialPrivate::handler& handler, QAtomicInt *ref);

    public:
                 const_iterator(const const_iterator& o);
        explicit const_iterator(const       iterator& o);
                ~const_iterator(void);

    public:
        const_iterator& operator = (const const_iterator& o);

    public:
        const QVariant operator *  (void)  const;
        const QVariant operator [] (int j) const;

    public:
        bool operator == (const const_iterator& o) const;
        bool operator != (const const_iterator& o) const;

    public:
        const_iterator& operator ++ (void);
        const_iterator  operator ++ (int);
        const_iterator& operator -- (void);
        const_iterator  operator -- (int);
        const_iterator& operator += (int j);
        const_iterator& operator -= (int j);
        const_iterator  operator +  (int j) const;
        const_iterator  operator -  (int j) const;
    };
    friend struct const_iterator;

public:
    explicit dtkMetaContainerSequential(dtkMetaContainerSequentialPrivate::handler h);

public:
          iterator  begin(void)      ;
    const_iterator  begin(void) const;
    const_iterator cbegin(void) const;
          iterator    end(void)      ;
    const_iterator    end(void) const;
    const_iterator   cend(void) const;

public:
    bool hasBiDirectionalIterator(void) const;
    bool  hasRandomAccessIterator(void) const;

public:
    void clear(void);

    void reserve(int size);
    void  resize(int size);

public:
    bool empty(void) const;
    int   size(void) const;

public:
    template <typename T> void setAt(int idx, const        T& t);
                          void setAt(int idx, const QVariant& v);

    template <typename T> void append(const        T& t);
                          void append(const QVariant& v);

    template <typename T> void prepend(const        T& t);
                          void prepend(const QVariant& v);

    template <typename T> void insert(int idx, const        T& t);
                          void insert(int idx, const QVariant& v);

                          void removeAt(int idx);

public:
    const QVariant at(int idx) const;

    const QVariant  first(void) const;
              item& first(void);

    const QVariant  last(void) const;
              item& last(void);

    const QVariant  operator [] (int idx) const;
              item& operator [] (int idx);

protected:
    dtkMetaContainerSequentialPrivate::handler m_handler;
};

// /////////////////////////////////////////////////////////////////
// Specialization of Qt internal struct to build QVariant of dtkMetaContainerSequential
// /////////////////////////////////////////////////////////////////

namespace QtPrivate {
template<> struct QVariantValueHelperInterface<dtkMetaContainerSequential>
{
    static dtkMetaContainerSequential invoke(const QVariant &v);
};
}

// /////////////////////////////////////////////////////////////////

#include "dtkMetaContainerSequential.tpp"

//
// dtkMetaContainerSequential.h ends here
