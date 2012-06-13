/* dtkAbstractContainerWrapper.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May 23 17:51:33 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri May 25 09:29:13 2012 (+0200)
 *           By: tkloczko
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractContainerWrapper.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainerWrapper implementation
// /////////////////////////////////////////////////////////////////

dtkAbstractContainerWrapper::dtkAbstractContainerWrapper(dtkAbstractData *parent) : dtkAbstractData(parent)
{
    m_container = NULL;
}

dtkAbstractContainerWrapper::dtkAbstractContainerWrapper(const dtkAbstractContainerWrapper& other) : dtkAbstractData(other)
{
    m_container = other.clone();
}

dtkAbstractContainerWrapper::~dtkAbstractContainerWrapper(void)
{
    delete m_container;

    m_container = NULL;
}

void dtkAbstractContainerWrapper::init(void)
{
    m_container = NULL;
}

void dtkAbstractContainerWrapper::reset(void)
{
    if (m_container) {
        delete m_container;
        m_container = NULL;
    }
}

dtkAbstractContainerWrapper& dtkAbstractContainerWrapper::operator=(const dtkAbstractContainerWrapper& other)
{
    dtkAbstractData::operator=(other);

    if (m_container)
        delete m_container;

    m_container = other.clone();

    return *this;
}

dtkAbstractContainerWrapper *dtkAbstractContainerWrapper::clone(void) const
{
    if (m_container)
        return m_container->clone();

    return NULL;
}

QString dtkAbstractContainerWrapper::identifier(void) const
{
    return "dtkAbstractContainerWrapper";
}

void dtkAbstractContainerWrapper::setName(const QString& name)
{
    this->setObjectName(name);
}

QString dtkAbstractContainerWrapper::name(void) const
{
    return this->objectName();
}

dtkAbstractContainerWrapper::Type dtkAbstractContainerWrapper::type(void) const
{
    if (m_container)
        return m_container->type();

    return None;
}

void dtkAbstractContainerWrapper::clear(void)
{
    if (m_container)
        m_container->clear();
}

void dtkAbstractContainerWrapper::append(const QVariant& data)
{
    if (m_container)
        m_container->append(data);
}

void dtkAbstractContainerWrapper::prepend(const QVariant& data)
{
    if (m_container)
        m_container->prepend(data);
}

void dtkAbstractContainerWrapper::remove(const QVariant& data)
{
    if (m_container)
        m_container->remove(data);
}

void dtkAbstractContainerWrapper::insert(const QVariant& data, dtkxarch_int index)
{
    if (m_container)
        m_container->insert(data, index);
}

void dtkAbstractContainerWrapper::replace(const QVariant& data, dtkxarch_int index)
{
    if (m_container)
        m_container->replace(data, index);
}

void dtkAbstractContainerWrapper::resize(dtkxarch_int size)
{
    if (m_container)
        m_container->resize(size);
}

bool dtkAbstractContainerWrapper::isEmpty(void) const
{
    if (m_container)
        return m_container->isEmpty();

    return true;
}

bool dtkAbstractContainerWrapper::contains(const QVariant& data) const
{
    if (m_container)
        return m_container->contains(data);

    return false;
}

dtkxarch_int dtkAbstractContainerWrapper::count(void) const
{
    if (m_container)
        return m_container->count();

    return -1;
}

dtkxarch_int dtkAbstractContainerWrapper::indexOf(const QVariant& data, dtkxarch_int from) const
{
    if (m_container)
        return m_container->indexOf(data, from);

    return -1;
}

QVariant dtkAbstractContainerWrapper::at(dtkxarch_int index) const
{
    if (m_container)
        return m_container->at(index);

    return QVariant();
}

bool dtkAbstractContainerWrapper::operator != (const dtkAbstractContainerWrapper& other) const
{
    if (m_container)
        return !m_container->isEqual(other);

    return true;
}

bool dtkAbstractContainerWrapper::operator == (const dtkAbstractContainerWrapper& other) const
{
    if (m_container)
        return m_container->isEqual(other);

    return false;
}

bool dtkAbstractContainerWrapper::isEqual(const dtkAbstractContainerWrapper& other) const
{
    if (m_container)
        return m_container->isEqual(other);

    return false;
}

