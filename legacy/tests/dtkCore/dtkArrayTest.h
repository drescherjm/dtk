/* dtkArrayTest.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Mon Jul  1 14:08:57 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Jul  1 15:57:25 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 21
 */

/* Change Log:
 * 
 */

#ifndef DTKARRAYTEST_H
#define DTKARRAYTEST_H

#include <dtkCore/dtkTest.h>

//class dtkArrayTestObjectPrivate;

class dtkArrayTestObject : public QObject
{
    Q_OBJECT

public:
             dtkArrayTestObject(void);
    virtual ~dtkArrayTestObject(void);

private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void testCreate(void);
    void testAppend(void);
    void testAppendTwoAtATime(void);
    void testAppendThreeAtATime(void);
    void testAppendFourAtATime(void);
    void testAppendArray(void);
    void testSetAt(void);
    void testValue(void);
    void testReplace(void);
    void testCopy(void);
    void testResize(void);
    void testReserve(void);
    void testSqueeze(void);
    void testCompare(void);
    void testRemove(void);
    void testRemoveFirstLast(void);
    void testExtend(void);
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
    void testExceptions(void);
    void testDataStream(void);

private:
    //dtkArrayTestObjectPrivate *d;
};

#endif

