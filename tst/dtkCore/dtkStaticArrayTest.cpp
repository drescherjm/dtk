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

#include "dtkStaticArrayTest.h"

#include <dtkCore/dtkStaticArray.h>

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
//
// ///////////////////////////////////////////////////////////////////

dtkStaticArrayTestCase::dtkStaticArrayTestCase(void)
{
}

dtkStaticArrayTestCase::~dtkStaticArrayTestCase(void)
{

}

void dtkStaticArrayTestCase::initTestCase(void)
{

}

void dtkStaticArrayTestCase::init(void)
{

}

void dtkStaticArrayTestCase::cleanup(void)
{

}

void dtkStaticArrayTestCase::cleanupTestCase(void)
{

}

void dtkStaticArrayTestCase::testCreate(void)
{
    {
        dtkStaticArray<double, 0> array;

        QVERIFY(array.empty());
        QCOMPARE(array.size(), 0LL);
        QVERIFY(!array.data());
    }

    {
        dtkStaticArray<double, 101> array;

        QVERIFY(!array.empty());
        QCOMPARE(array.size(),  101LL);
        QCOMPARE(array.count(), 101LL);
        QVERIFY(array.data());
    }

    {
        std::initializer_list<double> l = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        QVERIFY(!array.empty());
        QCOMPARE(array.size(), (qlonglong)l.size());

        int i = 0;
        double *data = array.data();
        for(auto val : l) {
            QCOMPARE(data[i++], val);
        }
    }

    {
        const dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> copy(array);

        QVERIFY(!copy.empty());
        QCOMPARE(copy.size(), array.size());

        const double *a_data = array.data();
        double *c_data = copy.data();
        for(int i = 0; i < 11; ++i) {
            QCOMPARE(c_data[i], a_data[i]);
        }
    }
}

void dtkStaticArrayTestCase::testAlignment(void)
{
    {
        typedef dtkStaticArray<double, 11>                           alignedArray;
        typedef dtkStaticArray<double, 11, 2 * sizeof(double)> customAlignedArray;

        QCOMPARE(std::alignment_of<alignedArray>::value, sizeof(double));
        QCOMPARE(std::alignment_of<customAlignedArray>::value, 2 * sizeof(double));
    }
}

void dtkStaticArrayTestCase::testFill(void)
{
    {
        dtkStaticArray<double, 101> array;

        double pi = 3.14159;
        array.fill(pi);
        const double *data = array.constData();
        for(int i = 0; i < 101; ++i) {
            QCOMPARE(data[i], pi);
        }
    }
}

void dtkStaticArrayTestCase::testAssignement(void)
{
    {
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> copy;

        copy = array;
        QCOMPARE(copy.size(), array.size());

        double *a_data = array.data();
        double *c_data = copy.data();
        for(int i = 0; i < 11; ++i) {
            QCOMPARE(c_data[i], a_data[i]);
        }
    }

}

void dtkStaticArrayTestCase::testSetAt(void)
{
    {
        dtkStaticArray<double, 101> array;
        double pi = 3.14159;

        for(int i = 0; i < 101; ++i) {
            array.setAt(i, pi * i);
        }

        double *data = array.data();
        for(int i = 0; i < 101; ++i) {
            QCOMPARE(data[i], pi * i);
        }
    }

    {
        dtkStaticArray<double, 101> array;
        double pi = 3.14159;

        for(int i = 0; i < 101; ++i) {
            array[i] = pi * i;
        }

        double *data = array.data();
        for(int i = 0; i < 101; ++i) {
            QCOMPARE(data[i], pi * i);
        }
    }
}

void dtkStaticArrayTestCase::testAt(void)
{
    {
        std::initializer_list<double> l = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        int i = 0;
        for(auto val : l) {
            QCOMPARE(array.at(i++), val);
        }
    }

    {
        std::initializer_list<double> l = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        int i = 0;
        for(auto val : l) {
            QCOMPARE(array[i++], val);
        }

        auto it = l.begin();
        QCOMPARE(array.first(), *it);
        QCOMPARE(array.front(), *it);
        it += l.size() - 1;
        QCOMPARE(array.last(), *it);
        QCOMPARE(array.back(), *it);
    }

    {
        std::initializer_list<double> l = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        const dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        int i = 0;
        for(auto val : l) {
            QCOMPARE(array[i++], val);
        }

        auto it = l.begin();
        QCOMPARE(array.first(), *it);
        QCOMPARE(array.front(), *it);
        it += l.size() - 1;
        QCOMPARE(array.last(), *it);
        QCOMPARE(array.back(), *it);
    }
}

void dtkStaticArrayTestCase::testIterate(void)
{
    {
        std::initializer_list<double> l = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        auto it = l.begin();
        for (auto val : array) {
            QCOMPARE(val, *it);
            ++it;
        }
    }

    {
        std::initializer_list<double> l = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        auto it = l.begin();
        for (const double& val : array) {
            QCOMPARE(val, *it);
            ++it;
        }
    }

    {
        std::initializer_list<double> l = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        const dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        auto it = l.begin();
        for (auto val : array) {
            QCOMPARE(val, *it);
            ++it;
        }
    }

    {
        std::initializer_list<double> l = { 1.1, 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1 };
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        auto it = l.begin();
        for (auto a_it = array.rbegin(); a_it != array.rend(); ++a_it, ++it) {
            QCOMPARE(*a_it, *it);
        }
    }

    {
        std::initializer_list<double> l = { 1.1, 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1 };
        dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        auto it = l.begin();
        for (auto a_it = array.crbegin(); a_it != array.crend(); ++a_it, ++it) {
            QCOMPARE(*a_it, *it);
        }
    }

    {
        std::initializer_list<double> l = { 1.1, 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1 };
        const dtkStaticArray<double, 11> array = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        auto it = l.begin();
        for (auto a_it = array.rbegin(); a_it != array.rend(); ++a_it, ++it) {
            QCOMPARE(*a_it, *it);
        }
    }
}

void dtkStaticArrayTestCase::testComparison(void)
{
    {
        dtkStaticArray<double, 11> lhs = { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
        dtkStaticArray<double, 11> rhs(lhs);

        QVERIFY(lhs == rhs);

        rhs = { 0.11, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };

        QVERIFY(lhs < rhs);
    }    
}


DTKTEST_MAIN_NOGUI(dtkStaticArrayTest, dtkStaticArrayTestCase)


//
// dtkStaticArrayTest.cpp ends here
