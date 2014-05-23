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

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkDistributedItem
{
public:
    explicit dtkDistributedItem(dtkDistributedCommunicator *communicator) : data(T()), comm(communicator), op(dtkDistributedCommunicator::None), updated(true) {}

public:
    dtkDistributedItem& operator  = (const T& t) { op = dtkDistributedCommunicator::None;     data  = t; updated = true;  return *this; }
    dtkDistributedItem& operator += (const T& t) { op = dtkDistributedCommunicator::dtkDistributedCommunicatorSum;      data += t; updated = false; return *this; }

public:
    T operator * (void) { this->update(); return data; }


protected:
    void update(void)
    {
        if (updated)
            return;

        if (op != dtkDistributedCommunicator::None) {
            T temp = data;
            comm->reduce(&temp, &data, 1, op, 0, true);
        }
        updated = true;

        return;
    }

protected:
    T data;
    dtkDistributedCommunicator *comm;
    dtkDistributedCommunicator::OperationType op;
    bool updated;
};

// 
// dtkDistributedItem.h ends here
