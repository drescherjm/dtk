/* dtkArrayTest.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Jul 23 15:00:18 2013 (+0200)
  */

/* Credits:
 *  
 * See EOF.
 */

#include "dtkArrayTest.h"

#include <dtkMath/dtkArray.h>

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// Helper classes
// /////////////////////////////////////////////////////////////////

// This must match the default for PreallocSize.
static const qlonglong ExpectedMinCapacity = 8;

// Exception type that is thrown by ComplexValue.
class ComplexValueException
{
public:
    ComplexValueException(int value, bool inCtor)
        : m_value(value), m_inCtor(inCtor) {}

    int value() const { return m_value; }
    bool inConstructor() const { return m_inCtor; }

private:
    int m_value;
    bool m_inCtor;
};

// Complex type that helps the tests determine if QArray is calling
// constructors, destructors, and copy constructors in the right places.
class ComplexValue
{
public:
    enum Mode
    {
        Default,
        Init,
        Copy,
        CopiedAgain,
        Assign,
        ThrowInCtor,
        ThrowOnCopy
    };

    static int destroyCount;

    ComplexValue() : m_value(-1), m_mode(Default) {}
    ComplexValue(int value) : m_value(value), m_mode(Init) {}
#ifndef QT_NO_EXCEPTIONS
    ComplexValue(int value, Mode mode) : m_value(value), m_mode(mode)
    {
        if (mode == ThrowInCtor)
            throw new ComplexValueException(value, true);
    }
#endif
    ComplexValue(const ComplexValue& other)
        : m_value(other.m_value)
    {
        if (other.m_mode == Copy || other.m_mode == CopiedAgain)
            m_mode = CopiedAgain;
#ifndef QT_NO_EXCEPTIONS
        else if (other.m_mode == ThrowOnCopy)
            throw new ComplexValueException(other.m_value, false);
#endif
        else
            m_mode = Copy;
    }
    ~ComplexValue() { ++destroyCount; }

    ComplexValue& operator=(const ComplexValue& other)
    {
#ifndef QT_NO_EXCEPTIONS
        if (other.m_mode == ThrowOnCopy)
            throw new ComplexValueException(other.m_value, false);
#endif
        m_value = other.m_value;
        m_mode = Assign;
        return *this;
    }

    int value() const { return m_value; }
    Mode mode() const { return m_mode; }

    bool operator==(const ComplexValue& other) const
        { return m_value == other.m_value; }
    bool operator==(int other) const
        { return m_value == other; }
    bool operator!=(const ComplexValue& other) const
        { return m_value != other.m_value; }
    bool operator!=(int other) const
        { return m_value != other; }

private:
    int m_value;
    Mode m_mode;
};

int ComplexValue::destroyCount = 0;

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkArrayTestCase::dtkArrayTestCase(void)
{
}

dtkArrayTestCase::~dtkArrayTestCase(void)
{

}

void dtkArrayTestCase::initTestCase(void)
{

}

void dtkArrayTestCase::init(void)
{

}

void dtkArrayTestCase::cleanup(void)
{

}

void dtkArrayTestCase::cleanupTestCase(void)
{

}

void dtkArrayTestCase::testCreate(void)
{
    dtkArray<double> array;

    // Check the basic properties.
    QVERIFY(array.isEmpty());
    QCOMPARE(array.count(), 0LL);
    QCOMPARE(array.size(), 0LL);
    QCOMPARE(array.capacity(), ExpectedMinCapacity);
    QVERIFY(array.constRawData() != 0);
    QVERIFY(array.rawData() == array.constRawData());
    QVERIFY(((const dtkArray<double> *)&array)->rawData() == array.constRawData());

    // The current constRawData() pointer should be pointing into
    // the middle of "array" at the m_prealloc structure.
    const double *d = array.constRawData();
    QVERIFY(d >= (const double *)&array);
    QVERIFY(d < (const double *)((&array) + 1));

    // Add one element and check the basic properties again.
    array.append(1.0);
    QVERIFY(!array.isEmpty());
    QCOMPARE(array.count(), 1LL);
    QCOMPARE(array.size(), 1LL);
    QCOMPARE(array.capacity(), ExpectedMinCapacity);
    QVERIFY(array.constRawData() != 0);
    QVERIFY(array.rawData() == array.constRawData());
    QVERIFY(((const dtkArray<double> *)&array)->rawData() == array.constRawData());

    // Create another array that is filled with an initial value.
    dtkArray<QVector3D> array2(100, QVector3D(1.0f, 2.0f, 3.0f));
    QVERIFY(!array2.isEmpty());
    QCOMPARE(array2.count(), 100LL);
    QCOMPARE(array2.size(), 100LL);
    QVERIFY(array2.capacity() >= 100LL);
    QVERIFY(array2.constRawData() != 0LL);
    QVERIFY(array2.rawData() == array2.constRawData());
    QVERIFY(((const dtkArray<QVector3D> *)&array2)->rawData() == array2.constRawData());
    for (int index = 0; index < 100; ++index)
        QVERIFY(array2.at(index) == QVector3D(1.0f, 2.0f, 3.0f));

    // Create a filled array that is within the prealloc area.
    dtkArray<double> array3(ExpectedMinCapacity, 42.5f);
    QVERIFY(!array3.isEmpty());
    QCOMPARE(array3.count(), ExpectedMinCapacity);
    QCOMPARE(array3.size(), ExpectedMinCapacity);
    QVERIFY(array3.capacity() == ExpectedMinCapacity);
    QVERIFY(array3.constRawData() != 0);
    QVERIFY(array3.rawData() == array3.constRawData());
    for (int index = 0; index < ExpectedMinCapacity; ++index)
        QVERIFY(array3.at(index) == 42.5f);

    // Create an array of strings.
    dtkArray<QString> array4;
    QCOMPARE(array4.size(), 0LL);
    array4.append(QLatin1String("foo"));
    array4.append(QLatin1String("bar"));
    array4.append(array4[0]);
    QCOMPARE(array4[0], QLatin1String("foo"));
    QCOMPARE(array4[1], QLatin1String("bar"));
    QCOMPARE(array4[2], QLatin1String("foo"));

    // Create an array of complex values and check that the
    // copy constructors were called correctly.  Also check that
    // the destructors are called when the array is destroyed.
    ComplexValue::destroyCount = 0;
    {
        dtkArray<ComplexValue> array5;
        array5.append(ComplexValue(1));
        array5.append(ComplexValue(2));
        array5.append(ComplexValue(3));
        QCOMPARE(ComplexValue::destroyCount, 3); // Destruction of temporaries.
        QCOMPARE(array5.size(), 3LL);
        QVERIFY(array5[0].value() == 1);
        QVERIFY(array5[0].mode()  == ComplexValue::Copy);
        QVERIFY(array5[1].value() == 2);
        QVERIFY(array5[1].mode()  == ComplexValue::Copy);
        QVERIFY(array5[2].value() == 3);
        QVERIFY(array5[2].mode()  == ComplexValue::Copy);
    }
    QCOMPARE(ComplexValue::destroyCount, 6);
}

// void dtkArrayTestCase::testAppend(void)
// {
//     dtkArray<double> array;
//     int index;

//     // Appending up to the minimum capacity should not cause a realloc.
//     const double *d = array.constRawData();
//     for (index = 0; index < ExpectedMinCapacity; ++index) {
//         array.append(double(index));
//         QVERIFY(array.constRawData() == d);
//     }

//     // Check that the array contains the values we expected.
//     QCOMPARE(array.count(), ExpectedMinCapacity);
//     QCOMPARE(array.capacity(), ExpectedMinCapacity);
//     for (index = 0; index < ExpectedMinCapacity; ++index) {
//         QCOMPARE(array[index], double(index));
//     }

//     // Append 1 more item and check for realloc.
//     array += double(1000.0);
//     QCOMPARE(array.count(), ExpectedMinCapacity + 1);
//     QVERIFY(array.capacity() > ExpectedMinCapacity);
//     QVERIFY(array.capacity() >= array.count());
//     QCOMPARE(array.size(), array.count());

//     // Check that the array still contains the values we expected.
//     for (index = 0; index < ExpectedMinCapacity; ++index) {
//         QCOMPARE(array[index], double(index));
//     }
//     QCOMPARE(array[ExpectedMinCapacity], 1000.0);

//     // Append a large number of values to test constant reallocation.
//     for (index = 0; index < 1000; ++index)
//         array.append(double(index));
//     QCOMPARE(array.count(), ExpectedMinCapacity + 1 + 1000);
//     QCOMPARE(array.size(), array.count());

//     // Make two copies of the array.
//     QVERIFY(array.isDetached());
//     dtkArray<double> array2(array);
//     QVERIFY(!array.isDetached());
//     QVERIFY(!array2.isDetached());
//     QCOMPARE(array2.count(), ExpectedMinCapacity + 1 + 1000);
//     QCOMPARE(array2.size(), array2.count());
//     QVERIFY(!array2.isEmpty());
//     QVERIFY(array2.capacity() >= array2.size());
//     dtkArray<double> array3;
//     array3 = array;
//     QCOMPARE(array3.count(), ExpectedMinCapacity + 1 + 1000);
//     QCOMPARE(array3.size(), array3.count());
//     QVERIFY(!array3.isEmpty());
//     QVERIFY(array3.capacity() >= array3.size());

//     // Check that we actually are sharing the data between the copies.
//     QVERIFY(array.constRawData() == array2.constRawData());
//     QVERIFY(array.constRawData() == array3.constRawData());
//     d = array2.constRawData();

//     // Add another item to the original and check that the copy is unchanged.
//     array << double(1500.0);
//     QVERIFY(array.isDetached());
//     QCOMPARE(array.count(), ExpectedMinCapacity + 1 + 1000 + 1);
//     QCOMPARE(array2.count(), ExpectedMinCapacity + 1 + 1000);
//     QCOMPARE(array3.count(), ExpectedMinCapacity + 1 + 1000);

//     // Check that we have detached the first array (copy-on-write).
//     QVERIFY(array.constRawData() != array2.constRawData());
//     QVERIFY(array.constRawData() != array3.constRawData());
//     QVERIFY(array2.constRawData() == array3.constRawData());
//     QVERIFY(array2.constRawData() == d);

//     // Check that the original and the copy contain the right values.
//     for (index = 0; index < ExpectedMinCapacity; ++index) {
//         QCOMPARE(array.at(index), double(index));
//         QCOMPARE(array2.at(index), double(index));
//         QCOMPARE(array3.at(index), double(index));
//     }
//     QCOMPARE(array.at(ExpectedMinCapacity), 1000.0);
//     QCOMPARE(array2.at(ExpectedMinCapacity), 1000.0);
//     QCOMPARE(array3.at(ExpectedMinCapacity), 1000.0);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array.at(index + ExpectedMinCapacity + 1), double(index));
//     }
//     QCOMPARE(array[ExpectedMinCapacity + 1000 + 1], 1500.0);

//     // Check the detach conditions.
//     QVERIFY(!array2.isDetached());
//     QVERIFY(!array3.isDetached());
//     array3.append(1.0);
//     QVERIFY(array3.isDetached());
//     QVERIFY(!array2.isDetached()); // Still thinks it is shared.
//     array2.rawData();
//     QVERIFY(array2.isDetached());  // Now knows that it isn't.

//     // Create a large array of strings.
//     dtkArray<QString> array4;
//     for (index = 0; index < 1000; ++index)
//         array4.append(QString::number(index));
//     QCOMPARE(array4.size(), 1000);
//     for (index = 0; index < 1000; ++index)
//         QVERIFY(array4[index] == QString::number(index));

//     // Make a copy of the array of strings and then force a detach.
//     dtkArray<QString> array5(array4);
//     QCOMPARE(array4.size(), 1000);
//     QCOMPARE(array5.size(), 1000);
//     for (index = 0; index < 1000; ++index) {
//         QVERIFY(array4[index] == QString::number(index));
//         QVERIFY(array5[index] == QString::number(index));
//     }
//     array5.append(QString::number(1000));
//     QCOMPARE(array4.size(), 1000);
//     QCOMPARE(array5.size(), 1001);
//     for (index = 0; index < 1000; ++index) {
//         QVERIFY(array4[index] == QString::number(index));
//         QVERIFY(array5[index] == QString::number(index));
//     }
//     QVERIFY(array5[1000] == QString::number(1000));

//     // Create an array of complex values and force one realloc
//     // to test that copy constructors and destructors are called
//     // when moving data from the prealloc array to the heap.
//     dtkArray<ComplexValue> array6;
//     ComplexValue::destroyCount = 0;
//     for (index = 0; index < ExpectedMinCapacity; ++index)
//         array6.append(ComplexValue(index));
//     QCOMPARE(ComplexValue::destroyCount, ExpectedMinCapacity);
//     ComplexValue::destroyCount = 0;
//     array6.append(ComplexValue(ExpectedMinCapacity));
//     QCOMPARE(ComplexValue::destroyCount, ExpectedMinCapacity + 1);
//     for (index = 0; index < (ExpectedMinCapacity + 1); ++index) {
//         QCOMPARE(array6[index].value(), index);
//         // The last element should be Copy, but all others are CopiedAgain.
//         if (index == ExpectedMinCapacity)
//             QVERIFY(array6[index].mode() == ComplexValue::Copy);
//         else
//             QVERIFY(array6[index].mode() == ComplexValue::CopiedAgain);
//     }

//     // Force another realloc to test heap to heap copies.
//     int capacity = array6.capacity();
//     for (int index = array6.size(); index < capacity; ++index)
//         array6.append(ComplexValue(index));
//     ComplexValue::destroyCount = 0;
//     array6.append(ComplexValue(capacity));
//     QCOMPARE(ComplexValue::destroyCount, capacity + 1);
//     for (index = 0; index < (capacity + 1); ++index) {
//         QCOMPARE(array6[index].value(), index);
//         // The last element should be Copy, but all others are CopiedAgain.
//         if (index == capacity)
//             QVERIFY(array6[index].mode() == ComplexValue::Copy);
//         else
//             QVERIFY(array6[index].mode() == ComplexValue::CopiedAgain);
//     }

//     // Make a copy of array6 and force a detach.
//     int size = array6.size();
//     dtkArray<ComplexValue> array7(array6);
//     QCOMPARE(array6.size(), size);
//     QCOMPARE(array7.size(), size);
//     for (index = 0; index < size; ++index) {
//         QVERIFY(array6[index].value() == index);
//         QVERIFY(array7[index].value() == index);
//     }
//     array7.append(ComplexValue(size));
//     QCOMPARE(array6.size(), size);
//     QCOMPARE(array7.size(), size + 1);
//     for (index = 0; index < size; ++index) {
//         QVERIFY(array6[index].value() == index);
//         QVERIFY(array7[index].value() == index);
//     }
//     QVERIFY(array7[size].value() == size);

//     // Make another copy using operator=.
//     dtkArray<ComplexValue> array8;
//     QCOMPARE(array8.size(), 0);
//     array8 = array6;
//     QCOMPARE(array6.size(), size);
//     QCOMPARE(array8.size(), size);
//     for (index = 0; index < size; ++index) {
//         QVERIFY(array6[index].value() == index);
//         QVERIFY(array8[index].value() == index);
//     }
//     array8.append(ComplexValue(size));
//     QCOMPARE(array6.size(), size);
//     QCOMPARE(array8.size(), size + 1);
//     for (index = 0; index < size; ++index) {
//         QVERIFY(array6[index].value() == index);
//         QVERIFY(array8[index].value() == index);
//     }
//     QVERIFY(array8[size].value() == size);

//     // Copy the same object over itself.
//     dtkArray<ComplexValue> array9(array8);
//     QVERIFY(array9.constRawData() == array8.constRawData());
//     for (index = 0; index < array8.size(); ++index)
//         QCOMPARE((*((const dtkArray<ComplexValue> *)&array9))[index],
//                  array8.at(index));
//     array9 = array8;
//     QVERIFY(array9.constRawData() == array8.constRawData());
//     for (index = 0; index < array8.size(); ++index)
//         QCOMPARE(array9.at(index), array8.at(index));
// }

// void dtkArrayTestCase::testAppendTwoAtATime(void)
// {
//     int index;

//     dtkArray<double> array;
//     array.append(1.0, 2.0);
//     array.append(3.0, 4.0);
//     QCOMPARE(array[0], 1.0);
//     QCOMPARE(array[1], 2.0);
//     QCOMPARE(array[2], 3.0);
//     QCOMPARE(array[3], 4.0);
//     QCOMPARE(array.count(), 4);

//     dtkArray<double> array2;
//     for (index = 0; index < 1000; ++index)
//         array2.append(double(index), double(index + 1));
//     QCOMPARE(array2.count(), 2000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array2[index * 2], double(index));
//         QCOMPARE(array2[index * 2 + 1], double(index + 1));
//     }

//     dtkArray<QString> array3;
//     for (index = 0; index < 1000; ++index)
//         array3.append(QString::number(index), QString::number(index + 1));
//     QCOMPARE(array3.count(), 2000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array3[index * 2], QString::number(index));
//         QCOMPARE(array3[index * 2 + 1], QString::number(index + 1));
//     }

//     dtkArray<ComplexValue> array4;
//     for (index = 0; index < 1000; ++index)
//         array4.append(ComplexValue(index), ComplexValue(index + 1));
//     QCOMPARE(array4.count(), 2000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array4[index * 2].value(), index);
//         QCOMPARE(array4[index * 2 + 1].value(), index + 1);
//     }
// }

// void dtkArrayTestCase::testAppendThreeAtATime(void)
// {
//     int index;

//     dtkArray<double> array;
//     array.append(1.0, 2.0, 3.0);
//     array.append(4.0, 5.0, 6.0);
//     QCOMPARE(array[0], 1.0);
//     QCOMPARE(array[1], 2.0);
//     QCOMPARE(array[2], 3.0);
//     QCOMPARE(array[3], 4.0);
//     QCOMPARE(array[4], 5.0);
//     QCOMPARE(array[5], 6.0);
//     QCOMPARE(array.count(), 6);

//     dtkArray<double> array2;
//     for (index = 0; index < 1000; ++index)
//         array2.append(double(index), double(index + 1), double(index + 2));
//     QCOMPARE(array2.count(), 3000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array2[index * 3], double(index));
//         QCOMPARE(array2[index * 3 + 1], double(index + 1));
//         QCOMPARE(array2[index * 3 + 2], double(index + 2));
//     }

//     dtkArray<QString> array3;
//     for (index = 0; index < 1000; ++index)
//         array3.append(QString::number(index), QString::number(index + 1),
//                       QString::number(index + 2));
//     QCOMPARE(array3.count(), 3000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array3[index * 3], QString::number(index));
//         QCOMPARE(array3[index * 3 + 1], QString::number(index + 1));
//         QCOMPARE(array3[index * 3 + 2], QString::number(index + 2));
//     }

//     dtkArray<ComplexValue> array4;
//     for (index = 0; index < 1000; ++index)
//         array4.append(ComplexValue(index), ComplexValue(index + 1),
//                       ComplexValue(index + 2));
//     QCOMPARE(array4.count(), 3000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array4[index * 3].value(), index);
//         QCOMPARE(array4[index * 3 + 1].value(), index + 1);
//         QCOMPARE(array4[index * 3 + 2].value(), index + 2);
//     }
// }

// void dtkArrayTestCase::testAppendFourAtATime(void)
// {
//     int index;

//     dtkArray<double> array;
//     array.append(1.0, 2.0, 3.0, 4.0);
//     array.append(5.0, 6.0, 7.0, 8.0);
//     QCOMPARE(array[0], 1.0);
//     QCOMPARE(array[1], 2.0);
//     QCOMPARE(array[2], 3.0);
//     QCOMPARE(array[3], 4.0);
//     QCOMPARE(array[4], 5.0);
//     QCOMPARE(array[5], 6.0);
//     QCOMPARE(array[6], 7.0);
//     QCOMPARE(array[7], 8.0);
//     QCOMPARE(array.count(), 8);

//     dtkArray<double> array2;
//     for (index = 0; index < 1000; ++index)
//         array2.append(double(index), double(index + 1), double(index + 2), double(index + 3));
//     QCOMPARE(array2.count(), 4000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array2[index * 4], double(index));
//         QCOMPARE(array2[index * 4 + 1], double(index + 1));
//         QCOMPARE(array2[index * 4 + 2], double(index + 2));
//         QCOMPARE(array2[index * 4 + 3], double(index + 3));
//     }

//     dtkArray<QString> array3;
//     for (index = 0; index < 1000; ++index)
//         array3.append(QString::number(index), QString::number(index + 1),
//                       QString::number(index + 2), QString::number(index + 3));
//     QCOMPARE(array3.count(), 4000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array3[index * 4], QString::number(index));
//         QCOMPARE(array3[index * 4 + 1], QString::number(index + 1));
//         QCOMPARE(array3[index * 4 + 2], QString::number(index + 2));
//         QCOMPARE(array3[index * 4 + 3], QString::number(index + 3));
//     }

//     dtkArray<ComplexValue> array4;
//     for (index = 0; index < 1000; ++index)
//         array4.append(ComplexValue(index), ComplexValue(index + 1),
//                       ComplexValue(index + 2), ComplexValue(index + 3));
//     QCOMPARE(array4.count(), 4000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array4[index * 4].value(), index);
//         QCOMPARE(array4[index * 4 + 1].value(), index + 1);
//         QCOMPARE(array4[index * 4 + 2].value(), index + 2);
//         QCOMPARE(array4[index * 4 + 3].value(), index + 3);
//     }
// }

// void dtkArrayTestCase::testAppendArray(void)
// {
//     dtkArray<double> array;
//     dtkArray<double> array2;
//     int index;

//     for (index = 0; index < 1000; ++index) {
//         array.append(index);
//         array2.append(1000 - index);
//     }

//     array.append(array2);
//     QCOMPARE(array.count(), 2000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array[index], double(index));
//         QCOMPARE(array[index + 1000], double(1000 - index));
//     }

//     array2 << array2;
//     QCOMPARE(array2.count(), 2000);
//     for (index = 0; index < 1000; ++index) {
//         QCOMPARE(array2[index], double(1000 - index));
//         QCOMPARE(array2[index + 1000], double(1000 - index));
//     }

//     array2 += (dtkArray<double>());
//     QCOMPARE(array2.count(), 2000);

//     dtkArray<double> array3(array2.constRawData(), array2.size());
//     QCOMPARE(array3.size(), array2.size());
//     for (index = 0; index < array2.size(); ++index)
//         QCOMPARE(array3.at(index), array2.at(index));
// }

// void dtkArrayTestCase::testSetAt(void)
// {
//     int index;

//     dtkArray<double> array;
//     array.append(1.0);
//     QCOMPARE(array[0], 1.0);

//     array[0] = 6.0;
//     QCOMPARE(array[0], 6.0);

//     dtkArray<double> array2;
//     for (index = 0; index < 1000; ++index)
//         array2.append(index);
//     for (index = 0; index < 1000; ++index)
//         array2[index] = index + 1000;
//     for (index = 0; index < 1000; ++index)
//         QCOMPARE(array2[index], double(index + 1000));
//     for (index = 0; index < 1000; ++index)
//         array2.replace(index, double(-index));
//     for (index = 0; index < 1000; ++index)
//         QCOMPARE(array2[index], double(-index));
// }

// void dtkArrayTestCase::testValue(void)
// {
//     dtkArray<double> array;
//     for (int index = 0; index < 1000; ++index)
//         array.append(double(index));

//     for (int index = 0; index < 1000; ++index) {
//         QCOMPARE(array.value(index), double(index));
//         QCOMPARE(array.value(index, 10001.0), double(index));
//     }

//     QCOMPARE(array.value(-1), 0.0);
//     QCOMPARE(array.value(1000), 0.0);

//     QCOMPARE(array.value(-1, 10001.0), 10001.0);
//     QCOMPARE(array.value(1000, 10001.0), 10001.0);
// }

// void dtkArrayTestCase::testReplace(void)
// {
//     dtkArray<double> array;
//     dtkArray<double> array2;
//     int index;

//     for (index = 0; index < 1000; ++index) {
//         array.append(index);
//         array2.append(1000 - index);
//     }

//     array.replace(500, array2.constRawData(), 500);
//     QCOMPARE(array.count(), 1000);
//     for (index = 0; index < 1000; ++index) {
//         if (index < 500)
//             QCOMPARE(array[index], double(index));
//         else
//             QCOMPARE(array[index], double(1000 - (index - 500)));
//     }

//     // Replace and extend the array from the middle.
//     array.replace(900, array2.constRawData(), 500);
//     QCOMPARE(array.count(), 1400);
//     for (index = 0; index < 1400; ++index) {
//         if (index < 500)
//             QCOMPARE(array[index], double(index));
//         else if (index < 900)
//             QCOMPARE(array[index], double(1000 - (index - 500)));
//         else
//             QCOMPARE(array[index], double(1000 - (index - 900)));
//     }

//     // Check the bail-out cases when index is negative or count zero.
//     array.replace(900, array2.constRawData(), 0);
//     array.replace(-1, array2.constRawData(), 900);
//     QCOMPARE(array.count(), 1400);
//     for (index = 0; index < 1400; ++index) {
//         if (index < 500)
//             QCOMPARE(array[index], double(index));
//         else if (index < 900)
//             QCOMPARE(array[index], double(1000 - (index - 500)));
//         else
//             QCOMPARE(array[index], double(1000 - (index - 900)));
//     }

//     // Replace beyond the end of the array.
//     static double const extras[] = {0.0, 0.0, 1.0, 2.0, 3.0, 4.0};
//     array.replace(1402, extras + 2, 4);
//     QCOMPARE(array.count(), 1406);
//     for (index = 0; index < 1406; ++index) {
//         if (index < 500)
//             QCOMPARE(array[index], double(index));
//         else if (index < 900)
//             QCOMPARE(array[index], double(1000 - (index - 500)));
//         else if (index < 1400)
//             QCOMPARE(array[index], double(1000 - (index - 900)));
//         else
//             QCOMPARE(array[index], extras[index - 1400]);
//     }

//     dtkArray<ComplexValue> array3;
//     dtkArray<ComplexValue> array4;
//     for (index = 0; index < 1000; ++index) {
//         array3.append(ComplexValue(index));
//         array4.append(ComplexValue(1000 - index));
//     }
//     array3.replace(0, array4.constRawData(), array4.size());
//     for (index = 0; index < 1000; ++index)
//         QVERIFY(array3[index] == array4[index]);
// }

// // Exercise the various conditionals in operator=().
// void dtkArrayTestCase::testCopy(void)
// {
//     dtkArray<double> array, array2, array3;

//     array2.append(1.0);
//     array2.append(7.0);
//     array = array2;
//     QCOMPARE(array.count(), 2);
//     QCOMPARE(array.at(0), double(1.0));
//     QCOMPARE(array.at(1), double(7.0));

//     array = array3;
//     QCOMPARE(array.count(), 0);

//     array2 = array2;
//     QCOMPARE(array2.count(), 2);
//     QCOMPARE(array2.at(0), double(1.0));
//     QCOMPARE(array2.at(1), double(7.0));

//     dtkArray<double> array4(array2);
//     QCOMPARE(array2.count(), 2);
//     QCOMPARE(array2.at(0), double(1.0));
//     QCOMPARE(array2.at(1), double(7.0));

//     dtkArray<double> array5, array6;
//     for (int index = 0; index < 32; ++index)
//         array5.append(2.0);
//     QCOMPARE(array5.count(), 32);
//     array6.append(1.0);
//     array5 = array6;
//     QCOMPARE(array5.count(), 1);
//     QCOMPARE(array5.at(0), double(1.0));

//     array5.clear();
//     QCOMPARE(array5.count(), 0);
//     QCOMPARE(array6.count(), 1);
//     QCOMPARE(array6.at(0), double(1.0));
//     array6.clear();
//     QCOMPARE(array5.count(), 0);
// }

// void dtkArrayTestCase::testResize(void)
// {
//     dtkArray<int> array;

//     array.resize(-1);
//     QCOMPARE(array.count(), 0);

//     array.resize(ExpectedMinCapacity);
//     QCOMPARE(array.count(), ExpectedMinCapacity);
//     for (int index = 0; index < ExpectedMinCapacity; ++index)
//         QCOMPARE(array[index], 0);
//     array.append(1);

//     array.resize(100);
//     QCOMPARE(array.count(), 100);
//     QVERIFY(array.capacity() >= 100);
//     int cap = array.capacity();
//     for (int index = 0; index < 100; ++index){
//         if (index != 8)
//             QCOMPARE(array[index], 0);
//         else
//             QCOMPARE(array[index], 1);
//     }

//     array.resize(50);
//     QCOMPARE(array.count(), 50);
//     QVERIFY(array.capacity() == cap); // Shouldn't change the capacity.
//     for (int index = 0; index < 50; ++index){
//         if (index != 8)
//             QCOMPARE(array[index], 0);
//         else
//             QCOMPARE(array[index], 1);
//     }

//     array.resize(50);
//     QCOMPARE(array.count(), 50);

//     dtkArray<int> array2(array);
//     array.resize(40);
//     QCOMPARE(array.count(), 40);
//     QCOMPARE(array2.count(), 50);

//     array2.resize(20);
//     QCOMPARE(array2.count(), 20);

//     for (int index = 0; index < 40; ++index){
//         if (index != 8)
//             QCOMPARE(array[index], 0);
//         else
//             QCOMPARE(array[index], 1);
//     }
//     for (int index = 0; index < 20; ++index){
//         if (index != 8)
//             QCOMPARE(array2[index], 0);
//         else
//             QCOMPARE(array2[index], 1);
//     }

//     // Check that resizing to zero keeps the same memory storage.
//     const int *d = array.constRawData();
//     array.resize(0);
//     QVERIFY(array.constRawData() == d);
//     QVERIFY(array.capacity() != ExpectedMinCapacity);

//     // Calling clear will reclaim the storage.
//     array.clear();
//     QVERIFY(array.constRawData() != d);
//     QVERIFY(array.capacity() == ExpectedMinCapacity);
// }

// void dtkArrayTestCase::testReserve(void)
// {
//     dtkArray<double> array;
//     array.reserve(1000);
//     QVERIFY(array.isEmpty());
//     QVERIFY(array.capacity() >= 1000);

//     // Append elements and check for reallocation.
//     const double *d = array.constRawData();
//     for (int index = 0; index < 1000; ++index) {
//         array.append(double(index));
//         QVERIFY(array.constRawData() == d);
//     }

//     // Reserving less doesn't change the capacity, or the count.
//     array.reserve(50);
//     QVERIFY(array.capacity() >= 1000);
//     QCOMPARE(array.count(), 1000);
// }

// void dtkArrayTestCase::testSqueeze(void)
// {
//     dtkArray<double> array;
//     array.reserve(100);
//     QVERIFY(array.isEmpty());
//     QVERIFY(array.capacity() >= 100);

//     for (int index = 0; index < 100; ++index)
//         array.append(double(index));

//     array.reserve(400);
//     QVERIFY(array.capacity() >= 400);

//     array.squeeze();
//     QCOMPARE(array.capacity(), 100);
//     QCOMPARE(array.count(), 100);

//     // Test squeezing within the preallocated area.
//     dtkArray<double> array2;
//     array2.append(1.0);
//     array2.append(2.0);
//     array2.append(3.0);
//     array2.squeeze();
//     QCOMPARE(array2.capacity(), ExpectedMinCapacity);
//     QCOMPARE(array2.count(), 3);

//     // Test copy-on-write during squeezing.
//     dtkArray<double> array3(array);
//     array3.squeeze();
//     QCOMPARE(array3.count(), 100);
//     QCOMPARE(array.count(), 100);

//     // Clear and check that the array reverts to preallocation.
//     array.resize(0);
//     array.squeeze();
//     QCOMPARE(array.size(), 0);
//     QCOMPARE(array.capacity(), ExpectedMinCapacity);
// }

// void dtkArrayTestCase::testCompare(void)
// {
//     dtkArray<double> array, array2, array3;

//     QVERIFY(array == array2);

//     array.append(1.0);
//     array3.append(1.0);
//     dtkArray<double> array4(array);

//     QVERIFY(array == array);
//     QVERIFY(array != array2);
//     QVERIFY(array == array3);
//     QVERIFY(array == array4);

//     array2.append(2.0);
//     QVERIFY(array != array2);

//     array2.append(1.0);
//     QVERIFY(array != array2);

//     for (int index = 0; index < 100; ++index)
//         array.append(index);
//     array2 = array;
//     QVERIFY(array2 == array);
//     QVERIFY(!(array2 != array));
// }

// void dtkArrayTestCase::testRemove(void)
// {
//     dtkArray<double> array;

//     array.remove(0, 100);
//     QCOMPARE(array.count(), 0);

//     for (int index = 0; index < 100; ++index)
//         array.append(double(index));

//     array.remove(100, 60);
//     QCOMPARE(array.count(), 100);
//     array.remove(-60, 60);

//     array.remove(10, 20);
//     QCOMPARE(array.count(), 80);
//     for (int index = 0; index < 80; ++index) {
//         if (index < 10)
//             QCOMPARE(array[index], double(index));
//         else
//             QCOMPARE(array[index], double(index + 20));
//     }

//     dtkArray<double> array2(array);
//     array2.remove(-10, 20);
//     array2.remove(60, 20);
//     QCOMPARE(array2.count(), 60);
//     for (int index = 0; index < 60; ++index) {
//         QCOMPARE(array2[index], double(index + 30));
//     }

//     array.remove(0, 10);
//     QCOMPARE(array.count(), 70);
//     for (int index = 0; index < 70; ++index) {
//         QCOMPARE(array[index], double(index + 30));
//     }

//     // Remove everything and check that it returns to preallocation.
//     array.remove(0, array.size());
//     QCOMPARE(array.count(), 0);
//     QCOMPARE(array.capacity(), ExpectedMinCapacity);

//     for (int index = 0; index < 100; ++index)
//         array.append(double(index));
//     array.erase(array.end() - 1);
//     QCOMPARE(array.size(), 99);
//     array.erase(array.begin(), array.end());
//     QCOMPARE(array.count(), 0);
// }

// void dtkArrayTestCase::testRemoveFirstLast(void)
// {
//     dtkArray<double> array;

//     array.removeFirst();
//     QVERIFY(array.isEmpty());
//     array.removeLast();
//     QVERIFY(array.isEmpty());

//     for (int index = 0; index < 100; ++index)
//         array.append(double(index));

//     array.removeFirst();
//     QCOMPARE(array.size(), 99);
//     for (int index = 0; index < array.size(); ++index)
//         QCOMPARE(array[index], double(index + 1));

//     array.removeLast();
//     QCOMPARE(array.size(), 98);
//     for (int index = 0; index < array.size(); ++index)
//         QCOMPARE(array[index], double(index + 1));
// }

// void dtkArrayTestCase::testExtend(void)
// {
//     dtkArray<double> array;

//     double *ptr = array.extend(4);
//     ptr[0] = 1.0;
//     ptr[1] = 2.0;
//     ptr[2] = 3.0;
//     ptr[3] = 4.0;
//     QCOMPARE(array.size(), 4);
//     QCOMPARE(array[0], 1.0);
//     QCOMPARE(array[1], 2.0);
//     QCOMPARE(array[2], 3.0);
//     QCOMPARE(array[3], 4.0);

//     array.append(5.0);
//     ptr = array.extend(1);
//     ptr[0] = 6.0;
//     QCOMPARE(array.size(), 6);
//     QCOMPARE(array[0], 1.0);
//     QCOMPARE(array[1], 2.0);
//     QCOMPARE(array[2], 3.0);
//     QCOMPARE(array[3], 4.0);
//     QCOMPARE(array[4], 5.0);
//     QCOMPARE(array[5], 6.0);

//     dtkArray<double> array2(array);

//     ptr = array.extend(1);
//     ptr[0] = 7.0;
//     QCOMPARE(array.size(), 7);
//     QCOMPARE(array[0], 1.0);
//     QCOMPARE(array[1], 2.0);
//     QCOMPARE(array[2], 3.0);
//     QCOMPARE(array[3], 4.0);
//     QCOMPARE(array[4], 5.0);
//     QCOMPARE(array[5], 6.0);
//     QCOMPARE(array[6], 7.0);

//     QCOMPARE(array2.size(), 6);
// }

// void dtkArrayTestCase::testReverse(void)
// {
//     dtkArray<double> array0;

//     // null case
//     array0.reverse();
//     QCOMPARE(array0.size(), 0);

//     // basic case
//     double *ptr = array0.extend(1);
//     ptr[0] = 1.0;
//     array0.reverse();
//     QCOMPARE(array0.size(), 1);
//     QCOMPARE(array0.at(0), 1.0);

//     // odd numbered size
//     dtkArray<double> array1;
//     ptr = array1.extend(5);
//     ptr[0] = 1.0;
//     ptr[1] = 2.0;
//     ptr[2] = 3.0;
//     ptr[3] = 4.0;
//     ptr[4] = 5.0;
//     array1.reverse();
//     QCOMPARE(array1.size(), 5);
//     QCOMPARE(array1.at(0), 5.0);
//     QCOMPARE(array1.at(2), 3.0);
//     QCOMPARE(array1.at(4), 1.0);

//     // even numbered size
//     dtkArray<double> array2;
//     ptr = array2.extend(6);
//     ptr[0] = 1.0;
//     ptr[1] = 2.0;
//     ptr[2] = 3.0;
//     ptr[3] = 4.0;
//     ptr[4] = 5.0;
//     ptr[5] = 6.0;
//     array2.reverse();
//     QCOMPARE(array2.size(), 6);
//     QCOMPARE(array2.at(0), 6.0);
//     QCOMPARE(array2.at(2), 4.0);
//     QCOMPARE(array2.at(3), 3.0);
//     QCOMPARE(array2.at(5), 1.0);

//     // complex type
//     QVERIFY(QTypeInfo<QString>::isComplex);
//     dtkArray<QString> array3(6, QLatin1String("test"));
//     array3[0] = QLatin1String("zero");
//     array3[1] = QLatin1String("one");
//     array3[2] = QLatin1String("two");
//     array3[3] = QLatin1String("three");
//     array3[4] = QLatin1String("four");
//     array3[5] = QLatin1String("five");
//     array3.reverse();
//     QCOMPARE(array3.size(), 6);
//     QCOMPARE(array3.at(0), QLatin1String("five"));
//     QCOMPARE(array3.at(2), QLatin1String("three"));
//     QCOMPARE(array3.at(3), QLatin1String("two"));
//     QCOMPARE(array3.at(5), QLatin1String("zero"));
// }

// void dtkArrayTestCase::testReversed(void)
// {
//     dtkArray<double> array0;

//     // null case
//     dtkArray<double> res0 = array0.reversed();
//     QCOMPARE(res0.size(), 0);

//     // basic case
//     double *ptr = array0.extend(1);
//     ptr[0] = 1.0;
//     res0 = array0.reversed();
//     QCOMPARE(res0.size(), 1);
//     QCOMPARE(res0.at(0), 1.0);

//     // odd numbered size
//     dtkArray<double> array1;
//     ptr = array1.extend(5);
//     ptr[0] = 1.0;
//     ptr[1] = 2.0;
//     ptr[2] = 3.0;
//     ptr[3] = 4.0;
//     ptr[4] = 5.0;
//     dtkArray<double> res1 = array1.reversed();
//     QCOMPARE(res1.size(), 5LL);
//     QCOMPARE(res1.at(0), 5.0);
//     QCOMPARE(res1.at(2), 3.0);
//     QCOMPARE(res1.at(4), 1.0);

//     // even numbered size
//     dtkArray<double> array2;
//     ptr = array2.extend(6);
//     ptr[0] = 1.0;
//     ptr[1] = 2.0;
//     ptr[2] = 3.0;
//     ptr[3] = 4.0;
//     ptr[4] = 5.0;
//     ptr[5] = 6.0;
//     dtkArray<double> res2 = array2.reversed();
//     QCOMPARE(res2.size(), 6LL);
//     QCOMPARE(res2.at(0), 6.0);
//     QCOMPARE(res2.at(2), 4.0);
//     QCOMPARE(res2.at(3), 3.0);
//     QCOMPARE(res2.at(5), 1.0);

//     // simple type with larger size
//     dtkArray<QVector3D> array4;
//     array4.extend(6);
//     QVector3D va(1.0f, 2.0f, 3.0f);
//     QVector3D vb(11.0f, 12.0f, 13.0f);
//     QVector3D vc(21.0f, 22.0f, 23.0f);
//     QVector3D vd(31.0f, 32.0f, 33.0f);
//     QVector3D ve(41.0f, 42.0f, 43.0f);
//     QVector3D vf(51.0f, 52.0f, 53.0f);
//     array4[0] = va;
//     array4[1] = vb;
//     array4[2] = vc;
//     array4[3] = vd;
//     array4[4] = ve;
//     array4[5] = vf;
//     dtkArray<QVector3D> res4 = array4.reversed();
//     QCOMPARE(res4.size(), 6);
//     QCOMPARE(res4.at(0), vf);
//     QCOMPARE(res4.at(2), vd);
//     QCOMPARE(res4.at(3), vc);
//     QCOMPARE(res4.at(5), va);
// }

// void dtkArrayTestCase::testMid(void)
// {
//     dtkArray<double> array;
//     for (int index = 0; index < 1024; ++index)
//         array.append(double(index));

//     dtkArray<double> mid = array.mid(0);
//     QCOMPARE(mid.size(), array.size());
//     QVERIFY(!mid.isEmpty());
//     QVERIFY(mid.constRawData() == array.constRawData());
//     for (int index = 0; index < 1024; ++index) {
//         QCOMPARE(mid.at(index), double(index));
//         QCOMPARE(mid[index], double(index));
//     }

//     mid = array.mid(500, 20);
//     QCOMPARE(mid.size(), 20);
//     QVERIFY(!mid.isEmpty());
//     for (int index = 0; index < 20; ++index) {
//         QCOMPARE(mid.at(index), double(index + 500));
//         QCOMPARE(mid[index], double(index + 500));
//     }

//     dtkArray<double> mid2 = array.mid(500, 20);
//     QVERIFY(mid == mid2);
//     QVERIFY(!(mid != mid2));

//     dtkArray<double> mid3 = array.mid(500, 21);
//     QVERIFY(mid != mid3);
//     QVERIFY(!(mid == mid3));

//     dtkArray<double> mid4 = array.mid(400, 20);
//     QVERIFY(mid != mid4);
//     QVERIFY(!(mid == mid4));

//     dtkArray<double> mid5;
//     dtkArray<double> mid6;
//     QVERIFY(mid != mid5);
//     QVERIFY(!(mid == mid5));
//     QVERIFY(mid5 != mid);
//     QVERIFY(!(mid5 == mid));
//     QVERIFY(mid5 == mid6);
//     QVERIFY(!(mid5 != mid6));

//     mid = array.mid(500, 0);
//     QCOMPARE(mid.size(), 0);
//     QVERIFY(mid.isEmpty());

//     mid = array.mid(1000, 30);
//     QCOMPARE(mid.size(), 24LL);
//     QVERIFY(!mid.isEmpty());
//     for (int index = 0; index < 24; ++index) {
//         QCOMPARE(mid.at(index), double(index + 1000));
//         QCOMPARE(mid[index], double(index + 1000));
//     }
// }

// void dtkArrayTestCase::testLeft(void)
// {
//     dtkArray<double> array;
//     for (int index = 0; index < 1024; ++index)
//         array.append(double(index));

//     dtkArray<double> left = array.left(-1);
//     QVERIFY(left == array);

//     left = array.left(0);
//     QVERIFY(left.isEmpty());

//     left = array.left(500);
//     QCOMPARE(left.size(), 500);
//     QVERIFY(left == array.mid(0, 500));

//     left = array.left(2048);
//     QVERIFY(left == array);
// }

// void dtkArrayTestCase::testRight(void)
// {
//     dtkArray<double> array;
//     for (int index = 0; index < 1024; ++index)
//         array.append(double(index));

//     dtkArray<double> right = array.right(-1);
//     QVERIFY(right == array);

//     right = array.right(0);
//     QVERIFY(right.isEmpty());

//     right = array.right(500);
//     QCOMPARE(right.size(), 500);
//     QVERIFY(right == array.mid(1024 - 500, 500));

//     right = array.right(2048);
//     QVERIFY(right == array);
// }

// void dtkArrayTestCase::testIterate(void)
// {
//     dtkArray<double> array;
//     for (int index = 0; index < 1024; ++index)
//         array.append(double(index));

//     dtkArray<double>::Iterator it1;
//     int value = 0;
//     for (it1 = array.begin(); it1 != array.end(); ++it1)
//         QCOMPARE(*it1, double(value++));
//     QCOMPARE(value, array.size());

//     dtkArray<double>::ConstIterator it2;
//     value = 0;
//     for (it2 = array.constBegin(); it2 != array.constEnd(); ++it2)
//         QCOMPARE(*it2, double(value++));
//     QCOMPARE(value, array.size());

//     value = 0;
//     for (it1 = array.begin(); it1 != array.end(); ++it1)
//         *it1 = double(1024 - value++);
//     value = 0;
//     for (it2 = array.constBegin(); it2 != array.constEnd(); ++it2) {
//         QCOMPARE(*it2, double(1024 - value));
//         QCOMPARE(array[value], double(1024 - value));
//         ++value;
//     }

//     for (int index = 0; index < 1024; ++index)
//         array[index] = double(index);
// }

// // Verify that when the data is in the preallocated section, it is
// // copied across and the original constRawData() pointer remains the same.
// void dtkArrayTestCase::testCopyPrealloc(void)
// {
//     dtkArray<double> array1;
//     array1.append(1.0);
//     array1.append(2.0);

//     const double *data = array1.constRawData();

//     dtkArray<double> array2(array1);

//     QVERIFY(array1.constRawData() == data);
//     QVERIFY(array2.constRawData() != data);

//     QCOMPARE(array2.size(), 2);
//     QCOMPARE(array2[0], double(1.0));
//     QCOMPARE(array2[1], double(2.0));

//     dtkArray<double> array3;
//     QCOMPARE(array3.size(), 0);
//     array3 = array1;

//     QVERIFY(array1.constRawData() == data);
//     QVERIFY(array3.constRawData() != data);

//     QCOMPARE(array3.size(), 2);
//     QCOMPARE(array3[0], double(1.0));
//     QCOMPARE(array3[1], double(2.0));
// }

// void dtkArrayTestCase::testInsert(void)
// {
//     dtkArray<double> array;
//     for (int index = 0; index < 10; ++index)
//         array.append(double(index));

//     array.prepend(-1.0);
//     QCOMPARE(array.size(), 11);
//     for (int index = 0; index < array.size(); ++index)
//         QCOMPARE(array[index], double(index - 1));

//     array.insert(array.size(), 10.0);
//     QCOMPARE(array.size(), 12);
//     for (int index = 0; index < array.size(); ++index)
//         QCOMPARE(array[index], double(index - 1));

//     array.insert(1, 0.5);
//     QCOMPARE(array.size(), 13);
//     QCOMPARE(array[0], -1.0);
//     QCOMPARE(array[1], 0.5);
//     QCOMPARE(array[2], 0.0);
//     QCOMPARE(array[12], 10.0);

//     array.insert(10, 0, 7.5);
//     array.insert(10, 4, 7.5);
//     QCOMPARE(array.size(), 17);
//     QCOMPARE(array[9], 7.0);
//     QCOMPARE(array[10], 7.5);
//     QCOMPARE(array[11], 7.5);
//     QCOMPARE(array[12], 7.5);
//     QCOMPARE(array[13], 7.5);
//     QCOMPARE(array[14], 8.0);
//     QCOMPARE(array[15], 9.0);
//     QCOMPARE(array[16], 10.0);

//     // Repeat the tests with QString
//     dtkArray<QString> array2;
//     for (int index = 0; index < 10; ++index)
//         array2.append(QString::number(index));

//     array2.prepend(QString::number(-1));
//     QCOMPARE(array2.size(), 11);
//     for (int index = 0; index < array2.size(); ++index)
//         QCOMPARE(array2[index], QString::number(index - 1));

//     array2.insert(array2.size(), QString::number(10));
//     QCOMPARE(array2.size(), 12);
//     for (int index = 0; index < array2.size(); ++index)
//         QCOMPARE(array2[index], QString::number(index - 1));

//     array2.insert(1, QString::number(5));
//     QCOMPARE(array2.size(), 13);
//     QCOMPARE(array2[0], QString::number(-1));
//     QCOMPARE(array2[1], QString::number(5));
//     QCOMPARE(array2[2], QString::number(0));
//     QCOMPARE(array2[12], QString::number(10));

//     array2.insert(10, 4, QString::number(3));
//     QCOMPARE(array2.size(), 17);
//     QCOMPARE(array2[9], QString::number(7));
//     QCOMPARE(array2[10], QString::number(3));
//     QCOMPARE(array2[11], QString::number(3));
//     QCOMPARE(array2[12], QString::number(3));
//     QCOMPARE(array2[13], QString::number(3));
//     QCOMPARE(array2[14], QString::number(8));
//     QCOMPARE(array2[15], QString::number(9));
//     QCOMPARE(array2[16], QString::number(10));

//     // Repeat the tests with ComplexValue
//     dtkArray<ComplexValue> array3;
//     for (int index = 0; index < 10; ++index)
//         array3.append(ComplexValue(index));

//     array3.prepend(ComplexValue(-1));
//     ComplexValue::destroyCount = 0;
//     QCOMPARE(array3.size(), 11);
//     for (int index = 0; index < array3.size(); ++index) {
//         QVERIFY(array3[index] == (index - 1));
//         QVERIFY(array3[index].mode() == ComplexValue::Assign);
//     }
//     QCOMPARE(ComplexValue::destroyCount, 0);

//     array3.insert(array3.size(), ComplexValue(10));
//     QCOMPARE(array3.size(), 12);
//     for (int index = 0; index < array3.size(); ++index)
//         QVERIFY(array3[index] == (index - 1));

//     array3.insert(1, ComplexValue(5));
//     QCOMPARE(array3.size(), 13);
//     QVERIFY(array3[0] == -1);
//     QVERIFY(array3[1] == 5);
//     QVERIFY(array3[2] == 0);
//     QVERIFY(array3[12] == 10);

//     array3.insert(10, 4, ComplexValue(3));
//     QCOMPARE(array3.size(), 17);
//     QVERIFY(array3[9] == 7);
//     QVERIFY(array3[10] == 3);
//     QVERIFY(array3[11] == 3);
//     QVERIFY(array3[12] == 3);
//     QVERIFY(array3[13] == 3);
//     QVERIFY(array3[14] == 8);
//     QVERIFY(array3[15] == 9);
//     QVERIFY(array3[16] == 10);
// }

// void dtkArrayTestCase::testSetRawData(void)
// {
//     dtkArray<double> array;
//     double contents[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
//                         7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

//     array.setRawData(contents, 0);
//     QCOMPARE(array.size(), 0);
//     QCOMPARE(array.capacity(), 0);
//     QVERIFY(!array.isDetached());
//     array.append(1.0);
//     QCOMPARE(array.size(), 1);
//     QVERIFY(array.capacity() > 0);
//     QCOMPARE(array.at(0), 1.0);
//     QVERIFY(array.isDetached());

//     array.setRawData(contents, 6);
//     QCOMPARE(array.size(), 6);
//     QCOMPARE(array.capacity(), 6);
//     for (int index = 0; index < 6; ++index)
//         QCOMPARE(array.at(index), contents[index]);
//     QVERIFY(array.constRawData() == contents);
//     QVERIFY(!array.isDetached());    

//     // Force a copy-on-write.
//     array[3] = 42.0;
//     QVERIFY(array.isDetached());
//     QCOMPARE(contents[3], 4.0);
//     QCOMPARE(array.size(), 6);
//     QVERIFY(array.capacity() > 6);
//     for (int index = 0; index < 6; ++index) {
//         if (index != 3)
//             QCOMPARE(array.at(index), contents[index]);
//         else
//             QCOMPARE(array.at(index), 42.0);
//     }
//     QVERIFY(array.constRawData() != contents);

//     array.setRawData(contents, 12);
//     QCOMPARE(array.size(), 12);
//     QCOMPARE(array.capacity(), 12);
//     for (int index = 0; index < 12; ++index)
//         QCOMPARE(array.at(index), contents[index]);
//     QVERIFY(array.constRawData() == contents);

//     QString strings[] = {QLatin1String("foo"), QLatin1String("bar")};
//     dtkArray<QString> array2;
//     array2.setRawData(strings, 2);
//     QCOMPARE(array2.size(), 2);
//     QCOMPARE(array2.capacity(), 2);
//     QCOMPARE(array2.at(0), QLatin1String("foo"));
//     QCOMPARE(array2.at(1), QLatin1String("bar"));
//     QVERIFY(array2.constRawData() == strings);

//     // Force a copy-on-write.
//     array2[1] = QLatin1String("baz");
//     QCOMPARE(array2.size(), 2);
//     QVERIFY(array2.capacity() > 2);
//     QCOMPARE(array2.at(0), QLatin1String("foo"));
//     QCOMPARE(array2.at(1), QLatin1String("baz"));
//     QVERIFY(array2.constRawData() != strings);
//     QCOMPARE(strings[0], QLatin1String("foo"));
//     QCOMPARE(strings[1], QLatin1String("bar"));
// }

// void dtkArrayTestCase::testFromRawData(void)
// {
//     dtkArray<double> array;
//     double contents[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
//                         7.0, 8.0, 9.0, 10.0, 11.0, 12.0};

//     array = dtkArray<double>::fromRawData(contents, 0);
//     QCOMPARE(array.size(), 0);
//     QCOMPARE(array.capacity(), 0);
//     QVERIFY(!array.isDetached());
//     array.append(1.0);
//     QCOMPARE(array.size(), 1);
//     QVERIFY(array.capacity() > 0);
//     QCOMPARE(array.at(0), 1.0);
//     QVERIFY(array.isDetached());

//     array = dtkArray<double>::fromRawData(contents, 6);
//     QCOMPARE(array.size(), 6);
//     QCOMPARE(array.capacity(), 6);
//     for (int index = 0; index < 6; ++index)
//         QCOMPARE(array.at(index), contents[index]);
//     QVERIFY(array.constRawData() == contents);
//     QVERIFY(!array.isDetached());

//     // Force a copy-on-write.
//     array[3] = 42.0;
//     QVERIFY(array.isDetached());
//     QCOMPARE(contents[3], 4.0);
//     QCOMPARE(array.size(), 6);
//     QVERIFY(array.capacity() > 6);
//     for (int index = 0; index < 6; ++index) {
//         if (index != 3)
//             QCOMPARE(array.at(index), contents[index]);
//         else
//             QCOMPARE(array.at(index), 42.0);
//     }
//     QVERIFY(array.constRawData() != contents);

//     array = dtkArray<double>::fromRawData(contents, 12);
//     QCOMPARE(array.size(), 12);
//     QCOMPARE(array.capacity(), 12);
//     for (int index = 0; index < 12; ++index)
//         QCOMPARE(array.at(index), contents[index]);
//     QVERIFY(array.constRawData() == contents);

//     QString strings[] = {QLatin1String("foo"), QLatin1String("bar")};
//     dtkArray<QString> array2;
//     array2 = dtkArray<QString>::fromRawData(strings, 2);
//     QCOMPARE(array2.size(), 2);
//     QCOMPARE(array2.capacity(), 2);
//     QCOMPARE(array2.at(0), QLatin1String("foo"));
//     QCOMPARE(array2.at(1), QLatin1String("bar"));
//     QVERIFY(array2.constRawData() == strings);

//     // Force a copy-on-write.
//     array2[1] = QLatin1String("baz");
//     QCOMPARE(array2.size(), 2);
//     QVERIFY(array2.capacity() > 2);
//     QCOMPARE(array2.at(0), QLatin1String("foo"));
//     QCOMPARE(array2.at(1), QLatin1String("baz"));
//     QVERIFY(array2.constRawData() != strings);
//     QCOMPARE(strings[0], QLatin1String("foo"));
//     QCOMPARE(strings[1], QLatin1String("bar"));
// }

// void dtkArrayTestCase::testFromWritableRawData(void)
// {
//     dtkArray<double> array;
//     double contents[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
//     double contentsModified[] =
//         {1.0, 2.0, 3.0, 42.0, 5.0, 6.0, 53.0};

//     array = dtkArray<double>::fromWritableRawData(contents, 0);
//     QCOMPARE(array.size(), 0);
//     QCOMPARE(array.capacity(), 0);
//     array.append(0.0);
//     QCOMPARE(array.size(), 1);
//     QVERIFY(array.capacity() > 0);
//     QCOMPARE(array.at(0), 0.0);

//     array = dtkArray<double>::fromWritableRawData(contents, 6);
//     QCOMPARE(array.size(), 6);
//     QCOMPARE(array.capacity(), 6);
//     for (int index = 0; index < 6; ++index)
//         QCOMPARE(array.at(index), contents[index]);
//     QVERIFY(array.constRawData() == contents);

//     // Modify the raw data in-place.
//     array[3] = 42.0;
//     QVERIFY(array.constRawData() == contents);

//     // Force a copy.
//     array.append(53.0);
//     QVERIFY(array.constRawData() != contents);
//     for (int index = 0; index < array.size(); ++index)
//         QCOMPARE(array.at(index), contentsModified[index]);

//     // Resize to smaller should stay within the raw data.
//     array = dtkArray<double>::fromWritableRawData(contents, 6);
//     array.resize(6);
//     QCOMPARE(array.size(), 6);
//     array.resize(5);
//     QCOMPARE(array.size(), 5);
//     QVERIFY(array.constRawData() == contents);
//     for (int index = 0; index < array.size(); ++index)
//         QCOMPARE(array.at(index), contentsModified[index]);
//     array.append(6.0);
//     QVERIFY(array.constRawData() == contents);
//     for (int index = 0; index < array.size(); ++index)
//         QCOMPARE(array.at(index), contentsModified[index]);

//     // Resize to larger should force a copy.
//     array = dtkArray<double>::fromWritableRawData(contents, 6);
//     array.resize(7);
//     QVERIFY(array.constRawData() != contents);
//     for (int index = 0; index < 6; ++index)
//         QCOMPARE(array.at(index), contentsModified[index]);
//     QCOMPARE(array.at(6), 0.0);

//     // Reserve to a larger size should force a copy.
//     array = dtkArray<double>::fromWritableRawData(contents, 6);
//     array.reserve(7);
//     QCOMPARE(array.size(), 6);
//     QVERIFY(array.capacity() >= 7);
//     QVERIFY(array.constRawData() != contents);
//     for (int index = 0; index < 6; ++index)
//         QCOMPARE(array.at(index), contentsModified[index]);
// }

// void dtkArrayTestCase::testSearch(void)
// {
//     dtkArray<double> array;
//     for (int index = 0; index < 1000; ++index)
//         array.append(double(index));

//     QCOMPARE(array.indexOf(0.0), 0);
//     QCOMPARE(array.indexOf(10.0), 10);
//     QCOMPARE(array.indexOf(999.0), 999);
//     QCOMPARE(array.indexOf(1000.0), -1);
//     QCOMPARE(array.indexOf(10.0, 9), 10);
//     QCOMPARE(array.indexOf(10.0, 10), 10);
//     QCOMPARE(array.indexOf(10.0, 11), -1);
//     QCOMPARE(array.indexOf(999.0, -1), 999);
//     QCOMPARE(array.indexOf(998.0, -1), -1);
//     QCOMPARE(array.indexOf(998.0, -2), 998);
//     QCOMPARE(array.indexOf(998.0, -3), 998);
//     QCOMPARE(array.indexOf(998.0, -2000), 998);
//     QCOMPARE(array.indexOf(998.0, 2000), -1);

//     QCOMPARE(array.lastIndexOf(0.0), 0);
//     QCOMPARE(array.lastIndexOf(10.0), 10);
//     QCOMPARE(array.lastIndexOf(999.0), 999);
//     QCOMPARE(array.lastIndexOf(1000.0), -1);
//     QCOMPARE(array.lastIndexOf(10.0, 9), -1);
//     QCOMPARE(array.lastIndexOf(10.0, 10), 10);
//     QCOMPARE(array.lastIndexOf(10.0, 11), 10);
//     QCOMPARE(array.lastIndexOf(999.0, -1), 999);
//     QCOMPARE(array.lastIndexOf(998.0, -1), 998);
//     QCOMPARE(array.lastIndexOf(998.0, -2), 998);
//     QCOMPARE(array.lastIndexOf(998.0, -3), -1);
//     QCOMPARE(array.lastIndexOf(998.0, -2000), -1);
//     QCOMPARE(array.lastIndexOf(998.0, 2000), 998);

//     QVERIFY(array.contains(0.0));
//     QVERIFY(array.contains(10.0));
//     QVERIFY(array.contains(999.0));
//     QVERIFY(!array.contains(1000.0));
//     QVERIFY(!array.contains(-1.0));

//     array.append(500.0);
//     QCOMPARE(array.count(0.0), 1);
//     QCOMPARE(array.count(10.0), 1);
//     QCOMPARE(array.count(500.0), 2);
//     QCOMPARE(array.count(999.0), 1);
//     QCOMPARE(array.count(1000.0), 0);

//     QVERIFY(array.startsWith(0.0));
//     QVERIFY(!array.startsWith(1.0));

//     QVERIFY(array.endsWith(500.0));
//     QVERIFY(!array.endsWith(1.0));

//     QCOMPARE(array.first(), 0.0);
//     QCOMPARE(array.last(), 500.0);
// }

// void dtkArrayTestCase::testFill(void)
// {
//     dtkArray<double> array;
//     array.fill(1.0);
//     QCOMPARE(array.size(), 0);

//     array.fill(1.0, 100);
//     QCOMPARE(array.size(), 100);
//     for (int index = 0; index < 100; ++index)
//         QCOMPARE(array.at(index), 1.0);

//     array.fill(2.0);
//     QCOMPARE(array.size(), 100);
//     for (int index = 0; index < 100; ++index)
//         QCOMPARE(array.at(index), 2.0);

//     array.fill(3.0, 20);
//     QCOMPARE(array.size(), 20);
//     for (int index = 0; index < 20; ++index)
//         QCOMPARE(array.at(index), 3.0);
// }

// void dtkArrayTestCase::testZeroPrealloc(void)
// {
//     // Check that the zero-prealloc case actually uses less memory
//     // by optimizing away the m_prealloc structure.
//     dtkArray<double, 0> array;
//     dtkArray<double, 1> array2;
//     QVERIFY(sizeof(array) < sizeof(array2));

//     // Check that zero-prealloc arrays act properly by expanding the
//     // template on functions that involve preallocation operations.
//     QVERIFY(array.isEmpty());
//     QCOMPARE(array.size(), 0);
//     QCOMPARE(array.capacity(), 0);
//     QVERIFY(!array.constRawData()); // Will be null for PreallocSize == 0.
//     array.append(1.0);
//     QCOMPARE(array.size(), 1);
//     QCOMPARE(array[0], 1.0);
//     dtkArray<double, 0> array3(array);
//     QVERIFY(array.constRawData() == array3.constRawData());

//     dtkArray<double, 0> array4(100, 3.0);
//     QCOMPARE(array4.size(), 100);
//     for (int index = 0; index < 100; ++index)
//         QCOMPARE(array4[index], 3.0);
//     array4.clear();
//     QCOMPARE(array4.size(), 0);
// }

// void dtkArrayTestCase::testExceptions(void)
// {
// #ifndef QT_NO_EXCEPTIONS

//     // Check that an exception thrown during append() will leave
//     // the array in the pre-append state.
//     dtkArray<ComplexValue> array;
//     try {
//         array.append(ComplexValue(42, ComplexValue::ThrowOnCopy));
//         QFAIL("should not be able to append - A");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 0);
//     }
//     try {
//         array.append(ComplexValue(42, ComplexValue::ThrowOnCopy), ComplexValue(24));
//         QFAIL("should not be able to append - B");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 0);
//     }
//     try {
//         array.append(ComplexValue(24), ComplexValue(42, ComplexValue::ThrowOnCopy));
//         QFAIL("should not be able to append - C");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 1);
//         QCOMPARE(array.at(0).value(), 24);
//     }
//     array.clear();
//     try {
//         array.append(ComplexValue(42, ComplexValue::ThrowOnCopy),
//                      ComplexValue(24),
//                      ComplexValue(16));
//         QFAIL("should not be able to append - D");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 0);
//     }
//     try {
//         array.append(ComplexValue(24),
//                      ComplexValue(42, ComplexValue::ThrowOnCopy),
//                      ComplexValue(16));
//         QFAIL("should not be able to append - E");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 1);
//         QCOMPARE(array.at(0).value(), 24);
//     }
//     array.clear();
//     try {
//         array.append(ComplexValue(24),
//                      ComplexValue(16),
//                      ComplexValue(42, ComplexValue::ThrowOnCopy));
//         QFAIL("should not be able to append - F");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 2);
//         QCOMPARE(array.at(0).value(), 24);
//         QCOMPARE(array.at(1).value(), 16);
//     }
//     array.clear();
//     try {
//         array.append(ComplexValue(42, ComplexValue::ThrowOnCopy),
//                      ComplexValue(24),
//                      ComplexValue(82),
//                      ComplexValue(16));
//         QFAIL("should not be able to append - G");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 0);
//     }
//     try {
//         array.append(ComplexValue(24),
//                      ComplexValue(42, ComplexValue::ThrowOnCopy),
//                      ComplexValue(82),
//                      ComplexValue(16));
//         QFAIL("should not be able to append - H");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 1);
//         QCOMPARE(array.at(0).value(), 24);
//     }
//     array.clear();
//     try {
//         array.append(ComplexValue(24),
//                      ComplexValue(16),
//                      ComplexValue(42, ComplexValue::ThrowOnCopy),
//                      ComplexValue(82));
//         QFAIL("should not be able to append - I");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 2);
//         QCOMPARE(array.at(0).value(), 24);
//         QCOMPARE(array.at(1).value(), 16);
//     }
//     array.clear();
//     try {
//         array.append(ComplexValue(24),
//                      ComplexValue(16),
//                      ComplexValue(82),
//                      ComplexValue(42, ComplexValue::ThrowOnCopy));
//         QFAIL("should not be able to append - J");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 3);
//         QCOMPARE(array.at(0).value(), 24);
//         QCOMPARE(array.at(1).value(), 16);
//         QCOMPARE(array.at(2).value(), 82);
//     }
//     array.clear();
//     ComplexValue values[] = {
//         ComplexValue(1),
//         ComplexValue(2),
//         ComplexValue(3, ComplexValue::ThrowOnCopy)
//     };
//     try {
//         array.append(values, 3);
//         QFAIL("should not be able to append - K");
//     } catch (ComplexValueException *e) {
//         delete e;
//         QCOMPARE(array.size(), 2);
//         QCOMPARE(array.at(0).value(), 1);
//         QCOMPARE(array.at(1).value(), 2);
//     }

// #endif
// }

// void dtkArrayTestCase::testDataStream(void)
// {
// #ifndef QT_NO_DATASTREAM
//     dtkArray<double> array;
//     for (int index = 0; index < 1024; ++index)
//         array.append(double(index));

//     QByteArray data;
//     {
//         QDataStream stream(&data, QIODevice::WriteOnly);
//         stream << array;
//     }

//     dtkArray<double> array2;
//     {
//         QDataStream stream2(data);
//         stream2 >> array2;
//     }

//     QVERIFY(array == array2);
// #endif
// }

DTKTEST_MAIN_NOGUI(dtkArrayTest, dtkArrayTestCase)

// ///////////////////////////////////////////////////////////////////
// Credits
// ///////////////////////////////////////////////////////////////////

/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
