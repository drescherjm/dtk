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

#include <dtkMeta/dtkMetaContainerSequential.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define TEST_SEQUENTIAL_INT(CONTAINER)                                  \
    {                                                                   \
        int size = 11;                                                  \
        CONTAINER<int> c;                                               \
        for (int i = 0; i < size; ++i) {                                \
            c.push_back(i);                                             \
        }                                                               \
                                                                        \
        QVariant v_c = QVariant::fromValue(&c);                         \
        dtkMetaContainerSequential m_c = v_c.value<dtkMetaContainerSequential>(); \
        QVERIFY(!m_c.empty());                                          \
        QCOMPARE(m_c.size(), (int)std::distance(c.begin(), c.end())); \
                                                                        \
        CONTAINER<int>::const_iterator cit = c.cbegin();                \
        QCOMPARE(m_c.first().value<int>(), *cit);                       \
        for (int i = 0;  i < size; ++i, ++cit) {                        \
            QCOMPARE(m_c.at(i).value<int>(), *cit);                     \
            QCOMPARE(m_c[i].value<int>(), *cit);                        \
        }                                                               \
        QCOMPARE(m_c.last().value<int>(), *(--cit));                    \
                                                                        \
        CONTAINER<int>::const_iterator c_cit = c.cbegin();              \
        dtkMetaContainerSequential::const_iterator m_c_cit = m_c.cbegin(); \
        dtkMetaContainerSequential::const_iterator m_c_cend = m_c.cend(); \
        for ( ; m_c_cit != m_c_cend; ++m_c_cit, ++c_cit) {              \
            QCOMPARE((*m_c_cit).value<int>(), *c_cit);                  \
        }                                                               \
        QCOMPARE(m_c_cit, m_c_cend);                                    \
                                                                        \
        CONTAINER<int>::iterator c_it = c.begin();                      \
        dtkMetaContainerSequential::iterator m_c_it = m_c.begin();      \
        dtkMetaContainerSequential::iterator m_c_end = m_c.end();       \
        int val;                                                        \
        for (int i = 0; m_c_it != m_c_end; ++i, ++m_c_it, ++c_it) {     \
            val = *c_it * 2;                                            \
            m_c.setAt(i, val);                                          \
            QCOMPARE((*m_c_it).value<int>(), val);                      \
            QCOMPARE(*c_it, val);                                       \
        }                                                               \
        QCOMPARE(m_c_it, m_c_end);                                      \
                                                                        \
        int count = size - 1;                                           \
        while (count >= 0 ) {                                           \
            m_c.removeAt(count);                                        \
            QCOMPARE(m_c.size(), count);                                \
            m_c.insert(count, count);                                   \
            QCOMPARE(m_c.at(count).value<int>(), count);                \
            m_c.removeAt(count);                                        \
            --count;                                                    \
        }                                                               \
        QCOMPARE((int)c.size(), 0);                                     \
                                                                        \
        m_c.reserve(size);                                              \
        for (int i = 0; i < size; ++i) {                                \
            m_c.append(i);                                              \
            QCOMPARE(m_c.at(i).value<int>(), i);                        \
        }                                                               \
        QCOMPARE(m_c.size(), size);                                     \
        QCOMPARE((int)std::distance(c.begin(), c.end()), size);         \
                                                                        \
        m_c.prepend(121);                                               \
        QCOMPARE(m_c.first().value<int>(), 121);                        \
                                                                        \
        m_c.clear();                                                    \
        QVERIFY(m_c.empty());                                           \
                                                                        \
        m_c.reserve(size);                                              \
        for (int i = 0; i < size; ++i) {                                \
            m_c.append(i);                                              \
        }                                                               \
        for (dtkMetaContainerSequential::item &item : m_c) {            \
            item += 2;                                                  \
        }                                                               \
        const dtkMetaContainerSequential& const_m_c = m_c;              \
        val = 0;                                                        \
        for (const QVariant& var : const_m_c) {                         \
            QCOMPARE(var.value<int>(), val + 2);                        \
            ++val;                                                      \
        }                                                               \
                                                                        \
        m_c.resize(2 * size);                                           \
        qDebug() << c.size();                                           \
    }

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
    TEST_SEQUENTIAL_INT(QList);
}

void dtkMetaContainerSequentialTestCase::testQVector(void)
{
    TEST_SEQUENTIAL_INT(QVector);
}

void dtkMetaContainerSequentialTestCase::testQVarLengthArray(void)
{
    TEST_SEQUENTIAL_INT(QVarLengthArray);
}

void dtkMetaContainerSequentialTestCase::testStdList(void)
{
    TEST_SEQUENTIAL_INT(std::list);
}

void dtkMetaContainerSequentialTestCase::testStdVector(void)
{
    TEST_SEQUENTIAL_INT(std::vector);
}

DTKTEST_MAIN_NOGUI(dtkMetaContainerSequentialTest, dtkMetaContainerSequentialTestCase)

// 
// dtkMetaContainerSequentialTest.cpp ends here
