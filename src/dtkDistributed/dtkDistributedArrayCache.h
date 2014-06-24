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

// ///////////////////////////////////////////////////////////////////
// dtkDistributedArrayCache
// ///////////////////////////////////////////////////////////////////

template <typename T, int Prealloc = 128, int Length = 5> class dtkDistributedArrayCache
{
public:
    typedef QVarLengthArray<T, Prealloc> Array;

public:
             dtkDistributedArrayCache(void);
    virtual ~dtkDistributedArrayCache(void) {}

public:
    int isCached(const qlonglong& entry_id);
    
    const T& value(const int& line_id, const qlonglong& entry_id);

    T* cacheLine(int& line_id);

    int cacheLineSize(void);

    void setCacheLineEntry(const int& line_id, const qlonglong& entry_id);

private:     
    Array lines[Length];
    qlonglong ids[Length];
    short counters[Length];
};

// ///////////////////////////////////////////////////////////////////

template <typename T, int Prealloc, int Length> inline dtkDistributedArrayCache<T, Prealloc, Length>::dtkDistributedArrayCache(void) 
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

// 
// dtkDistributedArrayCache.h ends here
