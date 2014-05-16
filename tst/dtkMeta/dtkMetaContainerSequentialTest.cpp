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

#include "dtkMetaContainerSequentialTest.h"
#include "dtkMetaContainerSequentialTest.tpp"

#include <QtCore>
#include <QtGui>

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkMetaContainerSequentialTestCase::dtkMetaContainerSequentialTestCase(void)
{
}

dtkMetaContainerSequentialTestCase::~dtkMetaContainerSequentialTestCase(void)
{

}

void dtkMetaContainerSequentialTestCase::initTestCase(void)
{

}

void dtkMetaContainerSequentialTestCase::init(void)
{

}

void dtkMetaContainerSequentialTestCase::cleanup(void)
{

}

void dtkMetaContainerSequentialTestCase::cleanupTestCase(void)
{

}

void dtkMetaContainerSequentialTestCase::testQList(void)
{
    typedef QList<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(size, c_i.size());

    typedef QList<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(size, c_s.size());
}

void dtkMetaContainerSequentialTestCase::testQVector(void)
{
    typedef QVector<int> ArrayInt;
    ArrayInt c;
    int size = 11;
    int values[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c, values, size);

    QCOMPARE(2 * size, c.size());

    typedef QVector<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, c_s.size());
}

void dtkMetaContainerSequentialTestCase::testQVarLengthArray(void)
{
    typedef QVarLengthArray<int> ArrayInt;
    ArrayInt c;
    int size = 11;
    int values[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c, values, size);

    QCOMPARE(2 * size, c.size());

    typedef QVarLengthArray<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, c_s.size());
}

void dtkMetaContainerSequentialTestCase::testStdList(void)
{
    typedef std::list<int> ArrayInt;
    ArrayInt c;
    int size = 11;
    int values[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c, values, size);

    QCOMPARE(2 * size, (int)c.size());

    typedef std::list<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, (int)c_s.size());
}

void dtkMetaContainerSequentialTestCase::testStdVector(void)
{
    typedef std::vector<int> ArrayInt;
    ArrayInt c;
    int size = 11;
    int values[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c, values, size);

    QCOMPARE(2 * size, (int)c.size());

    typedef std::vector<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, (int)c_s.size());
}

DTKTEST_MAIN_NOGUI(dtkMetaContainerSequentialTest, dtkMetaContainerSequentialTestCase)

// 
// dtkMetaContainerSequentialTest.cpp ends here
