/* dtkArrayTest.h ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Jul 23 08:31:17 2013 (+0200)
 */

/* Change Log:
 *
 */

#pragma once

#include <dtkTest>

class dtkArrayTestCase : public QObject
{
    Q_OBJECT

public:
             dtkArrayTestCase(void);
    virtual ~dtkArrayTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreate(void);
    void testCopyAndAssignement(void);
    void testAppend(void);
    void testAppendTwoAtATime(void);
    void testAppendThreeAtATime(void);
    void testAppendFourAtATime(void);
    void testAppendArray(void);
    void testSetAt(void);
    void testValue(void);
    void testReplace(void);
    void testResize(void);
    void testReserve(void);
    void testSqueeze(void);
    void testCompare(void);
    void testRemove(void);
    void testRemoveFirstLast(void);
    void testReverse(void);
    void testReversed(void);
    void testMid(void);
    void testLeft(void);
    void testRight(void);
    void testIterate(void);
    void testCopyPrealloc(void);
    void testInsert(void);
    void testSetRawData(void);
    void testFromRawData(void);
    void testFromWritableRawData(void);
    void testSearch(void);
    void testFill(void);
    void testZeroPrealloc(void);
    void testDataStream(void);
    void testDynamicArray(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
