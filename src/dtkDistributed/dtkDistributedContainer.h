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
#include "dtkDistributedMapper.h"
#include "dtkDistributedWorker.h"

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer
// /////////////////////////////////////////////////////////////////

class dtkDistributedContainer
{
public:
    dtkDistributedContainer(dtkDistributedWorker *worker) : 
        m_size(0),
        m_worker(worker), 
        m_mapper(new dtkDistributedMapper), 
        m_comm(worker->communicator()) 
    {
        m_mapper->ref();
        m_worker->record(this);
    }

    dtkDistributedContainer(const qlonglong& size, dtkDistributedWorker *worker) : 
        m_size(size),
        m_worker(worker), 
        m_mapper(new dtkDistributedMapper), 
        m_comm(worker->communicator()) 
    {
        m_mapper->ref();
        m_worker->record(this);
        if (m_size > 0) {
            m_mapper->setMapping(m_size, m_comm->size());
        }
    }

    dtkDistributedContainer(const qlonglong& size, dtkDistributedWorker *worker, dtkDistributedMapper *mapper) : 
        m_size(size),
        m_worker(worker), 
        m_mapper(mapper), 
        m_comm(worker->communicator()) 
    {
        m_mapper->ref();
        m_worker->record(this);
    }

public:
    virtual ~dtkDistributedContainer(void) 
    {
        m_worker->unrecord(this);
        if (!m_mapper->deref())
            delete m_mapper;
    }

public:
    virtual void setMode(const dtkDistributed::Mode&) {}

public:
    bool      empty(void) const { return !m_size; }
    qlonglong  size(void) const { return  m_size; }

public:
    dtkDistributedWorker             *worker(void) { return m_worker; }
    dtkDistributedMapper             *mapper(void) { return m_mapper; }
    dtkDistributedCommunicator *communicator(void) { return m_comm; }

public:
    qlonglong wid(void) const { return m_worker->wid(); }
    qlonglong cid(void) const { return m_worker->containerId(this); }

protected:
    qlonglong m_size;

    dtkDistributedWorker       *m_worker;
    dtkDistributedMapper       *m_mapper;
    dtkDistributedCommunicator *m_comm;
};

// 
// dtkDistributedContainer.h ends here
