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

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkDistributedIterator
// ///////////////////////////////////////////////////////////////////

template <typename Container> class dtkDistributedIterator
{
    const Container& c;
    qlonglong gid;

public:
    typedef std::random_access_iterator_tag     iterator_category;
    typedef typename Container::value_type      value_type;
    typedef typename Container::difference_type difference_type;
    typedef value_type*                         pointer;
    typedef value_type&                         reference;

public:
    explicit dtkDistributedIterator(const Container& container, qlonglong index);

public:
    qlonglong id(void) const;

public:
    value_type operator *  (void) const;
    value_type operator [] (qlonglong j) const;

public:
    bool operator == (const dtkDistributedIterator& o) const;
    bool operator != (const dtkDistributedIterator& o) const;
    bool operator <  (const dtkDistributedIterator& o) const;
    bool operator <= (const dtkDistributedIterator& o) const;
    bool operator >  (const dtkDistributedIterator& o) const;
    bool operator >= (const dtkDistributedIterator& o) const;

public:
    dtkDistributedIterator& operator ++ (void);
    dtkDistributedIterator  operator ++ (int);
    dtkDistributedIterator& operator -- (void);
    dtkDistributedIterator  operator -- (int);
    dtkDistributedIterator& operator += (qlonglong j);
    dtkDistributedIterator& operator -= (qlonglong j);
    dtkDistributedIterator  operator +  (qlonglong j) const;
    dtkDistributedIterator  operator -  (qlonglong j) const;

public:
    qlonglong operator - (const dtkDistributedIterator& o) const;
};

// ///////////////////////////////////////////////////////////////////

template <typename Container> inline dtkDistributedIterator<Container>::dtkDistributedIterator(const Container& container, qlonglong index) : c(container), gid(index)
{
}

template <typename Container> inline qlonglong dtkDistributedIterator<Container>::id(void) const
{
    return gid;
}

template <typename Container> inline typename dtkDistributedIterator<Container>::value_type dtkDistributedIterator<Container>::operator * (void) const
{
    return c[gid];
}

template <typename Container> inline typename dtkDistributedIterator<Container>::value_type dtkDistributedIterator<Container>::operator [] (qlonglong j) const
{
    return c[gid + j];
}

template <typename Container> inline bool dtkDistributedIterator<Container>::operator == (const dtkDistributedIterator& o) const
{
    return gid == o.gid;
}

template <typename Container> inline bool dtkDistributedIterator<Container>::operator != (const dtkDistributedIterator& o) const
{
    return gid != o.gid;
}

template <typename Container> inline bool dtkDistributedIterator<Container>::operator < (const dtkDistributedIterator& o) const
{
    return gid < o.gid;
}

template <typename Container> inline bool dtkDistributedIterator<Container>::operator <= (const dtkDistributedIterator& o) const
{
    return gid <= o.gid;
}

template <typename Container> inline bool dtkDistributedIterator<Container>::operator > (const dtkDistributedIterator& o) const
{
    return gid > o.gid;
}

template <typename Container> inline bool dtkDistributedIterator<Container>::operator >= (const dtkDistributedIterator& o) const
{
    return gid >= o.gid;
}

template <typename Container> inline dtkDistributedIterator<Container>& dtkDistributedIterator<Container>::operator ++ (void)
{
    ++gid; return *this;
}

template <typename Container> inline dtkDistributedIterator<Container> dtkDistributedIterator<Container>::operator ++ (int)
{
    ++gid; return dtkDistributedIterator(c, gid - 1);
}

template <typename Container> inline dtkDistributedIterator<Container>& dtkDistributedIterator<Container>::operator -- (void)
{
    --gid; return *this;
}

template <typename Container> inline dtkDistributedIterator<Container> dtkDistributedIterator<Container>::operator -- (int)
{
    --gid; return dtkDistributedIterator(c, gid + 1);
}

template <typename Container> inline dtkDistributedIterator<Container>& dtkDistributedIterator<Container>::operator += (qlonglong j)
{
    gid += j; return *this;
}

template <typename Container> inline dtkDistributedIterator<Container>& dtkDistributedIterator<Container>::operator -= (qlonglong j)
{
    gid-= j; return *this;
}

template <typename Container> inline dtkDistributedIterator<Container> dtkDistributedIterator<Container>::operator + (qlonglong j) const
{
    return dtkDistributedIterator(c, gid + j);
}

template <typename Container> inline dtkDistributedIterator<Container> dtkDistributedIterator<Container>::operator - (qlonglong j) const
{
    return dtkDistributedIterator(c, gid - j);
}

template <typename Container> inline qlonglong dtkDistributedIterator<Container>::operator - (const dtkDistributedIterator& o) const
{
    return (gid - o.gid);
}


// 
// dtkDistributedIterator.h ends here
