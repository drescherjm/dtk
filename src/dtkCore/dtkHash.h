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

#include <functional>
#include <utility>

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

template <typename SizeT> inline void dtkHashCombineImpl(SizeT& seed, SizeT value)
{
    seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

template < typename T > inline void dtkHashCombine(std::size_t& seed, T const& v)
{
    std::hash<T> hasher;
    dtkHashCombineImpl(seed, hasher(v));
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

template < typename It > inline void dtkHashRange(It first, It last)
{
    std::size_t seed = 0;

    for(; first != last; ++first) {
        std::hash<T> hasher;
        dtkHashCombineImpl(seed, hasher(*first));
    }

    return seed;
}

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

struct dtkHash
{
public:
    template < typename T, typename U > std::size_t operator()(const std::pair<T, U>& c) const;

    template < typename T, typename A > std::size_t operator()(const std::vector<T, A>& c) const;

    template < typename T, typename A > std::size_t operator()(const std::list<T, A>& c) const;

    template < typename T, typename A > std::size_t operator()(const std::deque<T, A>& c) const;

    template < typename K, typename C, typename A > std::size_t operator()(const std::set<K, C, A>& c) const;

    template < typename K, typename C, typename A > std::size_t operator()(const std::multiset<K, C, A>& c) const;

    template < typename K, typename T, typename C, typename A > std::size_t operator()(const std::map<K, T, C, A>& c) const;

    template < typename K, typename T, typename C, typename A > std::size_t operator()(const std::multimap<K, T, C, A>& c) const;
};

// /////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////

template < typename T, typename U > inline std::size_t dtkHash::operator()(const std::pair<T, U>& c) const
{
    std::size_t seed = 0;
    dtkHashCombine(seed, c.first);
    dtkHashCombine(seed, c.second);
    return seed;
}

template < typename T, typename A > inline std::size_t dtkHash::operator()(std::vector<T, A> const& c)
{
    return dtkHashRange(c.begin(), c.end());
}

template < typename T, typename A > inline std::size_t dtkHash::operator()(std::list<T, A> const& c)
{
    return dtkHashRange(c.begin(), c.end());
}

template < typename T, typename A > inline std::size_t dtkHash::operator()(std::deque<T, A> const& c)
{
    return dtkHashRange(c.begin(), c.end());
}

template < typename K, typename C, typename A > inline std::size_t dtkHash::operator()(std::set<K, C, A> const& c)
{
    return dtkHashRange(c.begin(), c.end());
}

template < typename K, typename C, typename A > inline std::size_t dtkHash::operator()(std::multiset<K, C, A> const& c)
{
    return dtkHashRange(c.begin(), c.end());
}

template < typename K, typename T, typename C, typename A> inline std::size_t dtkHash::operator()(std::map<K, T, C, A> const& c)
{
    return dtkHashRange(c.begin(), c.end());
}

template < typename K, typename T, typename C, typename A > inline std::size_t dtkHash::operator()(std::multimap<K, T, C, A> const& c)
{
    return dtkHashRange(c.begin(), c.end());
}

template < typename T > inline std::size_t dtkHash::operator()(std::complex<T> const& c)
{
    std::size_t seed = 0;
    dtkHashCombine(seed, c.imag());
    dtkHashCombine(seed, c.real());
    return seed;
}

//
// dtkHash.h ends here
