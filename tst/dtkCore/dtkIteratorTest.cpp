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
    qlonglong m_id;
    dtkArray<qlonglong> m_elts;

public:
    Dummy(qlonglong id, qlonglong e0, qlonglong e1, qlonglong e2, qlonglong e3) : m_id(id) {
        m_elts.append(e0, e1, e2, e3);
    }

public:
    bool operator == (const Dummy& o) const {
        return (m_id == o.m_id && m_elts == o.m_elts);
    }

public:
    qlonglong id() const {
        return m_id;
    }
    dtkArray<qlonglong> elts() {
        return m_elts;
    }
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
    dummyIterator& operator = (const dummyIterator& o) {
        it = o.it;
        return *this;
    }

public:
    bool operator == (const dummyIterator& o) const {
        return it == o.it;
    }
    bool operator != (const dummyIterator& o) const {
        return it != o.it;
    }
    bool operator <  (const dummyIterator& o) const {
        return it <  o.it;
    }
    bool operator <= (const dummyIterator& o) const {
        return it <= o.it;
    }
    bool operator >  (const dummyIterator& o) const {
        return it >  o.it;
    }
    bool operator >= (const dummyIterator& o) const {
        return it >= o.it;
    }

public:
    Dummy *&operator *  (void) const {
        return *it;
    }
    Dummy * *operator -> (void) const {
        return it.i;
    }
    Dummy *&operator [] (qlonglong j) const {
        return it[j];
    }

public:
    dummyIterator& operator ++ (void) {
        ++it;
        return *this;
    }
    dummyIterator  operator ++ (int)  {
        dummyIterator o(it);
        ++it;
        return o;
    }
    dummyIterator& operator -- (void) {
        --it;
        return *this;
    }
    dummyIterator  operator -- (int)  {
        dummyIterator o(it);
        --it;
        return o;
    }
    dummyIterator& operator += (qlonglong j) {
        it += j;
        return *this;
    }
    dummyIterator& operator -= (qlonglong j) {
        it -= j;
        return *this;
    }
    dummyIterator  operator +  (qlonglong j) const {
        return dummyIterator(it + j);
    }
    dummyIterator  operator -  (qlonglong j) const {
        return dummyIterator(it - j);
    }

public:
    operator Dummy * *() const {
        return it.i;
    }
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
    dtkDummyIterator begin() {
        return dtkDummyIterator(new dummyIterator(dummies.begin()));
    }
    dtkDummyIterator   end() {
        return dtkDummyIterator(new dummyIterator(dummies.end()));
    }
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

    QVERIFY(d->begin() == d->dummies.begin());
    QVERIFY(d->end() == d->dummies.end());
}

void dtkIteratorTestCase::testCopyCreate(void)
{
    dtkDummyIterator it = d->begin();
    dtkDummyIterator it_copy(it);

    QCOMPARE(*it, *it_copy);
}

void dtkIteratorTestCase::testCopy(void)
{
    dtkDummyIterator it = d->begin();
    dtkDummyIterator it_copy = it;

    QCOMPARE(*it, *it_copy);
}

void dtkIteratorTestCase::testDereference(void)
{
    dtkDummyIterator it = d->begin();

    dtkArray<qlonglong> ref_elts;
    ref_elts << 0 << 1 << 2 << 3;

    QCOMPARE((*it)->id(), (qlonglong)(0));
    QCOMPARE((*it)->elts(), ref_elts);
}

void dtkIteratorTestCase::testBracket(void)
{
    dtkDummyIterator it = d->begin();

    for (qlonglong i = 0; i < 4; ++i)
        QCOMPARE((it[i])->id(), i);
}

void dtkIteratorTestCase::testForward(void)
{
    dtkDummyIterator it = d->begin();

    for (qlonglong i = 0; i < 4; ++i) {
        QCOMPARE((*it)->id(), i);
        it++;
    }
}

void dtkIteratorTestCase::testPreForward(void)
{
    dtkDummyIterator it = d->begin();

    for (qlonglong i = 0; i < 4; ++i, ++it) {
        QCOMPARE((*it)->id(), i);
    }
}

void dtkIteratorTestCase::testBackward(void)
{
    dtkDummyIterator it = --d->end();

    for (qlonglong i = 3; i >= 0; --i, --it) {
        QCOMPARE((*it)->id(), i);
    }
}

void dtkIteratorTestCase::testPreBackward(void)
{
    dtkDummyIterator it = --d->end();

    for (qlonglong i = 3; i >= 0; --i, --it) {
        QCOMPARE((*it)->id(), i);
    }
}

void dtkIteratorTestCase::testAffectAdd(void)
{
    dtkDummyIterator it = d->begin();

    it += 3;
    QCOMPARE((*it)->id(), (qlonglong)(3));
}

void dtkIteratorTestCase::testAffectSubstract(void)
{
    dtkDummyIterator it = d->end();

    it -= 2;
    QCOMPARE((*it)->id(), (qlonglong)(2));
}

void dtkIteratorTestCase::testAdd(void)
{
    dtkDummyIterator it = d->begin();

    dtkDummyIterator o = (it + (qlonglong)(3));
    QCOMPARE((*o)->id(), (qlonglong)(3));
}

void dtkIteratorTestCase::testSubstract(void)
{
    dtkDummyIterator it = d->end();

    dtkDummyIterator o = (it - (qlonglong)(3));
    QCOMPARE((*o)->id(), (qlonglong)(1));
}

void dtkIteratorTestCase::testEquality(void)
{
    dtkDummyIterator it_0 = d->begin();
    dtkDummyIterator it_1 = d->end();

    it_0 += 2;
    it_1 -= 2;

    QVERIFY(it_0 == it_1);
}

void dtkIteratorTestCase::testInequality(void)
{
    dtkDummyIterator it_0 = d->begin();
    dtkDummyIterator it_1 = d->end();

    QVERIFY(it_0 != it_1);
}

void dtkIteratorTestCase::testInferior(void)
{
    dtkDummyIterator it_0 = d->begin();
    dtkDummyIterator it_1 = d->end();

    QVERIFY(it_0 < it_1);
}

void dtkIteratorTestCase::testInferiorEqual(void)
{
    dtkDummyIterator it_0 = d->begin();
    dtkDummyIterator it_1 = d->end();

    it_0 += 1;
    it_1 -= 1;
    QVERIFY(it_0 <= it_1);

    it_0 += 1;
    it_1 -= 1;
    QVERIFY(it_0 <= it_1);

    it_0 += 1;
    it_1 -= 1;
    QVERIFY(!(it_0 <= it_1));
}

void dtkIteratorTestCase::testSuperior(void)
{
    dtkDummyIterator it_0 = d->begin();
    dtkDummyIterator it_1 = d->end();
    it_0 += 3;
    it_1 -= 3;

    QVERIFY(it_0 > it_1);
}

void dtkIteratorTestCase::testSuperiorEqual(void)
{
    dtkDummyIterator it_0 = d->begin();
    dtkDummyIterator it_1 = d->end();

    it_0 += 1;
    it_1 -= 1;
    QVERIFY(it_1 >= it_0);

    it_0 += 1;
    it_1 -= 1;
    QVERIFY(it_1 >= it_0);

    it_0 += 1;
    it_1 -= 1;
    QVERIFY(!(it_1 >= it_0));
}

void dtkIteratorTestCase::cleanup(void)
{

}

void dtkIteratorTestCase::cleanupTestCase(void)
{
    for (Dummy *dum : d->dummies)
        delete dum;
}

DTKTEST_MAIN_NOGUI(dtkIteratorTest, dtkIteratorTestCase)

//
// dtkIteratorTest.cpp ends here
