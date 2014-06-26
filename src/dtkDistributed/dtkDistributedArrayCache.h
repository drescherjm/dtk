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

#include <QVarLengthArray>

template<typename T> class dtkDistributedArray;

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArrayCache
// ///////////////////////////////////////////////////////////////////

template <typename T, int Prealloc = 128, int Length = 5> class dtkDistributedArrayCache
{
public:
    typedef QVarLengthArray<T, Prealloc> Array;

public:
             dtkDistributedArrayCache(dtkDistributedArray<T> *array);
    virtual ~dtkDistributedArrayCache(void) {}

public:
    const T& value(const qlonglong& entry_id);

private:     
    Array lines[Length];
    qlonglong ids[Length];
    short counters[Length];

    dtkDistributedArray<T> *m_array;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.h"
#include "dtkDistributedMapper.h"
#include "dtkDistributedCommunicator.h"

template <typename T, int Prealloc, int Length> inline dtkDistributedArrayCache<T, Prealloc, Length>::dtkDistributedArrayCache(dtkDistributedArray<T> *array) : m_array(array)
{ 
    for (int i = 0; i < Length; ++i) { 
        ids[i] = - Prealloc - 1; 
        counters[i] = 0;
        lines[i].resize(Prealloc);
    }
}

template <typename T, int Prealloc, int Length> inline const T& dtkDistributedArrayCache<T, Prealloc, Length>::value(const qlonglong& entry_id)
{
    // Check if entry_id is already in the Cache
    int line_id = -1;
    for (int i = 0; i < Length; ++i) {
        if (entry_id >= ids[i] && entry_id < ids[i] + lines[i].size()) {
            line_id = i;
            break;
        }
    }

    // If not then find an available cache line and store remote values into it
    if (line_id < 0) {
        dtkDistributedMapper *mapper = this->m_array->mapper();
        dtkDistributedCommunicator *comm = this->m_array->communicator();

        short min_counter = counters[0];
        line_id = 0;
        for(int i = 1; i < Length; ++i) {
            if (min_counter > counters[i]) {
                min_counter = counters[i];
                line_id = i;
            }
        }
        counters[line_id] = 0;
        ids[line_id] = entry_id;

        qint32 owner  = static_cast<qint32>(mapper->owner(entry_id));
        int size = qMin(Prealloc, static_cast<int>(mapper->lastIndex(owner) - entry_id) + 1);
        lines[line_id].resize(size);

        T *line = lines[line_id].data();

        qlonglong pos = mapper->globalToLocal(entry_id);
        comm->get(owner, pos, line, m_array->dataId(), size);
    }

    counters[line_id] += 1;
    return lines[line_id].at(entry_id - ids[line_id]);
}

// 
// dtkDistributedArrayCache.h ends here
