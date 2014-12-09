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

const int N = 1000000;
static double s = 0;

void dtkMetaContainerSequentialTestCase::testBasics(void)
{
    typedef std::list<int> ArrayInt;
    ArrayInt c_i;
    int size = 11;
    int values_i[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int i = 0; i < size; ++i) {
        c_i.push_back(0);
    }
    
    dtkMetaContainerSequentialHandler *h = new dtkMetaContainerSequentialHandlerTemplate<ArrayInt>(&c_i);
    dtkMetaContainerSequential mc(h);

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

    dtkMetaContainerSequential::const_iterator cit  = mc.cbegin();
    dtkMetaContainerSequential::const_iterator cend = mc.cend();
    for(int i = 0; cit != cend; ++cit, ++i) {
        QCOMPARE((*cit).value<int>(), values_i[i]);
    }

    dtkMetaContainerSequential::iterator it  = mc.begin();
    dtkMetaContainerSequential::iterator end = mc.end();
    for(int i = 0; it != end; ++it, ++i) {
        QCOMPARE((it).value<int>(), values_i[i]);
    }
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

void dtkMetaContainerSequentialTestCase::testBenchVec(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QBENCHMARK {
        s= 0;
        for (int i = 0; i != N; ++i)
            s += vec[i];
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaItemAt(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        for (int i = 0; i != N; ++i)
            s += mvec[i].value<double>();
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaVariantAt(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        for (int i = 0; i != N; ++i)
            s += mvec.at(i).value<double>();
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaConstIterators(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        dtkMetaContainerSequential::const_iterator it  = mvec.cbegin();
        dtkMetaContainerSequential::const_iterator end = mvec.cend();
        for(; it != end; ++it) {
            s += (*it).value<double>();
        }
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaIterators(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        dtkMetaContainerSequential::iterator it  = mvec.begin();
        dtkMetaContainerSequential::iterator end = mvec.end();
        for(; it != end; ++it) {
            s += (*it).value<double>();
        }
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaIteratorsDirect(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        dtkMetaContainerSequential::iterator it  = mvec.begin();
        dtkMetaContainerSequential::iterator end = mvec.end();
        for(; it != end; ++it) {
            s += (it).value<double>();
        }
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaOperatorConst(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    const dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        for (int i = 0; i != N; ++i)
            s += mvec[i].value<double>();
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaOperator(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        for (int i = 0; i != N; ++i)
            s += mvec[i].value<double>();
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaRangeLoopConst(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    const dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        for (const QVariant& var : mvec)
            s += var.value<double>();
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaRangeLoop(void)
{
    QVector<double> vec(N);
    for (int i = 0; i != N; ++i)
        vec[i] = i;

    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        s = 0;
        for (dtkMetaContainerSequential::item& it : mvec)
            s += it.value<double>();
    }
}

void dtkMetaContainerSequentialTestCase::testBenchVecSetAt(void)
{
    QVector<double> vec(N);
    QBENCHMARK {        
        for (int i = 0; i != N; ++i)
            vec[i] = i;
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaSetAt(void)
{
    QVector<double> vec(N);
    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            mvec.setAt(i, i);
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaSetAtIterator(void)
{
    QVector<double> vec(N);
    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        dtkMetaContainerSequential::iterator it  = mvec.begin();
        dtkMetaContainerSequential::iterator end = mvec.end();
        for(int i = 0; it != end; ++it, ++i) {
            *it = i;
        }
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaSetAtOperator(void)
{
    QVector<double> vec(N);
    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        for (int i = 0; i != N; ++i)
            mvec[i] = i;
    }
}

void dtkMetaContainerSequentialTestCase::testBenchMetaSetAtRange(void)
{
    QVector<double> vec(N);
    QVariant vc = dtkMetaType::variantFromValue(&vec);
    dtkMetaContainerSequential mvec = vc.value<dtkMetaContainerSequential>();
    QBENCHMARK {
        int i = -1;
        for (dtkMetaContainerSequential::item& it : mvec) {
            it = ++i;
        }
    }
}

DTKTEST_MAIN_NOGUI(dtkMetaContainerSequentialTest, dtkMetaContainerSequentialTestCase)

// 
// dtkMetaContainerSequentialTest.cpp ends here
