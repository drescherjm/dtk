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
    int isCached(const qlonglong& entry_id);
    
    const T& value(const int& line_id, const qlonglong& entry_id);
    const T& value(const qlonglong& entry_id);

    T* cacheLine(int& line_id);

    int cacheLineSize(void);

    void setCacheLineEntry(const int& line_id, const qlonglong& entry_id);

private:     
    Array lines[Length];
    qlonglong ids[Length];
    short counters[Length];

    dtkDistributedArray<T> *m_array;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkDistributedArray.h"

template <typename T, int Prealloc, int Length> inline dtkDistributedArrayCache<T, Prealloc, Length>::dtkDistributedArrayCache(dtkDistributedArray<T> *array) : m_array(array)
{ 
    for (int i = 0; i < Length; ++i) { 
        ids[i] = - Prealloc - 1; 
        counters[i] = 0;
        lines[i].resize(Prealloc);
    }
}

template <typename T, int Prealloc, int Length> inline int dtkDistributedArrayCache<T, Prealloc, Length>::isCached(const qlonglong& entry_id)
{
    for (int i = 0; i < Length; ++i) {
        if (entry_id < ids[i] || entry_id >= ids[i] + lines[i].size()) continue;
        return i;
    }
    return -1;
}

template <typename T, int Prealloc, int Length> inline const T& dtkDistributedArrayCache<T, Prealloc, Length>::value(const int& line_id, const qlonglong& entry_id)
{
    counters[line_id] += 1;
    return lines[line_id].at(entry_id - ids[line_id]);
}

template <typename T, int Prealloc, int Length> inline T *dtkDistributedArrayCache<T, Prealloc, Length>::cacheLine(int& line_id)
{
    short min_counter = counters[0];
    line_id = 0;
    for(int i = 1; i < Length; ++i) {
        if (min_counter > counters[i]) {
            min_counter = counters[i];
            line_id = i;
        }
    }
    counters[line_id] = 0;
    return const_cast<T *>(lines[line_id].data());
}

template <typename T, int Prealloc, int Length> inline int dtkDistributedArrayCache<T, Prealloc, Length>::cacheLineSize(void)
{
    return lines[0].size();
}

template <typename T, int Prealloc, int Length> inline void dtkDistributedArrayCache<T, Prealloc, Length>::setCacheLineEntry(const int& line_id, const qlonglong& entry_id)
{
    ids[line_id] = entry_id;
}

template <typename T, int Prealloc, int Length> inline const T& dtkDistributedArrayCache<T, Prealloc, Length>::value(const qlonglong& entry_id)
{
    qint32 owner  = static_cast<qint32>(this->m_array->mapper()->owner(entry_id));
    qlonglong pos = this->m_array->mapper()->globalToLocal(entry_id);

    int line_id = this->isCached(entry_id);
    if (line_id < 0) {            
        T *line = this->cacheLine(line_id);
        this->setCacheLineEntry(line_id, entry_id);
        int size = qMin(Prealloc, static_cast<int>(this->m_array->size() - entry_id));
        this->m_array->communicator()->get(owner, pos, line, m_array->dataId(), size);
    }
    counters[line_id] += 1;
    return lines[line_id].at(entry_id - ids[line_id]);
}

// 
// dtkDistributedArrayCache.h ends here
