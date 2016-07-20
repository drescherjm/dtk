/* dtkComposerNodeTest.h ---
 *
 * Author: Thibaud Kloczko
 * Created: Wed Apr  3 12:14:41 2013 (+0200)
 * Version:
 * Last-Updated: Thu Apr  4 09:12:07 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 27
 */

/* Change Log:
 *
 */

#pragma once

#include <dtkTest>

class dtkComposerNodeTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testBooleanOperatorBinary_data(void);

private slots:
    void testBoolean(void);
    void testBooleanOperatorUnary(void);
    void testBooleanOperatorBinary(void);

    void testString(void);
    void testStringOperator(void);

    void testNumber(void);
    void testNumberOperatorUnary(void);
    void testNumberOperatorBinary(void);
    void testNumberComparator(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
