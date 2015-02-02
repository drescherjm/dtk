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

#include "dtkDistributedCommunicator.h"
#include "dtkDistributedCoreApplication.h"
#include "dtkDistributedMapper.h"
#include "dtkDistributedWorker.h"
#include "dtkDistributedExport.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer
// /////////////////////////////////////////////////////////////////

class DTKDISTRIBUTED_EXPORT dtkDistributedContainer
{
public:
    dtkDistributedContainer(void) :
        m_size(0),
        /* m_worker(dtkDistributed::app()->worker()), */
        m_mapper(new dtkDistributedMapper),
            m_comm(dtkDistributed::app()->communicator())
    {
        m_mapper->ref();
    }

    dtkDistributedContainer(const qlonglong& size) :
        m_size(size),
        /* m_worker(dtkDistributed::app()->worker()), */
        m_mapper(new dtkDistributedMapper),
        m_comm(dtkDistributed::app()->communicator())
    {
        m_mapper->ref();
        if (m_size > 0) {
            m_mapper->setMapping(m_size, m_comm->size());
        }
    }

    dtkDistributedContainer(const qlonglong& size, dtkDistributedMapper *mapper) :
        m_size(size),
        /* m_worker(dtkDistributed::app()->worker()), */
        m_mapper(mapper),
        m_comm(dtkDistributed::app()->communicator())
    {
        m_mapper->ref();
    }

public:
    virtual ~dtkDistributedContainer(void)
    {
        if (!m_mapper->deref())
            delete m_mapper;
    }

public:
    bool      empty(void) const { return !m_size; }
    qlonglong  size(void) const { return  m_size; }

public:
    /* dtkDistributedWorker             *worker(void) { return m_worker; } */
    dtkDistributedMapper             *mapper(void) { return m_mapper; }
    dtkDistributedCommunicator *communicator(void) { return m_comm; }

public:
    qlonglong wid(void) const { return m_comm->wid(); }

protected:
    qlonglong m_size;

    /* dtkDistributedWorker       *m_worker; */
    dtkDistributedMapper       *m_mapper;
    dtkDistributedCommunicator *m_comm;
};

//
// dtkDistributedContainer.h ends here
