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

#include "dtkDistributedMapper.h"
#include "dtkDistributedWorker.h"

class dtkDistributedCommunicator;

// /////////////////////////////////////////////////////////////////
// dtkDistributedContainer
// /////////////////////////////////////////////////////////////////

class dtkDistributedContainer
{
public:
    dtkDistributedContainer(dtkDistributedWorker *worker) : m_worker(worker), 
                                                            m_mapper(new dtkDistributedMapper), 
                                                            m_comm(worker->communicator()) 
    {
        m_worker->record(this);
    }

public:
    virtual ~dtkDistributedContainer(void) 
    {
        m_worker->unrecord(this);
        if (m_mapper)
            delete m_mapper;
    }

public:
    virtual void setMode(const dtkDistributed::Mode&) {}

public:
    dtkDistributedWorker             *worker(void) { return m_worker; }
    dtkDistributedMapper             *mapper(void) { return m_mapper; }
    dtkDistributedCommunicator *communicator(void) { return m_comm; }

protected:
    qlonglong wid(void) { return m_worker->wid(); }
    qlonglong cid(void) { return m_worker->containerId(this); }

protected:
    dtkDistributedWorker       *m_worker;
    dtkDistributedMapper       *m_mapper;
    dtkDistributedCommunicator *m_comm;
};

// 
// dtkDistributedContainer.h ends here
