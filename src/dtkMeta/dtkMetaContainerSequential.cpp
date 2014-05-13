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

dtkMetaContainerSequential::iterator::iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref) : m_h(container.m_handler), m_ref(ref)
{
    m_ref->ref();
    m_item = new item(this);
}

dtkMetaContainerSequential::iterator::iterator(const dtkMetaContainerSequentialPrivate::handler& handler, QAtomicInt *ref) : m_h(handler), m_ref(ref)
{
    m_ref->ref();
    m_item = new item(this);
}

dtkMetaContainerSequential::iterator::iterator(const iterator& o) : m_h(o.m_h), m_ref(o.m_ref)
{
    m_ref->ref();
    m_item = new item(this);
}

dtkMetaContainerSequential::iterator::~iterator(void)
{
    if (!m_ref->deref()) {
        m_h.destroyIterator();
        delete m_ref;
    }
    if (m_item) {
        m_item->m_iterator = NULL;
        delete m_item;
    }
}

dtkMetaContainerSequential::iterator& dtkMetaContainerSequential::iterator::operator = (const iterator& o)
{
    if (!m_h.equal(o.m_h)) {
        m_h = o.m_h;
        m_ref = o.m_ref;
    }
    m_ref->ref();
    
    return *this;
}

dtkMetaContainerSequential::item& dtkMetaContainerSequential::iterator::operator [] (int j) const
{
    iterator *it = new iterator(*this);
    *it += j;
    return *(it->m_item);
}

dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator ++ (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copy(m_h);
    m_h.advance(1);
    return iterator(h, new QAtomicInt(0));
}

dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator -- (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copy(m_h);
    m_h.advance(-1);
    return iterator(h, new QAtomicInt(0));
}

dtkMetaContainerSequential::iterator dtkMetaContainerSequential::iterator::operator + (int j) const
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copy(m_h);
    h.advance(j);
    return iterator(h, new QAtomicInt(0));
}

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

dtkMetaContainerSequential::const_iterator::const_iterator(const dtkMetaContainerSequential& container, QAtomicInt *ref) : m_h(container.m_handler), m_ref(ref)
{
    m_ref->ref();
}

dtkMetaContainerSequential::const_iterator::const_iterator(const dtkMetaContainerSequentialPrivate::handler& handler, QAtomicInt *ref) : m_h(handler), m_ref(ref)
{
    m_ref->ref();
}

dtkMetaContainerSequential::const_iterator::const_iterator(const const_iterator& o) : m_h(o.m_h), m_ref(o.m_ref)
{
    m_ref->ref();
}

dtkMetaContainerSequential::const_iterator::const_iterator(const iterator& o) : m_h(o.m_h), m_ref(new QAtomicInt(0))
{
    m_h.moveToCBegin();
    m_h.advanceConst(o.m_h.indexOfIterator());
    m_ref->ref();
}

dtkMetaContainerSequential::const_iterator::~const_iterator(void)
{
    if (!m_ref->deref()) {
        m_h.destroyConstIterator();
        delete m_ref;
    }
}

dtkMetaContainerSequential::const_iterator& dtkMetaContainerSequential::const_iterator::operator = (const const_iterator& o)
{
    if (!m_h.equalConst(o.m_h)) {
        m_h = o.m_h;
        m_ref = o.m_ref;
    }
    m_ref->ref();
    
    return *this;
}

const QVariant dtkMetaContainerSequential::const_iterator::operator * (void) const
{
    const QtMetaTypePrivate::VariantData d = m_h.currentConstData();
    if (d.metaTypeId == qMetaTypeId<QVariant>())
        return *reinterpret_cast<const QVariant *>(d.data);
    return QVariant(d.metaTypeId, d.data, d.flags);
}

const QVariant dtkMetaContainerSequential::const_iterator::operator [] (int j) const
{
    const_iterator cit(*this);
    cit += j;
    return *cit;
}

dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator ++ (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copyConst(m_h);
    m_h.advanceConst(1);
    return const_iterator(h, new QAtomicInt(0));
}

dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator -- (int)
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copyConst(m_h);
    m_h.advanceConst(-1);
    return const_iterator(h, new QAtomicInt(0));
}

dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::const_iterator::operator + (int j) const
{
    dtkMetaContainerSequentialPrivate::handler h;
    h.copyConst(m_h);
    h.advanceConst(j);
    return const_iterator(h, new QAtomicInt(0));
}

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

dtkMetaContainerSequential::iterator dtkMetaContainerSequential::begin(void)
{
    iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToBegin();
    return it;
}

dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::begin(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCBegin();
    return it;
}

dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::cbegin(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCBegin();
    return it;
}

dtkMetaContainerSequential::iterator dtkMetaContainerSequential::end(void)
{
    iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToEnd();
    return it;
}

dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::end(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCEnd();
    return it;
}

dtkMetaContainerSequential::const_iterator dtkMetaContainerSequential::cend(void) const
{
    const_iterator it(this->m_handler, new QAtomicInt(0));
    it.m_h.moveToCEnd();
    return it;
}

const QVariant dtkMetaContainerSequential::at(int idx) const
{
    const QtMetaTypePrivate::VariantData d = m_handler.at(idx);
    if (d.metaTypeId == qMetaTypeId<QVariant>())
        return *reinterpret_cast<const QVariant *>(d.data);
    return QVariant(d.metaTypeId, d.data, d.flags);
}

void dtkMetaContainerSequential::setAt(int idx, const QVariant& v)
{
    if (m_handler.m_metaType_id == QMetaType::QVariant)
        m_handler.setAt(idx, &v);

    m_handler.setAt(idx, v.constData());
}

void dtkMetaContainerSequential::insert(int idx, const QVariant& v)
{
    if (m_handler.m_metaType_id == QMetaType::QVariant)
        m_handler.insert(idx, &v);

    m_handler.insert(idx, v.constData());
}
