/* dtkAbstractContainerWrapper.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed May 23 17:51:33 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 19 10:26:11 2012 (+0200)
 *           By: tkloczko
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractContainerWrapper.h"
#include "dtkContainerVectorWrapper.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainerWrapper implementation
// /////////////////////////////////////////////////////////////////

dtkAbstractContainerWrapper::dtkAbstractContainerWrapper(void) : dtkAbstractData()
{
    m_container = NULL;
}

dtkAbstractContainerWrapper::dtkAbstractContainerWrapper(const dtkAbstractContainerWrapper& other) : dtkAbstractData(other)
{
    m_container = other.clone();
}

dtkAbstractContainerWrapper::~dtkAbstractContainerWrapper(void)
{
    if (this != m_container)
        delete m_container;

    m_container = NULL;
}

void dtkAbstractContainerWrapper::init(dtkAbstractContainerWrapper *wrapper)
{
    m_container = wrapper;
}

void dtkAbstractContainerWrapper::reset(void)
{
    // if (m_container && (this != m_container))
    //     delete m_container;

    // m_container = NULL;
}

bool dtkAbstractContainerWrapper::isReset(void) const
{
    if (!m_container)
        return true;

    return false;
}

dtkAbstractContainerWrapper& dtkAbstractContainerWrapper::operator=(const dtkAbstractContainerWrapper& other)
{
    if (this == &other)
        return *this;

    dtkAbstractData::operator=(other);

    if (m_container && (m_container != this))
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

dtkAbstractContainerWrapper *dtkAbstractContainerWrapper::voidClone(void) const
{
    if (m_container)
        return m_container->voidClone();

    return NULL;
}

dtkAbstractContainerWrapper *dtkAbstractContainerWrapper::container(void)
{
    return m_container;
}

QString dtkAbstractContainerWrapper::identifier(void) const
{
    if (m_container)
        return m_container->identifier();

    return "dtkAbstractContainerWrapper";
}

QString dtkAbstractContainerWrapper::description(void) const
{
    if (m_container)
        return m_container->description();

    return "dtkAbstractContainerWrapper is void! It might not be what you expect.";
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

void dtkAbstractContainerWrapper::insert(const QVariant& data, qlonglong index)
{
    if (m_container)
        m_container->insert(data, index);
}

void dtkAbstractContainerWrapper::replace(const QVariant& data, qlonglong index)
{
    if (m_container)
        m_container->replace(data, index);
}

void dtkAbstractContainerWrapper::resize(qlonglong size)
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

qlonglong dtkAbstractContainerWrapper::count(void) const
{
    if (m_container)
        return m_container->count();

    return -1;
}

qlonglong dtkAbstractContainerWrapper::indexOf(const QVariant& data, qlonglong from) const
{
    if (m_container)
        return m_container->indexOf(data, from);

    return -1;
}

QVariant dtkAbstractContainerWrapper::at(qlonglong index) const
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

