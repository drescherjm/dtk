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
    dtkDistributedItem& operator  = (const T& t) {
        op = dtkDistributedCommunicator::None;
        data = t;
        buffer = T();
        updated = true;
        return *this;
    }
    dtkDistributedItem& operator += (const T& t) {
        op = dtkDistributedCommunicator::Sum;
        buffer += t;
        updated = false;
        return *this;
    }
    dtkDistributedItem& operator -= (const T& t) {
        op = dtkDistributedCommunicator::Sum;
        buffer -= t;
        updated = false;
        return *this;
    }
    dtkDistributedItem& operator *= (const T& t) {
        op = dtkDistributedCommunicator::Product;
        buffer *= t;
        updated = false;
        return *this;
    }

public:
    T operator * (void) {
        this->update();
        return data;
    }

public:
    void update(void) {
        if (updated)
            return;

        if (op != dtkDistributedCommunicator::None) {
            T temp = buffer;
            comm->reduce(&temp, &buffer, 1, op, 0, true);

            switch (op) {
            case dtkDistributedCommunicator::Sum:
                data += buffer;
                break;

            case dtkDistributedCommunicator::Product:
                data *= buffer;
                break;

            default:
                break;
            }

            buffer = T();
        }

        updated = true;

        return;
    }

protected:
    T data;
    T buffer;
    dtkDistributedCommunicator *comm;
    dtkDistributedCommunicator::OperationType op;
    bool updated;
};

//
// dtkDistributedItem.h ends here
