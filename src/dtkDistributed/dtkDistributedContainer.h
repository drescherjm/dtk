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

#include "dtkDistributed.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedMapper.h"
#include "dtkDistributedExport.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedContainer
{
public:
    dtkDistributedContainer(void);
    dtkDistributedContainer(const qlonglong& size);
    dtkDistributedContainer(const qlonglong& size, dtkDistributedMapper *mapper);

public:
    virtual ~dtkDistributedContainer(void);

public:
    void setMapper(dtkDistributedMapper *mapper);

public:
    bool      empty(void) const;
    qlonglong  size(void) const;

public:
    dtkDistributedMapper             *mapper(void) const;
    dtkDistributedCommunicator *communicator(void) const;

public:
    qlonglong wid(void) const;

public:
    bool deref(void);
    bool   ref(void);

protected:
    QAtomicInt m_ref;

protected:
    qlonglong m_size;

    dtkDistributedMapper       *m_mapper;
    dtkDistributedCommunicator *m_comm;
    qint32                     m_wid;
};

// /////////////////////////////////////////////////////////////////

inline dtkDistributedContainer::dtkDistributedContainer(void) : m_ref(1), m_size(0), m_mapper(new dtkDistributedMapper), m_comm(dtkDistributed::communicator::instance()), m_wid(m_comm->wid())
{
    m_mapper->ref();
}


inline dtkDistributedContainer::dtkDistributedContainer(const qlonglong& size) : m_ref(1), m_size(size), m_mapper(new dtkDistributedMapper), m_comm(dtkDistributed::communicator::instance()), m_wid(m_comm->wid())
{
    m_mapper->ref();
    if (m_size > 0) {
        m_mapper->setMapping(m_size, m_comm->size());
    }
}

inline dtkDistributedContainer::dtkDistributedContainer(const qlonglong& size, dtkDistributedMapper *mapper) : m_ref(1), m_size(size), m_mapper(mapper), m_comm(dtkDistributed::communicator::instance()), m_wid(m_comm->wid())
{
    m_mapper->ref();
}

inline dtkDistributedContainer::~dtkDistributedContainer(void)
{
    if (!m_mapper->deref())
        delete m_mapper;
}

inline void dtkDistributedContainer::setMapper(dtkDistributedMapper *mapper) 
{ 
    if (!m_mapper->deref())
        delete m_mapper;
    
    m_mapper = mapper;
    m_mapper->ref();
}

inline bool dtkDistributedContainer::empty(void) const
{
    return !m_size;
}

inline qlonglong dtkDistributedContainer::size(void) const
{ 
    return  m_size;
}

inline dtkDistributedMapper *dtkDistributedContainer::mapper(void) const
{
    return m_mapper;
}

inline dtkDistributedCommunicator *dtkDistributedContainer::communicator(void) const
{ 
    return m_comm;
}

inline qlonglong dtkDistributedContainer::wid(void) const
{
    return m_wid;
}
    
inline bool dtkDistributedContainer::deref(void)
{
    return m_ref.deref();
}

inline bool dtkDistributedContainer::ref(void)
{
    return m_ref.ref();
}

//
// dtkDistributedContainer.h ends here
