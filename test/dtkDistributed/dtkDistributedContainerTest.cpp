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
#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedContainer.h>

void dtkDistributedContainerTestCase::initTestCase(void)
{

}

void dtkDistributedContainerTestCase::init(void)
{

}

void dtkDistributedContainerTestCase::test1(void)
{
    // qlonglong N = 1001;

    // qlonglong sum = 0;
    // for (qlonglong i = 0; i < N; ++i)
    //     sum += i;

    // dtkDistributedContainer<qlonglong> c;
    // c.resize(N);

    // QVERIFY(N == c.size());

    // dtkDistributedLocalIterator<qlonglong>& it  = c.localIterator();

    // while(it.hasNext()) {
    //     c.set(it.globalIndex(), it.localIndex());
    //     it.next();
    // }

    // qlonglong check_sum = 0;

    // it.toFront();
    // while(it.hasNext()) {
    //     check_sum += c.at(it.localIndex());
    //     it.next();
    // }

    // QVERIFY(sum == check_sum);
}

void dtkDistributedContainerTestCase::test2(void)
{
    qlonglong N = 1001;

    dtkDistributedCommunicator comm;

    dtkDistributedContainer<qlonglong> c = dtkDistributedContainer<qlonglong>(N, &comm);

    QVERIFY(N == c.size());

    dtkDistributedGlobalIterator<qlonglong>& g_it  = c.globalIterator();

    while(g_it.hasNext()) {
        c.set(g_it.globalIndex(), g_it.globalIndex());
        g_it.next();
    }

    dtkDistributedLocalIterator<qlonglong>& it  = c.localIterator();

    while(it.hasNext()) {
        c.setLocal(it.localIndex(), 2 * c.localAt(it.localIndex()));
        it.next();
    }
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{

}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)
