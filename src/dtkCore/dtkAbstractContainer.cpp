/* dtkAbstractContainer.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Apr 27 16:15:20 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon May 21 15:44:34 2012 (+0200)
 *           By: tkloczko
 *     Update #: 88
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkAbstractContainer.h"

// /////////////////////////////////////////////////////////////////
// dtkAbstractContainer implementation
// /////////////////////////////////////////////////////////////////

dtkAbstractContainer::dtkAbstractContainer(dtkAbstractData *parent) : dtkAbstractData(parent)
{
    m_container = NULL;
}

dtkAbstractContainer::dtkAbstractContainer(const dtkAbstractContainer& other) : dtkAbstractData(other)
{
    m_container = other.clone();
}

dtkAbstractContainer::~dtkAbstractContainer(void)
{
    delete m_container;

    m_container = NULL;
}

void dtkAbstractContainer::init(void)
{
    m_container = NULL;
}

void dtkAbstractContainer::reset(void)
{
    if (m_container) {
        delete m_container;
        m_container = NULL;
    }
}

dtkAbstractContainer& dtkAbstractContainer::operator=(const dtkAbstractContainer& other)
{
    dtkAbstractData::operator=(other);

    if (m_container)
        delete m_container;

    m_container = other.clone();

    return *this;
}

dtkAbstractContainer *dtkAbstractContainer::clone(void) const
{
    if (m_container)
        return m_container->clone();

    return NULL;
}

QString dtkAbstractContainer::identifier(void) const
{
    return "dtkAbstractContainer";
}

void dtkAbstractContainer::setName(const QString& name)
{
    this->setObjectName(name);
}

QString dtkAbstractContainer::name(void) const
{
    return this->objectName();
}

dtkAbstractContainer::Type dtkAbstractContainer::type(void) const
{
    if (m_container)
        return m_container->type();

    return None;
}

void dtkAbstractContainer::clear(void)
{
    if (m_container)
        m_container->clear();
}

void dtkAbstractContainer::append(const QVariant& data)
{
    if (m_container)
        m_container->append(data);
}

void dtkAbstractContainer::prepend(const QVariant& data)
{
    if (m_container)
        m_container->prepend(data);
}

void dtkAbstractContainer::remove(const QVariant& data)
{
    if (m_container)
        m_container->remove(data);
}

void dtkAbstractContainer::insert(const QVariant& data, qlonglong index)
{
    if (m_container)
        m_container->insert(data, index);
}

void dtkAbstractContainer::replace(const QVariant& data, qlonglong index)
{
    if (m_container)
        m_container->replace(data, index);
}

void dtkAbstractContainer::resize(qlonglong size)
{
    if (m_container)
        m_container->resize(size);
}

bool dtkAbstractContainer::isEmpty(void) const
{
    if (m_container)
        return m_container->isEmpty();

    return true;
}

bool dtkAbstractContainer::contains(const QVariant& data) const
{
    if (m_container)
        return m_container->contains(data);

    return false;
}

qlonglong dtkAbstractContainer::count(void) const
{
    if (m_container)
        return m_container->count();

    return -1;
}

qlonglong dtkAbstractContainer::indexOf(const QVariant& data, qlonglong from) const
{
    if (m_container)
        return m_container->indexOf(data, from);

    return -1;
}

QVariant dtkAbstractContainer::at(qlonglong index) const
{
    if (m_container)
        return m_container->at(index);

    return QVariant();
}

QVariant dtkAbstractContainer::first(void) const
{
    if (m_container)
        return m_container->first();

    return QVariant();
}

QVariant dtkAbstractContainer::last(void) const
{
    if (m_container)
        return m_container->last();

    return QVariant();
}

bool dtkAbstractContainer::operator != (const dtkAbstractContainer& other) const
{
    if (m_container)
        return !m_container->isEqual(other);

    return true;
}

bool dtkAbstractContainer::operator == (const dtkAbstractContainer& other) const
{
    if (m_container)
        return m_container->isEqual(other);

    return false;
}

bool dtkAbstractContainer::isEqual(const dtkAbstractContainer& other) const
{
    if (m_container)
        return m_container->isEqual(other);

    return false;
}

