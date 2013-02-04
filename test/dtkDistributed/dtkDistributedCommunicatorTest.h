/* dtkDistributedCommunicatorTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 13:58:16 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb  4 15:53:57 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtkDistributedCommunicatorTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void test1(void);
    void test2(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
