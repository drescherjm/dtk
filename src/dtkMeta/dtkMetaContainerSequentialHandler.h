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

#include "dtkMetaTypeTraits.h"
#include "dtkMetaExport.h"

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialHandler
// ///////////////////////////////////////////////////////////////////

class DTKMETA_EXPORT dtkMetaContainerSequentialHandler
{
public:  
    virtual ~dtkMetaContainerSequentialHandler(void) {}

public:
    virtual bool hasBiDirectionalIterator(void) const = 0;
    virtual bool  hasRandomAccessIterator(void) const = 0;

public:
    struct DTKMETA_EXPORT item
    {
    public:
        virtual ~item(void) {}
        virtual item *clone(void) const = 0;
        virtual void copy(const item& o) = 0;
        virtual bool equal(const item& o) const = 0;
        virtual const void *value(void) const = 0;
        virtual QVariant variant(void) const = 0;

    public:
        virtual void    assign(const void *t) = 0;
        virtual void addAssign(const void *t) = 0;
        virtual void subAssign(const void *t) = 0;
        virtual void mulAssign(const void *t) = 0;
        virtual void divAssign(const void *t) = 0;

    public:
        virtual bool equal(const void *t) = 0;
    };

public:
    struct DTKMETA_EXPORT iterator
    {
    public:
        virtual ~iterator(void) {}
        virtual iterator *clone(void) const = 0;
        virtual void copy(const iterator& o) = 0;
        virtual bool equal(const iterator& o) const = 0;
        virtual QVariant value(void) const = 0;
        virtual item *proxyItem(void) const = 0;
        virtual void advance(void) = 0;
        virtual void  moveForward(qlonglong step) = 0;
        virtual void moveBackward(qlonglong step) = 0;
    };

public:
    struct DTKMETA_EXPORT const_iterator
    {
    public:
        virtual ~const_iterator(void) {}
        virtual const_iterator *clone(void) const = 0;
        virtual void copy(const const_iterator& o) = 0;
        virtual bool equal(const const_iterator& o) const = 0;
        virtual QVariant value(void) const = 0;
        virtual void advance(void) = 0;
        virtual void  moveForward(qlonglong step) = 0;
        virtual void moveBackward(qlonglong step) = 0;
    };

public:
    virtual       iterator  *begin(void)       = 0;
    virtual const_iterator *cbegin(void) const = 0;
    virtual       iterator    *end(void)       = 0;
    virtual const_iterator   *cend(void) const = 0;

public:
    virtual bool      empty(void) const = 0;
    virtual qlonglong  size(void) const = 0;

public:
    virtual void   clear(void) = 0;
    virtual void reserve(qlonglong size) = 0;
    virtual void  resize(qlonglong size) = 0;

public:
    virtual void  append(const void *t) = 0;
    virtual void prepend(const void *t) = 0;
    virtual void  insert(qlonglong idx, const void *t) = 0;

public:
    virtual void    setAt(qlonglong idx, const void *t) = 0;
    virtual void removeAt(qlonglong idx) = 0;

public:
    virtual const void *at(qlonglong idx) const = 0;
    virtual       void *at(qlonglong idx)       = 0;

public:
    virtual item *itemAt(qlonglong idx) = 0;
    virtual QVariant variantAt(qlonglong idx) = 0;
};

// ///////////////////////////////////////////////////////////////////

class DTKMETA_EXPORT dtkMetaContainer
{
public:
    struct iterator;
    struct DTKMETA_EXPORT item
    {
    private:
        friend struct iterator;
        dtkMetaContainerSequentialHandler::item *it;        

    public:
        explicit item(dtkMetaContainerSequentialHandler::item *item) : it(item) {}

    public:
         item(const item& o) : it(o.it->clone()) {}
         item(item&& o) : it(o.it) { o.it = NULL; }
        ~item(void) { if (it) delete it; it = NULL; }

    public:
        item& operator = (const item& o) { it->copy(*(o.it)); return *this; }
        item& operator = (item&& o) { std::swap(it, o.it); return *this; }

    public:
        bool operator == (const item& o) { return  it->equal(*(o.it)); }
        bool operator != (const item& o) { return !it->equal(*(o.it)); }

    public:
        template <typename T> const        T& value(void) const { return *static_cast<const T *>(it->value()); }
                              const QVariant  value(void) const { return it->variant(); }

    public:
        template <typename T> item& operator  = (const T& t) { it->assign(&t);    return *this; }
        template <typename T> item& operator += (const T& t) { it->addAssign(&t); return *this; }
        template <typename T> item& operator -= (const T& t) { it->subAssign(&t); return *this; }
        template <typename T> item& operator *= (const T& t) { it->mulAssign(&t); return *this; }
        template <typename T> item& operator /= (const T& t) { it->divAssign(&t); return *this; }

    public:
        template <typename T> bool operator == (const T& t) { return  it->equal(&t); }
        template <typename T> bool operator != (const T& t) { return !it->equal(&t); }

    private:
        void setItem(dtkMetaContainerSequentialHandler::item *item) { it = item; }
    };

public:
    struct DTKMETA_EXPORT iterator
    {
    private:
        friend class dtkMetaContainer;
        dtkMetaContainerSequentialHandler::iterator *it;
        mutable item proxy;

    private:
        explicit iterator(dtkMetaContainerSequentialHandler::iterator *iterator) : it(iterator), proxy(iterator->proxyItem()) {}

    public:
         iterator(const iterator& o) : it(o.it->clone()), proxy(o.it->proxyItem()) {}
         iterator(iterator&& o) : it(o.it), proxy(std::move(o.it->proxyItem())) { o.it = NULL; }
        ~iterator(void) { delete it; }

    public:
        iterator& operator = (const iterator& o) { it->copy(*(o.it)); return *this; }
        iterator& operator = (iterator&& o) { std::swap(it, o.it); return *this; }

    public:
        item& operator *  (void)  const { proxy.setItem(it->proxyItem()); return proxy; }
        item& operator [] (qlonglong j) const { return *(*this + j); }

    public:
        bool operator == (const iterator& o) const { return  it->equal(*(o.it)); }
        bool operator != (const iterator& o) const { return !it->equal(*(o.it)); }

    public:
        iterator& operator ++ (void) { it->advance(); return *this; }
        iterator  operator ++ (int)  { iterator o(*this); it->advance(); return o; }
        iterator& operator -- (void) { it->moveBackward(static_cast<qlonglong>(1)); return *this; }
        iterator  operator -- (int)  { iterator o(*this); it->moveBackward(static_cast<qlonglong>(1)); return *this; }
        iterator& operator += (qlonglong j) { it->moveForward(j);  return *this; }
        iterator& operator -= (qlonglong j) { it->moveBackward(j); return *this; }
        iterator  operator +  (qlonglong j) const { iterator o(*this); o += j; return o; }
        iterator  operator -  (qlonglong j) const { iterator o(*this); o -= j; return o; }
    };

public:
    struct DTKMETA_EXPORT const_iterator
    {
    private:
        friend class dtkMetaContainer;
        dtkMetaContainerSequentialHandler::const_iterator *it;

    private:
        explicit const_iterator(dtkMetaContainerSequentialHandler::const_iterator *iterator) : it(iterator) {}

    public:
         const_iterator(const const_iterator& o) : it(o.it->clone()) {}
        ~const_iterator(void) { delete it; }

    public:
        const_iterator& operator = (const const_iterator& o) { it->copy(*(o.it)); return *this; }

    public:
        const QVariant operator *  (void)        const { return it->value(); }
        const QVariant operator [] (qlonglong j) const { return *(*this + j); }

    public:
        bool operator == (const const_iterator& o) const { return  it->equal(*(o.it)); }
        bool operator != (const const_iterator& o) const { return !it->equal(*(o.it)); }

    public:
        const_iterator& operator ++ (void) { it->advance(); return *this; }
        const_iterator  operator ++ (int)  { const_iterator o(*this); it->advance(); return o; }
        const_iterator& operator -- (void) { it->moveBackward(static_cast<qlonglong>(1)); return *this; }
        const_iterator  operator -- (int)  { const_iterator o(*this); it->moveBackward(static_cast<qlonglong>(1)); return *this; }
        const_iterator& operator += (qlonglong j) { it->moveForward(j);  return *this; }
        const_iterator& operator -= (qlonglong j) { it->moveBackward(j); return *this; }
        const_iterator  operator +  (qlonglong j) const { const_iterator o(*this); o += j; return o; }
        const_iterator  operator -  (qlonglong j) const { const_iterator o(*this); o -= j; return o; }
    };
public:
     dtkMetaContainer(dtkMetaContainerSequentialHandler *handler) : h(handler) {}
    ~dtkMetaContainer(void) { if (h) delete h; }

public:
          iterator  begin(void)       { return       iterator(h->begin());  }
    const_iterator  begin(void) const { return const_iterator(h->cbegin()); }
    const_iterator cbegin(void) const { return const_iterator(h->cbegin()); }
          iterator    end(void)       { return       iterator(h->end());    }
    const_iterator    end(void) const { return const_iterator(h->cend());   }
    const_iterator   cend(void) const { return const_iterator(h->cend());   }

public:
    bool hasBiDirectionalIterator(void) const { return h->hasBiDirectionalIterator(); }
    bool  hasRandomAccessIterator(void) const { return h->hasRandomAccessIterator(); }

public:
    bool      empty(void) const { return h->empty(); }
    qlonglong  size(void) const { return h->size(); }

public:
    void   clear(void) { h->clear(); }
    void reserve(qlonglong size) { h->reserve(size); }
    void  resize(qlonglong size) { h->resize(size); }

public:
    template <typename T> void  append(const T& t) { h->append(&t); }
    template <typename T> void prepend(const T& t) { h->prepend(&t); }
    template <typename T> void  insert(qlonglong idx, const T& t) { h->insert(idx, &t); }

public:
    template <typename T> void    setAt(qlonglong idx, const T& t) { h->setAt(idx, &t); }
                          void removeAt(qlonglong idx) { h->removeAt(idx); }

public:
    template <typename T> const        T& at(qlonglong idx) const { return *static_cast<const T *>(h->at(idx)); }
                          const QVariant  at(qlonglong idx) const { return (this->cbegin())[idx]; }

public:
    item first(void) { return item(h->itemAt(0)); } 
    item  last(void) { return item(h->itemAt(h->size()-1)); }
    item operator [] (qlonglong idx) { return item(h->itemAt(idx)); }

public:
    QVariant first(void) const { return h->variantAt(0); }
    QVariant  last(void) const { return h->variantAt(h->size()-1); }
    QVariant operator [] (qlonglong idx) const { return h->variantAt(idx); }

public:
    dtkMetaContainerSequentialHandler *h;
};

Q_DECLARE_METATYPE(dtkMetaContainerSequentialHandler *)

// ///////////////////////////////////////////////////////////////////

inline QDebug& operator << (QDebug debug, const dtkMetaContainer::item& item)
{
    const bool oldSetting = debug.autoInsertSpaces();
    debug.nospace() << item.value();
    debug.setAutoInsertSpaces(oldSetting);
    return debug.maybeSpace();    
}

namespace QtPrivate {
template<> struct QVariantValueHelperInterface<dtkMetaContainer>
{
    static dtkMetaContainer invoke(const QVariant &v)
    {
        return dtkMetaContainer(v.value<dtkMetaContainerSequentialHandler *>());
    }
};
}

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialHandlerTemplate
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkMetaContainerSequentialHandlerTemplate : public dtkMetaContainerSequentialHandler
{
    T *m_container;

public:
    explicit dtkMetaContainerSequentialHandlerTemplate(T *c);
            ~dtkMetaContainerSequentialHandlerTemplate(void);

public:
    bool hasBiDirectionalIterator(void) const;
    bool  hasRandomAccessIterator(void) const;

public:
    struct DTKMETA_EXPORT item : public dtkMetaContainerSequentialHandler::item
    {
        typedef typename T::value_type ValueType;
    private:
        ValueType *ref;

    public:
         item(ValueType *reference) : ref(reference) {}
         item *clone(void) const { return new item(ref); }
         void copy(const dtkMetaContainerSequentialHandler::item& o) { *ref = *static_cast<const item&>(o).ref; }
         bool equal(const dtkMetaContainerSequentialHandler::item& o) const { return (*ref == *static_cast<const item&>(o).ref); }
         const void *value(void) const { return ref; }
         QVariant variant(void) const { return dtkMetaType::variantFromValue(*ref); }

    public:
         void    assign(const void *t);
         void addAssign(const void *t);
         void subAssign(const void *t);
         void mulAssign(const void *t);
         void divAssign(const void *t);

    public:
        bool equal(const void *t);
    };

public:
    struct DTKMETA_EXPORT iterator : public dtkMetaContainerSequentialHandler::iterator
    {
    private:
        typename T::iterator it;

    public:
         iterator(const typename T::iterator& iterator) : it(iterator) {}
         iterator *clone(void) const { return new iterator(it); }
         void copy(const dtkMetaContainerSequentialHandler::iterator& o) { it = static_cast<const iterator&>(o).it; }
         bool equal(const dtkMetaContainerSequentialHandler::iterator& o) const { return it == static_cast<const iterator&>(o).it; }
         QVariant value(void) const { return dtkMetaType::variantFromValue(*it); }
         dtkMetaContainerSequentialHandler::item *proxyItem(void) const { return new item(&(*it)); }
         void advance(void) { ++it; }
         void  moveForward(qlonglong step) { std::advance(it, step); }
         void moveBackward(qlonglong step) { std::advance(it, -step); }
    };

public:
    struct DTKMETA_EXPORT const_iterator : public dtkMetaContainerSequentialHandler::const_iterator
    {
    private:
        typename T::const_iterator it;

    public:
         const_iterator(const typename T::const_iterator& iterator) : it(iterator) {}
         const_iterator *clone(void) const { return new const_iterator(it); }
         void copy(const dtkMetaContainerSequentialHandler::const_iterator& o) { it = static_cast<const const_iterator&>(o).it; }
         bool equal(const dtkMetaContainerSequentialHandler::const_iterator& o) const { return it == static_cast<const const_iterator&>(o).it; }
         QVariant value(void) const { return dtkMetaType::variantFromValue(*it); }
         void advance(void) { ++it; }
         void  moveForward(qlonglong step) { std::advance(it, step); }
         void moveBackward(qlonglong step) { std::advance(it, -step); }
    };

public:
    dtkMetaContainerSequentialHandler::iterator        *begin(void)       { return new       iterator(m_container->begin());  }
    dtkMetaContainerSequentialHandler::const_iterator *cbegin(void) const { return new const_iterator(m_container->cbegin()); }
    dtkMetaContainerSequentialHandler::iterator          *end(void)       { return new       iterator(m_container->end());    }
    dtkMetaContainerSequentialHandler::const_iterator   *cend(void) const { return new const_iterator(m_container->cend());   }

public:
    bool      empty(void) const;
    qlonglong  size(void) const;

public:
    void   clear(void);
    void reserve(qlonglong size);
    void  resize(qlonglong size);

public:
    void  append(const void *t);
    void prepend(const void *t);
    void  insert(qlonglong idx, const void *t);

public:
    void    setAt(qlonglong idx, const void *t);
    void removeAt(qlonglong idx);

public:
    const void *at(qlonglong idx) const;
          void *at(qlonglong idx);

public:
        item   *itemAt(qlonglong idx);
    QVariant variantAt(qlonglong idx);
};

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialHandlerHelper
// ///////////////////////////////////////////////////////////////////

template <typename T> struct dtkMetaContainerSequentialHandlerHelper
{
    typedef typename T::value_type ValueType;

public:
    template <typename U = T> static typename std::enable_if< dtkMetaIteratorIsBidirectional<typename U::iterator>::value, bool>::type hasBidirectionalIterator(void) { return true; }
    template <typename U = T> static typename std::enable_if<!dtkMetaIteratorIsBidirectional<typename U::iterator>::value, bool>::type hasBidirectionalIterator(void) { return false; }

public:
    template <typename U = T> static typename std::enable_if< dtkMetaIteratorIsRandomAccess<typename U::iterator>::value, bool>::type hasRandomAccesIterator(void) { return true; }
    template <typename U = T> static typename std::enable_if<!dtkMetaIteratorIsRandomAccess<typename U::iterator>::value, bool>::type hasRandomAccesIterator(void) { return false; }

public:
    static bool      empty(const T *c);
    static qlonglong  size(const T *c);

public:
    static void   clear(T *c);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaContainerIsReservable<U>::value>::type reserve(T *c, qlonglong size);
    template <typename U = T> static typename std::enable_if<!dtkMetaContainerIsReservable<U>::value>::type reserve(T *c, qlonglong size);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaContainerIsResizable<U>::value>::type resize(T *c, qlonglong size);
    template <typename U = T> static typename std::enable_if<!dtkMetaContainerIsResizable<U>::value>::type resize(T *c, qlonglong size);

public:
    static void   insert(T *c, qlonglong idx, const ValueType& t);
    static void    setAt(T *c, qlonglong idx, const ValueType& t);
    static void removeAt(T *c, qlonglong idx);

public:
    static const ValueType *at(const T *c, qlonglong idx);
    static       ValueType *at(      T *c, qlonglong idx);
};

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialItemHelper
// ///////////////////////////////////////////////////////////////////

template <typename T> struct dtkMetaContainerSequentialItemHelper
{
public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsAssignable<U>::value>::type assign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if<!dtkMetaTypeIsAssignable<U>::value>::type assign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsAddAssignable<U>::value>::type addAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if<!dtkMetaTypeIsAddAssignable<U>::value>::type addAssign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsSubAssignable<U>::value>::type subAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if<!dtkMetaTypeIsSubAssignable<U>::value>::type subAssign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsMulAssignable<U>::value>::type mulAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if<!dtkMetaTypeIsMulAssignable<U>::value>::type mulAssign(T&, const T&);

public:
    template <typename U = T> static typename std::enable_if< dtkMetaTypeIsDivAssignable<U>::value>::type divAssign(T& lhs, const T& rhs);
    template <typename U = T> static typename std::enable_if<!dtkMetaTypeIsDivAssignable<U>::value>::type divAssign(T&, const T&);
};

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialPrivate::convertFunctor for QMetatype system
// /////////////////////////////////////////////////////////////////

template <typename From> struct dtkMetaContainerSequentialConvertFunctor
{    
};

template <typename From> struct dtkMetaContainerSequentialConvertFunctor<From *>
{
    dtkMetaContainerSequentialHandler *operator () (From *f) const;
};

// ///////////////////////////////////////////////////////////////////
// dtkMetaContainerSequentialRegisterConverter
// ///////////////////////////////////////////////////////////////////

template < typename T, bool = dtkMetaTypeIsSequentialContainerPointer<T>::value > struct dtkMetaContainerSequentialRegisterConverter
{
    static bool record(int id);
};

template < typename T> struct dtkMetaContainerSequentialRegisterConverter<T, true>
{
    static bool record(int id);
};

// ///////////////////////////////////////////////////////////////////

#include "dtkMetaContainerSequentialHandler.tpp"

// 
// dtkMetaContainerSequentialHandler.h ends here
