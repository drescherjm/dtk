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
    qlonglong N = 1000;

    qlonglong sum = 0;
    for (qlonglong i = 0; i < N; ++i)
        sum += i;

    dtkDistributedContainer<qlonglong> c;
    c.resize(N);

    QVERIFY(N == c.size());

    dtkDistributedLocalIterator<qlonglong> *it  = c.localIterator();

    while(it->hasNext()) {
        c.set(it->globalIndex(), it->localIndex());
        it->next();
    }

    qlonglong check_sum = 0;

    it->toFront();
    while(it->hasNext()) {
        check_sum += c.at(it->localIndex());
        it->next();
    }

    QVERIFY(sum == check_sum);
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{

}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)
