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

#include "dtkIteratorTest.h"

#include <dtkCore/dtkIterator.h>
#include <dtkCore/dtkArray.h>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// Dummy class
// /////////////////////////////////////////////////////////////////

class Dummy
{
    int m_id;
    dtkArray<int> m_elts;

public:
    Dummy(int id, int e0, int e1, int e2, int e3) : m_id(id) { m_elts.append(e0, e1, e2, e3); }

public:
    bool operator == (const Dummy& o) const { return (m_id == o.m_id && m_elts == o.m_elts); }

public:
    int id() const { return m_id; }
    dtkArray<int> elts() { return m_elts; }
};

// ///////////////////////////////////////////////////////////////////
// dummyIterator
// ///////////////////////////////////////////////////////////////////

class dummyIterator : public dtkIteratorBase< Dummy *, dummyIterator >
{
    typedef dtkArray<Dummy *>::iterator iterator;
    iterator it;

public:
    dummyIterator(const iterator ite) : it(ite) {}
    dummyIterator(const dummyIterator& o) : it(o.it) {}

public:
    dummyIterator& operator = (const dummyIterator& o) { it = o.it; return *this; }

public:
    bool operator == (const dummyIterator& o) const { return it == o.it; }
    bool operator != (const dummyIterator& o) const { return it != o.it; }
    bool operator <  (const dummyIterator& o) const { return it <  o.it; }
    bool operator <= (const dummyIterator& o) const { return it <= o.it; }
    bool operator >  (const dummyIterator& o) const { return it >  o.it; }
    bool operator >= (const dummyIterator& o) const { return it >= o.it; }

public:
    Dummy*& operator *  (void) const { return *it; }
    Dummy* *operator -> (void) const { return it.i; }
    Dummy*& operator [] (qlonglong j) const { return it[j]; }

public:
    dummyIterator& operator ++ (void) { ++it; return *this; }
    dummyIterator  operator ++ (int)  { dummyIterator o(it); ++it; return o; }
    dummyIterator& operator -- (void) { --it; return *this; }
    dummyIterator  operator -- (int)  { dummyIterator o(it); --it; return o; }
    dummyIterator& operator += (qlonglong j) { it += j; return *this; }
    dummyIterator& operator -= (qlonglong j) { it -= j; return *this; }
    dummyIterator  operator +  (qlonglong j) const { return dummyIterator(it + j); }
    dummyIterator  operator -  (qlonglong j) const { return dummyIterator(it - j); }

public:
    operator Dummy* * () const { return it.i; }
};

typedef dtkIterator<Dummy *> dtkDummyIterator;

// ///////////////////////////////////////////////////////////////////
// dtkIteratorTestCasePrivate
// ///////////////////////////////////////////////////////////////////

class dtkIteratorTestCasePrivate
{
public:
    dtkArray<Dummy *> dummies;

public:
    dtkDummyIterator begin() { return dtkDummyIterator(new dummyIterator(dummies.begin())); }
    dtkDummyIterator   end() { return dtkDummyIterator(new dummyIterator(dummies.end())); }
};

// ///////////////////////////////////////////////////////////////////
// dtkIteratorTestCase
// ///////////////////////////////////////////////////////////////////

dtkIteratorTestCase::dtkIteratorTestCase(void) : d(new dtkIteratorTestCasePrivate)
{
}

dtkIteratorTestCase::~dtkIteratorTestCase(void)
{
    delete d;
}

void dtkIteratorTestCase::initTestCase(void)
{
    Dummy *d0 = new Dummy(0, 0, 1, 2, 3);
    Dummy *d1 = new Dummy(1, 1, 2, 3, 4);
    Dummy *d2 = new Dummy(2, 2, 3, 4, 5);
    Dummy *d3 = new Dummy(3, 3, 4, 5, 6);
    
    d->dummies.append(d0, d1, d2, d3);
}

void dtkIteratorTestCase::init(void)
{

}

void dtkIteratorTestCase::testCreate(void)
{
    dtkArray<Dummy *>::iterator ref_it = d->dummies.begin();

    dtkDummyIterator it = d->begin();
    dtkDummyIterator end = d->end();
}

void dtkIteratorTestCase::cleanup(void)
{

}

void dtkIteratorTestCase::cleanupTestCase(void)
{
    for(Dummy *dum : d->dummies)
        delete dum;
}

DTKTEST_MAIN_NOGUI(dtkIteratorTest, dtkIteratorTestCase)

// 
// dtkIteratorTest.cpp ends here
