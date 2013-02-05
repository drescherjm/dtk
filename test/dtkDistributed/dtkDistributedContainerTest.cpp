/* dtkDistributedContainerTest.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Mon Feb  4 15:37:54 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedContainerTest.h"
#include <dtkDistributed/dtkDistributedContainer.h>

void dtkDistributedContainerTestCase::initTestCase(void)
{

}

void dtkDistributedContainerTestCase::init(void)
{

}

void dtkDistributedContainerTestCase::test(void)
{
    qlonglong N = 10;

    dtkDistributedContainer<qlonglong> c;
    c.resize(N);

    QVERIFY(N == c.size());

    dtkDistributedLocalIterator<qlonglong> *it  = c.localIterator();

    while(it->hasNext()) {
        c.set(it->localIndex(), it->globalIndex());
        qDebug() << it->next();
    }
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{

}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)
