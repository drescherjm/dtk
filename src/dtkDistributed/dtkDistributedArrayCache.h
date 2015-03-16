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

template <typename T, int Prealloc = 128, int Length = 32> class dtkDistributedArrayCache
{
    typedef dtkDistributedArray<T> DSArray;

public:
    typedef QVarLengthArray<T, Prealloc> Array;

public:
             dtkDistributedArrayCache(DSArray *array);
    virtual ~dtkDistributedArrayCache(void) {}

public:
    void clear(void);

    const T& value(const qlonglong& entry_id);
    double hitrate(void);

private:     
    Array lines[Length];
    qlonglong ids[Length];
    qlonglong hit;
    qlonglong miss;
    int       last;

//dtkDistributedArray<T> *m_array;
    DSArray *m_array;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.h"
#include "dtkDistributedMapper.h"
#include "dtkDistributedCommunicator.h"

template <typename T, int Prealloc, int Length> inline dtkDistributedArrayCache<T, Prealloc, Length>::dtkDistributedArrayCache(DSArray *array) : m_array(array)
{ 
    for (int i = 0; i < Length; ++i) { 
        ids[i] = - Prealloc - 1; 
        lines[i].resize(Prealloc);
    }
    hit  = 0;
    miss = 0;
    last = -1;
}

template <typename T, int Prealloc, int Length> inline void dtkDistributedArrayCache<T, Prealloc, Length>::clear(void)
{
    for (int i = 0; i < Length; ++i) { 
        ids[i] = - Prealloc - 1; 
        lines[i].resize(0);
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
        miss++;
        line_id = (last +1) % Length;
        ids[line_id] = entry_id;

        qlonglong size = Prealloc;
        m_array->copyIntoArray(entry_id, lines[line_id].data(), size);
        lines[line_id].resize(size);
    } else {
        hit ++;
    }

    last = line_id;
    return lines[line_id].at(entry_id - ids[line_id]);
}

template <typename T, int Prealloc, int Length> inline double dtkDistributedArrayCache<T, Prealloc, Length>::hitrate()
{
    qlonglong sum = miss+hit;
    qDebug() <<"misses:" << miss << "hits:" << hit ;

    if (sum == 0)
        return 0;

    return double(hit) / (double)(sum);
}
//
// dtkDistributedArrayCache.h ends here
