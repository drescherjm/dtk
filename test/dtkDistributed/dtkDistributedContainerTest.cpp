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
#include <dtkDistributed>

void dtkDistributedContainerTestCase::initTestCase(void)
{
    dtkDistributed::communicator::pluginManager().initialize();
}

void dtkDistributedContainerTestCase::init(void)
{

}

void dtkDistributedContainerTestCase::testLocal(void)
{
    qlonglong N = 11;

    dtkDistributedCommunicator comm;

    qlonglong sum = 0;
    for (qlonglong i = 0; i < N; ++i)
        sum += i;

    dtkDistributedContainer<qlonglong> c = dtkDistributedContainer<qlonglong>(N, &comm);

    QVERIFY(N == c.size());

    dtkDistributedLocalIterator<qlonglong>& it  = c.localIterator();

    while(it.hasNext()) {
        c.setLocal(it.localIndex(), it.localIndex());
        it.next();
    }

    qlonglong check_sum = 0;

    it.toFront();
    while(it.hasNext()) {
        check_sum += c.localAt(it.localIndex());
        it.next();
    }

    QVERIFY(sum == check_sum);
}

void dtkDistributedContainerTestCase::testGlobal(void)
{
    qlonglong N = 11;

    qlonglong sum = 0;
    for (qlonglong i = 0; i < N; ++i)
        sum += i;

    dtkDistributedCommunicator comm;

    dtkDistributedContainer<qlonglong> c = dtkDistributedContainer<qlonglong>(N, &comm);

    QVERIFY(N == c.size());

    if (comm.pid() == 0) {

        dtkDistributedGlobalIterator<qlonglong>& g_it  = c.globalIterator();
        
        while(g_it.hasNext()) {
            c.set(g_it.globalIndex(), g_it.globalIndex());
            g_it.next();
        }
        
        qlonglong check_sum = 0;
        
        g_it.toFront();
        while(g_it.hasNext()) {
            check_sum += c.at(g_it.globalIndex());
            g_it.next();
        }
        
        QVERIFY(sum == check_sum);

    } else {
        qDebug() << "OUPS";
    }
}

void dtkDistributedContainerTestCase::testGlobalLocal(void)
{
    qlonglong N = 1001;

    qlonglong sum = 0;
    for (qlonglong i = 0; i < N; ++i)
        sum += 2*i;

    dtkDistributedCommunicator *comm = dtkDistributed::communicator::pluginFactory().create("mpi");
    
    dtkDistributedContainer<qlonglong>& c = *(new dtkDistributedContainer<qlonglong>(N, comm));

    QVERIFY(N == c.size());

    comm->barrier();
    if (comm->pid() == 0) {

        dtkDistributedGlobalIterator<qlonglong>& g_it  = c.globalIterator();

        while(g_it.hasNext()) {
            c.set(g_it.globalIndex(), g_it.globalIndex());
            g_it.next();
        }
    }
    comm->barrier();

    dtkDistributedLocalIterator<qlonglong>& l_it  = c.localIterator();

    while(l_it.hasNext()) {
        c.setLocal(l_it.localIndex(), 2 * l_it.peekNext());
        l_it.next();
    }

    l_it.toFront();
    while(l_it.hasNext()) {
        qDebug() << comm->pid() << l_it.localIndex() << l_it.peekNext();
        l_it.next();
    }


    comm->barrier();
    if (comm->pid() == 0) {

        qlonglong check_sum = 0;

        dtkDistributedGlobalIterator<qlonglong>& g_it  = c.globalIterator();

        while(g_it.hasNext()) {
            check_sum += c.at(g_it.globalIndex());
            qDebug() << g_it.globalIndex() << g_it.peekNext();
            g_it.next();
        }

        qDebug() << "TOTAL SUM" << check_sum;
        QVERIFY(sum == check_sum);
    }


    comm->barrier();
    delete &c;
    comm->barrier();
    comm->uninitialize();
    delete comm;
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)
