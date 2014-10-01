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

#include "dtkMetaContainerSequential.h"

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential::item implementation
// /////////////////////////////////////////////////////////////////

/*! \class dtkMetaContainerSequential::item
    \inmodule dtkMeta

    \brief The dtkMetaContainerSequential::item class enables to use
    arithmetic operations on the elements of a container in a
    QVariant.

    \snippet dtkmeta_container_sequential.cpp 5

    By default, the operators such as \c += , \c *= , \c -= , \c /= ,
    \c == or \c != are available for elements of integer and floating
    types. The += operator is also available for QString type. For any
    other types, these operators are disabled, a warning being then
    emitted.

    However, it is likely to enable all or a part of these operators
    by overloading the template struct \c
    dtkMetaContainerSequentialPrivate::itemOperator<I,T,false> where
    \c T is the type you want to deal with.

    Given a type \c Dummy that supports \c += and \c /= operators for
    instance. In order to enable these operators for an item that
    refers a \c Dummy element in a container, one must overload the
    template struct as follows:

    \code
    namespace dtkMetaContainerSequentialPrivate {
       template <typename I> struct itemOperator<I, Dummy, false> : itemOperatorBase<I, Dummy>
       {
           static void addValue(I& it, const Dummy *value) { *it += *value; }
           static void divValue(I& it, const Dummy *value) { *it /= *value; }
       };
    }
    \endcode

    Then, it is likely to use the items of the
    dtkMetaContainerSequential as if they were \c Dummy variable.

    \code
    QList<Dummy> my_list;
    my_list << Dummy() << Dummy() << Dummy();
    QVariant variant = QVariant::fromValue(&my_list);
    dtkMetaContainerSequential meta_list = variant.value<dtkMetaContainerSequential>();
    for (dtkMetaContainerSequential::item &item : meta_list) {
        item += Dummy();
        item /= Dummy();
    }
    \endcode

    \sa dtkMetaContainerSequential, dtkMetaContainerSequential::iterator
*/

/*! \fn const QVariant dtkMetaContainerSequential::item::operator * (void) const

    Returns the element referred by the item converted to a QVariant.
*/
const QVariant dtkMetaContainerSequential::item::operator * (void) const
{
    const QtMetaTypePrivate::VariantData d = m_h.currentData();
    if (d.metaTypeId == qMetaTypeId<QVariant>())
        return *reinterpret_cast<const QVariant *>(d.data);
    return QVariant(d.metaTypeId, d.data, d.flags);
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential::iterator implementation
// /////////////////////////////////////////////////////////////////

/*! \class dtkMetaContainerSequential::iterator
    \inmodule dtkMeta

    \brief The dtkMetaContainerSequential::iterator together with the
    dtkMetaContainerSequential::item enable to iterate over a container
    in a QVariant and to modify its content.

    As its const counterpart it can only be created by a
    dtkMetaContainerSequential instance, and can be used in a way
    similar to other stl-style iterators.

    Furthermore, it gives access to the element via a
    dtkMetaContainerSequential::item which provides functionalities to
    modify the element.

    \snippet dtkmeta_container_sequential.cpp 4

    \sa dtkMetaContainerSequential::item, dtkMetaContainerSequential
*/

/*! \fn dtkMetaContainerSequential::iterator::iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref)
    \internal
*/
dtkMetaContainerSequential::iterator::iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref) : m_h(container.m_handler), m_ref(ref)
{
    m_ref->ref();
    m_item = new item(this);
}

/*! \fn dtkMetaContainerSequential::iterator::iterator(const dtkMetaContainerSequentialPrivate::handler& h, QAtomicInt *ref)
    \internal
*/
dtkMetaContainerSequential::iterator::iterator(const dtkMetaContainerSequentialPrivate::handler& handler, QAtomicInt *ref) : m_h(handler), m_ref(ref)
{
    m_ref->ref();
    m_item = new item(this);
}

/*! \fn dtkMetaContainerSequential::iterator::iterator(const iterator& o)

    Creates a copy of \a o.
*/
dtkMetaContainerSequential::iterator::iterator(const iterator& o) : m_h(o.m_h), m_ref(o.m_ref)
{
    m_ref->ref();
    m_item = new item(this);
}

/*! \fn dtkMetaContainerSequential::iterator::~iterator(void)

    Detroys the iterator and the related dtkMetaContainerSequential::item.
*/
dtkMetaContainerSequential::iterator::~iterator(void)
{
    if(!m_ref->deref()) {
        m_h.destroyIterator();
        delete m_ref;
    }
    if (m_item) {
        m_item->m_iterator = NULL;
        delete m_item;
    }
}

/*! \fn dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator = (const iterator& o)

    Assigns \a o to \c this.
*/
dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator = (const iterator& o)
{
    if(!m_h.equal(o.m_h)) {
        m_h = o.m_h;
        m_ref = o.m_ref;
    }
    m_ref->ref();

    return *this;
}

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::iterator::operator [] (int j) const

    Returns a reference to the dtkMetaContainerSequential::item which
    enables to modify the element at \c *this \c + \a j pointed by the
    iterator.
*/
dtkMetaContainerSequential::item& dtkMetaContainerSequential::iterator::operator [] (int j) const
{
    iterator *it = new iterator(*this);
    *it += j;
    return *(it->m_item);
}

/*! \fn dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator ++ (int)

    The postfix ++ operator (\c{it++}) advances the iterator to the
    next element in the container and returns an iterator to the
    previously current element.
*/
dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator ++ (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copy(m_h);
    m_h.advance(1);
    return iterator(h, new QAtomicInt(0));
}

/*! \fn dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator -- (int)

    The postfix -- operator (\c{it--}) makes the preceding element
    current and returns an iterator to the previously current element.

    If the container in the QVariant does not support bi-directional
    iteration, calling this function leads to undefined results.

    \sa hasBiDirectionalIterator()
*/
dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator -- (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copy(m_h);
    m_h.advance(-1);
    return iterator(h, new QAtomicInt(0));
}

/*! \fn dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator + (int j) const

    Returns an iterator to the element at \a j positions forward from
    this iterator.

    \sa operator-(), operator+=()
*/
dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator + (int j) const
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copy(m_h);
    h.advance(j);
    return iterator(h, new QAtomicInt(0));
}

/*! \fn dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator - (int j) const

    Returns an iterator to the item at \a j positions backward from
    this iterator.

    If the container in the QVariant does not support bi-directional
    iteration, calling this function leads to undefined results.

    \sa operator+(), operator-=(), hasBiDirectionalIterator()
*/
dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator - (int j) const
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copy(m_h);
    h.advance(-j);
    return iterator(h, new QAtomicInt(0));
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential::const_iterator implementation
// /////////////////////////////////////////////////////////////////

/*! \class dtkMetaContainerSequential::const_iterator
    \inmodule dtkMeta

    \brief The dtkMetaContainerSequential::const_iterator enables to
    iterate over a pointer of a container in a QVariant.

    A dtkMetaContainerSequential::const_iterator can only be created
    by a dtkMetaContainerSequential instance, and can be used in a way
    similar to other stl-style iterators.

    \snippet dtkmeta_container_sequential.cpp 3
*/

/*! \fn dtkMetaContainerSequential::const_iterator::const_iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref)
    \internal
*/
dtkMetaContainerSequential::const_iterator::const_iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref) : m_h(container.m_handler), m_ref(ref)
{
    m_ref->ref();
}

/*! \fn dtkMetaContainerSequential::const_iterator::const_iterator(const dtkMetaContainerSequentialPrivate::handler& handler, QAtomicInt *ref)
    \internal
*/
dtkMetaContainerSequential::const_iterator::const_iterator(const dtkMetaContainerSequentialPrivate::handler& handler, QAtomicInt *ref) : m_h(handler), m_ref(ref)
{
    m_ref->ref();
}

/*! \fn dtkMetaContainerSequential::const_iterator::const_iterator(const const_iterator& o)

    Creates a copy of \a o.
*/
dtkMetaContainerSequential::const_iterator::const_iterator(const const_iterator& o) : m_h(o.m_h), m_ref(o.m_ref)
{
    m_ref->ref();
}

/*! \fn dtkMetaContainerSequential::const_iterator::const_iterator(const iterator& o)

    Creates a const_iterator that refers the same element than the iterator \a o.
*/
dtkMetaContainerSequential::const_iterator::const_iterator(const iterator& o) : m_h(o.m_h), m_ref(new QAtomicInt(0))
{
    m_h.moveToCBegin();
    m_h.advanceConst(o.m_h.indexOfIterator());
    m_ref->ref();
}

/*! \fn dtkMetaContainerSequential::const_iterator::~const_iterator(void)

    Detroys the const_iterator.
*/
dtkMetaContainerSequential::const_iterator::~const_iterator(void)
{
    if (!m_ref->deref()) {
        m_h.destroyConstIterator();
        delete m_ref;
    }
}

/*! \fn dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator = (const const_iterator& o)

    Assigns \a o to \c this.
*/
dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator = (const const_iterator& o)
{
    if (!m_h.equalConst(o.m_h)) {
        m_h = o.m_h;
        m_ref = o.m_ref;
    }
    m_ref->ref();

    return *this;
}

/*! \fn const QVariant dtkMetaContainerSequential::const_iterator::operator * (void) const

    Returns the current element, converted to a QVariant.
*/
const QVariant dtkMetaContainerSequential::const_iterator::operator * (void) const
{
    const QtMetaTypePrivate::VariantData d = m_h.currentConstData();
    if (d.metaTypeId == qMetaTypeId<QVariant>())
        return *reinterpret_cast<const QVariant *>(d.data);
    return QVariant(d.metaTypeId, d.data, d.flags);
}

/*! \fn const QVariant dtkMetaContainerSequential::const_iterator::operator [] (int j) const

    Returns the element at \c *this \c + \a j, converted to a QVariant.
*/
const QVariant dtkMetaContainerSequential::const_iterator::operator [] (int j) const
{
    const_iterator cit(*this);
    cit += j;
    return *cit;
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator ++ (int)

    The postfix ++ operator (\c{it++}) advances the iterator to the
    next element in the container and returns an iterator to the
    previously current element.
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator ++ (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copyConst(m_h);
    m_h.advanceConst(1);
    return const_iterator(h, new QAtomicInt(0));
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator -- (int)

    The postfix -- operator (\c{it--}) makes the preceding current and
    returns an iterator to the new current element.

    If the container in the QVariant does not support bi-directional
    iteration, calling this function leads to undefined results.

    \sa hasBiDirectionalIterator()
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator -- (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copyConst(m_h);
    m_h.advanceConst(-1);
    return const_iterator(h, new QAtomicInt(0));
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator + (int j) const

    Returns an iterator to the element at \a j positions forward from
    this iterator.

    \sa operator-(), operator+=()
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator + (int j) const
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copyConst(m_h);
    h.advanceConst(j);
    return const_iterator(h, new QAtomicInt(0));
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator - (int j) const

    Returns an iterator to the element at \a j positions backward from
    this iterator.

    If the container in the QVariant does not support bi-directional iteration, calling this function
    leads to undefined results.

    \sa operator+(), operator+=()
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator - (int j) const
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copyConst(m_h);
    h.advanceConst(-j);
    return const_iterator(h, new QAtomicInt(0));
}

// /////////////////////////////////////////////////////////////////
// dtkMetaContainerSequential implementation
// /////////////////////////////////////////////////////////////////

/*! \class dtkMetaContainerSequential
    \inmodule dtkMeta

    \brief The dtkMetaContainerSequential class is an interface for a
    container encapsulated as a pointer in a QVariant.

    This interface provides usual methods to handle the container held
    within a QVariant. In the manner of QSequentialIterable, it allows
    to iterate over the container without extracting it from the
    QVariant.

    \snippet dtkmeta_container_sequential.cpp 0

    However, unlike its Qt counterpart, it provides a set of methods
    that enable to modify the elements of the container. The container
    itself is never copied.

    \snippet dtkmeta_container_sequential.cpp 1

    Moreover, in order to enable the use of arithmetic operators, the
    notion of item has been introduced together with a non const
    iterator.

    \snippet dtkmeta_container_sequential.cpp 2

    Such arithmetic operators are available for container of all integer
    and floating types. The += operator is also available for container
    of QString. By default, these operators are disabled for container
    of any other types. A warning is emitted if they are used. One can
    refer to dtkMetaContainerSequential::item to know how to enable such
    operators for other types.

    \sa QSequentialIterable, QVariant
*/

/*! \fn dtkMetaContainerSequential::iterator dtkMetaContainerSequential::begin(void)

    Returns a dtkMetaContainerSequential::iterator for the beginning
    of the container. This can be used in stl-style iteration.

    \sa cbegin(), end()
*/
dtkMetaContainerSequential::iterator dtkMetaContainerSequential::begin(void)
{
    iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToBegin();
    return it;
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::begin(void) const

    This is an overloaded function.

    \sa cbegin()
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::begin(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCBegin();
    return it;
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::cbegin(void) const

    Returns a dtkMetaContainerSequential::const_iterator for the beginning
    of the container. This can be used in stl-style iteration.

    \sa begin(), cend()
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::cbegin(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCBegin();
    return it;
}

/*! \fn dtkMetaContainerSequential::iterator dtkMetaContainerSequential::end(void)

    Returns a dtkMetaContainerSequential::iterator for the end of the
    container. This can be used in stl-style iteration.

    \sa cend(), begin()
*/
dtkMetaContainerSequential::iterator dtkMetaContainerSequential::end(void)
{
    iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToEnd();
    return it;
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::end(void) const

    This is an overloaded function.

    \sa cend()
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::end(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCEnd();
    return it;
}

/*! \fn dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::cend(void) const

    Returns a dtkMetaContainerSequential::const_iterator for the end
    of the container. This can be used in stl-style iteration.

    \sa cbegin(), end()
*/
dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::cend(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCEnd();
    return it;
}

/*! \fn const QVariant dtkMetaContainerSequential::at(int idx) const

    Returns as a QVariant the item at position \a idx in the container.

    \a idx must be a valid index position in the container (i.e., 0 <=
    \a idx < size()).

    \sa operator[]()
*/
const QVariant dtkMetaContainerSequential::at(int idx) const
{
    const QtMetaTypePrivate::VariantData d = m_handler.at(idx);
    if (d.metaTypeId == qMetaTypeId<QVariant>())
        return *reinterpret_cast<const QVariant *>(d.data);
    return QVariant(d.metaTypeId, d.data, d.flags);
}

/*! \fn void dtkMetaContainerSequential::setAt(int idx, const QVariant& v)

    Replaces the item at index position \a idx with the value wrapped
    into the QVariant \a v.

    \a idx must be a valid index position in the container (i.e., 0 <=
    \a idx < size()).

    \sa at(), operator[](), removeAt()
*/
void dtkMetaContainerSequential::setAt(int idx, const QVariant& v)
{
    if (m_handler.m_metaType_id == QMetaType::QVariant)
        m_handler.setAt(idx, &v);

    m_handler.setAt(idx, v.constData());
}

/*! \fn void dtkMetaContainerSequential::insert(int idx, const QVariant& v)

    Inserts the value wrapped into QVariant \a v at index position \a
    idx in the container. If \a idx is 0, the value is prepended to
    the container. If \a idx is size(), the value is appended to the
    container.

    \sa append(), prepend(), removeAt()
*/
void dtkMetaContainerSequential::insert(int idx, const QVariant& v)
{
    if (m_handler.m_metaType_id == QMetaType::QVariant)
        m_handler.insert(idx, &v);

    m_handler.insert(idx, v.constData());
}

// ///////////////////////////////////////////////////////////////////
// Documentation of inline methods
// ///////////////////////////////////////////////////////////////////

/*! \fn dtkMetaContainerSequential::item::item(iterator *iter)
    \internal
*/

/*! \fn dtkMetaContainerSequential::item::item(const item& o)
    \internal
*/

/*! \fn dtkMetaContainerSequential::item::~item(void)

    Destroys the current dtkMetaContainerSequential::item and the
    dtkMetaContainerSequential::iterator to which it is related.
*/

/*! \fn T dtkMetaContainerSequential::item::value(void) const

    Returns the value of the element referred by the item.
*/

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator = (const item& o)

    Assigns \a o to \c this.
*/

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator = (const T& value)

    Assigns \a value to the element referred by the item.
*/

/*! \fn bool dtkMetaContainerSequential::item::operator == (const T& value)

    Returns \c true if the element referred by the item is equal to \a
    value. Otherwise returns \c false.
*/

/*! \fn bool dtkMetaContainerSequential::item::operator != (const T& value)

    Returns \c true if the element referred by the item differs from
    \a value. Otherwise returns \c false.
*/

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator += (const T& value)

    When type of the element referred by the item allows it, adds \a value to the element.

    By default, this operator is enabled for integer and floating types plus QString.
*/

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator -= (const T& value)

    When type of the element referred by the item allows it, substracts \a value to the element.

    By default, this operator is enabled for integer and floating types.
*/

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator *= (const T& value)

    When type of the element referred by the item allows it, multiplies the element by  \a value.

    By default, this operator is enabled for integer and floating types.
*/

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::item::operator /= (const T& value)

    When type of the element referred by the item allows it, divides the element by  \a value.

    By default, this operator is enabled for integer and floating types.
*/

// ///////////////////////////////////////////////////////////////////

/*! \fn dtkMetaContainerSequential::item& dtkMetaContainerSequential::iterator::operator * (void) const

    Returns the current element, converted to a dtkMetaContainerSequential::item.
*/

/*! \fn bool dtkMetaContainerSequential::iterator::operator == (const iterator& o) const

    Returns \c true if \a o points to the same item as this iterator;
    otherwise returns \c false.

    \sa operator!=()
*/

/*! \fn bool dtkMetaContainerSequential::iterator::operator != (const iterator& o) const

    Returns \c true if \a o points to a different item than this
    iterator; otherwise returns \c false.

    \sa operator==()
*/

/*! \fn dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator ++ (void)

    The prefix ++ operator (\c{++it}) advances the iterator to the
    next element in the container and returns an iterator to the new
    current element.

    Calling this function on dtkMetaContainerSequential::end() leads
    to undefined results.

    \sa operator--()
*/

/*! \fn dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator -- (void)

    The prefix -- operator (\c{--it}) makes the preceding element
    current and returns an iterator to the new current element.

    Calling this function on dtkMetaContainerSequential::begin() leads

    If the container in the QVariant does not support bi-directional
    iteration, calling this function leads to undefined results.

    \sa operator++(), hasBiDirectionalIterator()
*/

/*! \fn dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator += (int j)

    Advances the iterator by \a j elements.

    \sa operator-=(), operator+()
*/

/*! \fn dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator -= (int j)

    Makes the iterator go back by \a j elements.

    If the container in the QVariant does not support bi-directional
    iteration, calling this function leads to undefined results.

    \sa operator+=(), operator-(), hasBiDirectionalIterator()
*/

// ///////////////////////////////////////////////////////////////////

/*! \fn bool dtkMetaContainerSequential::const_iterator::operator == (const const_iterator& o) const

    Returns \c true if \a o points to the same item as this iterator;
    otherwise returns \c false.

    \sa operator!=()
*/

/*! \fn bool dtkMetaContainerSequential::const_iterator::operator != (const const_iterator& o) const

    Returns \c true if \a o points to a different item than this
    iterator; otherwise returns \c false.

    \sa operator==()
*/

/*! \fn dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator ++ (void)

    The prefix ++ operator (\c{++it}) advances the iterator to the
    next element in the container and returns an iterator to the new
    current element.

    Calling this function on dtkMetaContainerSequential::cend() leads
    to undefined results.

    \sa operator--()
*/

/*! \fn dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator -- (void)

    The prefix -- operator (\c{--it}) makes the preceding element
    current and returns an iterator to the new current element.

    Calling this function on dtkMetaContainerSequential::cbegin() leads

    If the container in the QVariant does not support bi-directional
    iteration, calling this function leads to undefined results.

    \sa operator++(), hasBiDirectionalIterator()
*/

/*! \fn dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator += (int j)

    Advances the iterator by \a j elements.

    \sa operator-=(), operator+()
*/

/*! \fn dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator -= (int j)

    Makes the iterator go back by \a j elements.

    If the container in the QVariant does not support bi-directional
    iteration, calling this function leads to undefined results.

    \sa operator+=(), operator-(), hasBiDirectionalIterator()
*/

// ///////////////////////////////////////////////////////////////////

/*! \fn dtkMetaContainerSequential::dtkMetaContainerSequential(dtkMetaContainerSequentialPrivate::handler h)
    \internal
*/

/*! \fn void dtkMetaContainerSequential::append(const T& value)

    Inserts \a value at the end of the container.

    \sa prepend(), insert()
*/

/*! \fn void dtkMetaContainerSequential::append(const QVariant& v)

    Inserts the value wrapped into QVariant \a v at the end of the
    container.

    \sa prepend(), insert()
*/

/*! \fn void dtkMetaContainerSequential::clear(void)

    Removes all the elements from the container.
*/

/*! \fn bool dtkMetaContainerSequential::empty(void) const

    Returns \c true if the container is empty; otherwise returns \c
    false.
*/

/*! \fn dtkMetaContainerSequential::item dtkMetaContainerSequential::first(void)

    Returns a the first element of the container as a
    dtkMetaContainerSequential::item. This item can be used through
    arithmetic operators such as \c += , \c *= , \c -= , \c /= , \c ==
    or \c != provided that the type of the element supports them.

    \sa last()
*/

/*! \fn const QVariant dtkMetaContainerSequential::first(void) const

    Returns a the first element of the container as a QVariant.

    \sa last()
*/

/*! \fn bool dtkMetaContainerSequential::hasBiDirectionalIterator(void) const

    Returns whether it is possible to iterate over the container in
    reverse. This corresponds to the std::bidirectional_iterator_tag
    iterator trait of the const_iterator of the container.

    \sa hasRandomAccessIterator()
*/

/*! \fn bool dtkMetaContainerSequential::hasRandomAccessIterator(void) const

    Returns \c true if the const_iterator of the container matchs
    std::random_iterator_tag iterator.

    \sa hasBiDirectionalIterator()
*/

/*! \fn void dtkMetaContainerSequential::insert(int idx, const T& value)

    Inserts \a value at index position \a idx in the container. If \a
    idx is 0, the value is prepended to the container. If \a idx is
    size(), the value is appended to the container.

    \sa append(), prepend(), removeAt()
*/

/*! \fn dtkMetaContainerSequential::item dtkMetaContainerSequential::last(void)

    Returns a the last element of the container as a
    dtkMetaContainerSequential::item. This item can be used through
    arithmetic operators such as \c += , \c *= , \c -= , \c /= , \c ==
    or \c != provided that the type of the element supports them.

    \sa first()
*/

/*! \fn const QVariant dtkMetaContainerSequential::last(void) const

    Returns a the last element of the container as a QVariant.

    \sa first()
*/

/*! \fn void dtkMetaContainerSequential::prepend(const T& value)

    Inserts \a value at the beginning of the container.

    \sa append(), insert()
*/

/*! \fn void dtkMetaContainerSequential::prepend(const QVariant& v)

    Inserts the value wrapped into QVariant \a v at the beginning of the
    container.

    \sa append(), insert()
*/

/*! \fn void dtkMetaContainerSequential::removeAt(int idx)

    Removes the element at index position \a idx.

    \sa insert(), setAt()
*/

/*! \fn void dtkMetaContainerSequential::reserve(int size)

    With respect to the container, it enables to allocate memory for
    at least \a size elements.

    Be careful, since this method is not available for every
    container. For instance, QList does not provide it. Using it will
    prompt a warning.
*/

/*! \fn void dtkMetaContainerSequential::resize(int size)

    Sets the size of the container to \a size. The growing policy
    relies on the kind of container.

    One must notice that this method is meaningless for std::list or
    QLinkedList for instance. A warning is then prompt.

    \sa size()
*/

/*! \fn void dtkMetaContainerSequential::setAt(int idx, const T& value)

    Replaces the item at index position \a idx with \a value.

    \a idx must be a valid index position in the container (i.e., 0 <=
    \a idx < size()).

    \sa at(), operator[](), removeAt()
*/

/*! \fn int dtkMetaContainerSequential::size(void) const

    Returns the number of items in the container.

    \sa resize(), empty()
*/

/*! \fn dtkMetaContainerSequential::item dtkMetaContainerSequential::operator[](int idx)

    Returns a the element at position \a idx of the container as a
    modifiable dtkMetaContainerSequential::item.

    dtkMetaContainerSequential::item can be used through arithmetic
    operators such as \c += , \c *= , \c -= , \c /= , \c == or \c \c
    != provided that the type of the element supports them.

    \sa first(), at(), last()
*/

/*! \fn const QVariant dtkMetaContainerSequential::operator[](int idx) const

    \overload

    Same as at(\a idx).

    \sa at()
*/
