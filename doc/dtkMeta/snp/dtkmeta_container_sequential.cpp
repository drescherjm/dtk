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

//! [0]
QVector<int> int_vector;
int size = 11;

for (int i = 0; i < size; ++i)
{
    int_vector << i;
}

// Sets the variant from the address of the vector
QVariant variant = QVariant::fromValue(&int_vector);

// Gets the meta container without copying the vector
const dtkMetaContainerSequential const_meta_vector = variant.value<dtkMetaContainerSequential>();

qDebug() << const_meta_vector.empty() << const_meta_vector.size();
qDebug() << const_meta_vector.first() << const_meta_vector.last();

// Classical loop
for (int i = 0;  i < size; ++i)
{
    qDebug() << i << int_vector.at(i) << const_meta_vector.at(i).value<int>() << const_meta_vector[i].value<int>();
}

// Const iterators loop
dtkMetaContainerSequential::const_iterator cit = const_meta_vector.cbegin();
dtkMetaContainerSequential::const_iterator cend = const_meta_vector.cend();

for ( ; cit != cend; ++cit)
{
    qDebug() << *cit;
}

// C++11 range loop
for (const QVariant& v : const_meta_vector)
{
    qDebug() << v;
}

//! [0]

//! [1]
dtkMetaContainerSequential meta_vector = variant.value<dtkMetaContainerSequential>();

for (int i = 0; i < size; ++i)
{
    meta_vector.setAt(i, meta_vector.at(i).value<int>() + i);
}

for (int i = 0; i < size; ++i)
{
    meta_vector.removeAt(i);
}

qDebug() << (int_vector.size() == 0);

for (int i = 0; i < size; ++i)
{
    meta_vector.append(i);
}

qDebug() << (int_vector.size() == size);

meta_vector.prepend(-1);
qDebug() << (int_vector.first() == (int)(-1));
meta_vector.removeAt(0);
//! [1]

//! [2]
dtkMetaContainerSequential::iterator it = meta_vector.begin();
dtkMetaContainerSequential::iterator end = meta_vector.end();

for (; it != end; ++it)
{
    *it += 121;
    *it *= 2;
}

int count = 0;

for (dtkMetaContainerSequential::item& item : m_c)
{
    item /= 2;
    item -= 121;
    qDebug() << (item == count);
    ++count;
}

for (int i = 0; i < size; ++i)
{
    meta_vector[i] += i;
}

//! [2]

//! [3]
QVector<int> int_vector;
int size = 11;

for (int i = 0; i < size; ++i)
{
    int_vector << i;
}

QVariant variant = QVariant::fromValue(&int_vector);
const dtkMetaContainerSequential const_meta_vector = variant.value<dtkMetaContainerSequential>();
// Classical loop
for (int i = 0;  i < size; ++i)
{
    qDebug() << i << const_meta_vector[i];
}

// Const iterators loop
dtkMetaContainerSequential::const_iterator cit = const_meta_vector.cbegin();
dtkMetaContainerSequential::const_iterator cend = const_meta_vector.cend();

for ( ; cit != cend; ++cit)
{
    qDebug() << *cit;
}

// C++11 range loop
for (const QVariant& v : const_meta_vector)
{
    qDebug() << v;
}

//! [3]

//! [4]
QVector<int> int_vector;
int size = 11;

for (int i = 0; i < size; ++i)
{
    int_vector << i;
}

QVariant variant = QVariant::fromValue(&int_vector);
dtkMetaContainerSequential meta_vector = variant.value<dtkMetaContainerSequential>();
dtkMetaContainerSequential::iterator it = meta_vector.begin();
dtkMetaContainerSequential::iterator end = meta_vector.end();

for (; it != end; ++it)
{
    *it += 121;
    *it *= 2;
}

int count = 0;

for (dtkMetaContainerSequential::item& item : m_c)
{
    item /= 2;
    item -= 121;
    qDebug() << (item == count);
    ++count;
}

for (int i = 0; i < size; ++i)
{
    meta_vector[i] += i;
}

//! [4]

//! [5]
QVector<int> int_vector;
int size = 11;

for (int i = 0; i < size; ++i)
{
    int_vector << i;
}

QVariant variant = QVariant::fromValue(&int_vector);
dtkMetaContainerSequential meta_vector = variant.value<dtkMetaContainerSequential>();

meta_vector.first() += 1;
meta_vector.last()  -= 1;

for (int i = 0; i < size; ++i)
{
    meta_vector[i] *= 3;
    meta_vector[i] /= 4;
}

dtkMetaContainerSequential::iterator it = meta_vector.begin();
*it += 121;
*it /= 5;
//! [5]

//
// dtkmeta_container_sequential.cpp ends here
