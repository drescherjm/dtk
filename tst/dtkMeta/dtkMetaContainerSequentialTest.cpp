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

#include <dtkMeta/dtkMetaContainerSequentialHandler.h>

#include <QtCore>

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

void dtkMetaContainerSequentialTestCase::testConversion(void)
{
    QVariant var;

    QList<int> list;
    var = dtkMetaType::variantFromValue(&list);
    QVERIFY(dtkMetaType::canConvert<dtkMetaContainerSequential>(var.userType()));

    QVector<QString> vec;
    var = dtkMetaType::variantFromValue(&vec);
    QVERIFY(dtkMetaType::canConvert<dtkMetaContainerSequential>(var.userType()));

    QVarLengthArray<double> vla;
    var = dtkMetaType::variantFromValue(&vla);
    QVERIFY(dtkMetaType::canConvert<dtkMetaContainerSequential>(var.userType()));

    std::list<double> std_l;
    var = dtkMetaType::variantFromValue(&std_l);
    QVERIFY(dtkMetaType::canConvert<dtkMetaContainerSequential>(var.userType()));

    std::vector<double> std_v;
    var = dtkMetaType::variantFromValue(&std_v);
    QVERIFY(dtkMetaType::canConvert<dtkMetaContainerSequential>(var.userType()));
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
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, c_i.size());

    typedef QVector<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    qDebug() << qMetaTypeId<QVector<QString> *>(reinterpret_cast<QVector<QString> **>(0));

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, c_s.size());
}

void dtkMetaContainerSequentialTestCase::testQVarLengthArray(void)
{
    typedef QVarLengthArray<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, c_i.size());

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
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, (int)c_i.size());

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
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    testContainer<ArrayInt>(c_i, values_i, size);

    QCOMPARE(2 * size, (int)c_i.size());

    typedef std::vector<QString> ArrayString;
    ArrayString c_s;
    size = 4;
    QString values_s[4] = {"toto", "allo", "ici", "bebe"};

    testContainer<ArrayString>(c_s, values_s, size);

    QCOMPARE(2 * size, (int)c_s.size());
}

void dtkMetaContainerSequentialTestCase::testNew(void)
{
    typedef std::list<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int i = 0; i < size; ++i) {
        c_i.push_back(0);
    }

    dtkMetaContainerSequentialHandler *h = new dtkMetaContainerSequentialHandlerTemplate<ArrayInt>(&c_i);
    dtkMetaContainer mc(h);

    QVERIFY(mc.hasBiDirectionalIterator());
    QVERIFY(!mc.hasRandomAccessIterator());

    mc.reserve(12);
    mc.resize(11);

    for(int i = 0; i < size; ++i) {
        mc.setAt(i, values_i[i]);
    }
    int count = 0;
    for(int i : c_i) {
        QCOMPARE(i, values_i[count++]);
    }
    for(int i = 0; i < size; ++i) {
        QCOMPARE(mc.at<int>(i), values_i[i]);
    }

    //qDebug() << mc.at(5) << mc.at<int>(5) << mc[5] << mc.first() << (*(const dtkMetaContainer*)(&mc)).last();

    qDebug() << (mc[5] == mc[5]);

    dtkMetaContainer::const_iterator cit  = mc.cbegin();
    dtkMetaContainer::const_iterator cend = mc.cend();

    for(int i = 0; cit != cend; ++cit, ++i) {
        QCOMPARE((*cit).value<int>(), values_i[i]);
    }

    dtkMetaContainer::iterator it  = mc.begin();
    dtkMetaContainer::iterator end = mc.end();

    for(int i = 0; it != end; ++it, ++i) {
        QCOMPARE((*it).value<int>(), values_i[i]);
    }

    mc[10] += 5; //qDebug() << mc[10];

    *it = 121;
    *it /= 11;
    // qDebug() << (*it).value<int>() << (*copy).value<int>();

    QVector<QString> array;
    dtkMetaContainerSequentialHandler *h1 = new dtkMetaContainerSequentialHandlerTemplate<QVector<QString> >(&array);
    QVERIFY(h1->hasBiDirectionalIterator());
    QVERIFY(h1->hasRandomAccessIterator());
}

DTKTEST_MAIN_NOGUI(dtkMetaContainerSequentialTest, dtkMetaContainerSequentialTestCase)

// 
// dtkMetaContainerSequentialTest.cpp ends here
