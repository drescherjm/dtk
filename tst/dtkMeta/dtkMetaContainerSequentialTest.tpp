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

#include <dtkMeta/dtkMetaContainerSequential.h>

// ///////////////////////////////////////////////////////////////////

template <typename T> void testContainer(T& c, typename T::value_type *values, int& size)
{
    typedef typename T::value_type Type;

    for (int i = 0; i < size; ++i) {
        c.push_back(values[i]);
    }

    QVariant v_c = dtkMetaType::variantFromValue(&c);
    QVERIFY(dtkMetaType::canConvert<dtkMetaContainerSequential>(v_c.userType()));
    dtkMetaContainerSequential m_c = v_c.value<dtkMetaContainerSequential>();
    QVERIFY(!m_c.empty());
    QCOMPARE(m_c.size(), (int)std::distance(c.begin(), c.end()));

    typename T::const_iterator cit = c.cbegin();
    QCOMPARE(m_c.first().value<Type>(), *cit);
    for (int i = 0;  i < size; ++i, ++cit) {
        QCOMPARE(m_c.at<Type>(i), *cit);
        QCOMPARE(m_c.at(i).value<Type>(), *cit);
        QCOMPARE(m_c[i].value<Type>(), *cit);
    }
    QCOMPARE(m_c.last().value<Type>(), *(--cit));

    typename T::const_iterator c_cit = c.cbegin();
    dtkMetaContainerSequential::const_iterator m_c_cit = m_c.cbegin();
    dtkMetaContainerSequential::const_iterator m_c_cend = m_c.cend();
    for ( ; m_c_cit != m_c_cend; ++m_c_cit, ++c_cit) {
        QCOMPARE((*m_c_cit).value<Type>(), *c_cit);
    }
    QCOMPARE(m_c_cit, m_c_cend);

    typename T::iterator c_it = c.begin();
    dtkMetaContainerSequential::iterator m_c_it = m_c.begin();
    dtkMetaContainerSequential::iterator m_c_end = m_c.end();
    Type val;
    for (int i = 0; m_c_it != m_c_end; ++i, ++m_c_it, ++c_it) {
        val = *c_it + values[0];
        m_c.setAt(i, val);
        QCOMPARE((*m_c_it).value<Type>(), val);
        QCOMPARE((m_c_it).value<Type>(), val);
        QCOMPARE(*c_it, val);
        QVERIFY((*m_c_it == *c_it));
    }
    QCOMPARE(m_c_it, m_c_end);

    int count = size - 1;
    while (count >= 0 ) {
        m_c.removeAt(count);
        QCOMPARE(m_c.size(), count);
        m_c.insert(count, values[count]);
        QCOMPARE(m_c.at(count).value<Type>(), values[count]);
        m_c.removeAt(count);
        --count;
    }
    QCOMPARE((int)c.size(), 0);

    for (int i = 0; i < size; ++i) {
        m_c.append(values[i]);
        QCOMPARE(m_c.at(i).value<Type>(), values[i]);
    }
    QCOMPARE(m_c.size(), size);
    QCOMPARE((int)std::distance(c.begin(), c.end()), size);

    m_c.prepend(values[size-1]);
    QCOMPARE(m_c.first().value<Type>(), values[size-1]);

    m_c.clear();
    QVERIFY(m_c.empty());

    m_c.reserve(size);
    for (int i = 0; i < size; ++i) {
        m_c.append(values[i]);
    }
    count = size - 1;
    for (dtkMetaContainerSequential::item& item : m_c) {
        item += values[count]; --count;
    }
    const dtkMetaContainerSequential& const_m_c = m_c;

    count = size - 1;
    int pos = 0;
    for (const QVariant& var : const_m_c) {
        QCOMPARE(var.value<Type>(), values[pos] + values[count]);
        --count; ++pos;
    }

    m_c.resize(2 * size);
}

// 
// dtkMetaContainerSequentialTest.tpp ends here
