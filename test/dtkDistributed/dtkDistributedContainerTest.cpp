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
<<<<<<< Updated upstream
#include <dtkDistributed/dtkDistributedPolicy.h>
#include <dtkDistributed/dtkDistributedWork.h>
#include <dtkDistributed/dtkDistributedWorker.h>
#include <dtkDistributed/dtkDistributedWorkerManager.h>
=======
#include <dtkDistributed/dtkDistributedArray.h>
#include <dtkDistributed/dtkDistributedArrayHandler.h>
>>>>>>> Stashed changes

class myWork : public dtkDistributedWork
{
    myWork *clone(void) {return new myWork(*this); };

    void run(void)
        {
            qDebug()<< "run!!!!";
            qlonglong N = 10000000;

<<<<<<< Updated upstream
            qlonglong sum = 0;
            for (qlonglong i = 0; i < N; ++i)
                sum += 2*i;

            dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();

            QTime time, maintime;
            maintime.start();
            time.start();

            dtkDistributedContainer<qlonglong>& c = *(new dtkDistributedContainer<qlonglong>(N,dtkDistributedWork::worker() ));

            QVERIFY(N == c.size());

            qDebug()<< "allocation time:" <<time.elapsed() << "ms"; time.restart();
            DTK_DISTRIBUTED_BEGIN_LOCAL

            dtkDistributedLocalIterator<qlonglong>& it  = c.localIterator();

            // Fill the container in parallel
            while(it.hasNext()) {
                c.setLocal(it.index(), it.globalIndex());
                it.next();
            }

            comm->barrier();

            it.toFront();

            // Do the computation in parallel
            while(it.hasNext()) {
                c.setLocal(it.index(),  2 * it.peekNext() );
                it.next();
            }

            // it.toFront();
            // while(it.hasNext()) {
            //     qDebug() << dtkDistributedWork::worker()->wid() << it.index() << it.peekNext();
            //     it.next();
            // }

            comm->barrier();

            qlonglong check_sum = 0;

            dtkDistributedContainer<qlonglong>& partial_sum = *(new dtkDistributedContainer<qlonglong>(dtkDistributedWork::worker()->wct(), dtkDistributedWork::worker() ));

            dtkDistributedIterator<qlonglong>& it_partial  = partial_sum.iterator();
            comm->barrier();
            it.toFront();

            // Do the partial sum in parallel, and put the result in a parallel container (of size = number of process/threads)
            while(it.hasNext()) {
                check_sum += c.localAt(it.index());
                it.next();
            }
            partial_sum.setLocal(0,check_sum);

            DTK_DISTRIBUTED_END_LOCAL

            DTK_DISTRIBUTED_BEGIN_GLOBAL

            // Sum the partial sums in sequential mode
            check_sum = 0;
            while(it_partial.hasNext()) {

                check_sum += partial_sum.at(it_partial.index());
                it_partial.next();
            }

            qDebug() << "TOTAL SUM" << check_sum << sum << maintime.elapsed() << "ms";
            QVERIFY(sum == check_sum);

            DTK_DISTRIBUTED_END_GLOBAL

            delete &c;
            delete &partial_sum;
        }
};

void dtkDistributedContainerTestCase::initTestCase(void)
{
    dtkDistributed::communicator::pluginManager().initialize();
}

void dtkDistributedContainerTestCase::init(void)
{
=======
}

void dtkDistributedContainerTestCase::testLocal(void)
{
    // qlonglong N = 11;

    // dtkDistributedCommunicator comm;

    // qlonglong sum = 0;
    // for (qlonglong i = 0; i < N; ++i)
    //     sum += i;

    // dtkDistributedContainer<qlonglong> c = dtkDistributedContainer<qlonglong>(N, &comm);

    // QVERIFY(N == c.size());

    // dtkDistributedLocalIterator<qlonglong>& it  = c.localIterator();

    // while(it.hasNext()) {
    //     c.setLocal(it.localIndex(), it.localIndex());
    //     it.next();
    // }

    // qlonglong check_sum = 0;

    // it.toFront();
    // while(it.hasNext()) {
    //     check_sum += c.localAt(it.localIndex());
    //     it.next();
    // }

    // QVERIFY(sum == check_sum);
}

void dtkDistributedContainerTestCase::testGlobal(void)
{
    // qlonglong N = 11;

    // qlonglong sum = 0;
    // for (qlonglong i = 0; i < N; ++i)
    //     sum += i;

    // dtkDistributedCommunicator comm;

    // dtkDistributedContainer<qlonglong> c = dtkDistributedContainer<qlonglong>(N, &comm);

    // QVERIFY(N == c.size());

    // if (comm.pid() == 0) {

    //     dtkDistributedGlobalIterator<qlonglong>& g_it  = c.globalIterator();
        
    //     while(g_it.hasNext()) {
    //         c.set(g_it.globalIndex(), g_it.globalIndex());
    //         g_it.next();
    //     }
        
    //     qlonglong check_sum = 0;
        
    //     g_it.toFront();
    //     while(g_it.hasNext()) {
    //         check_sum += c.at(g_it.globalIndex());
    //         g_it.next();
    //     }
        
    //     QVERIFY(sum == check_sum);

    // } else {
    //     qDebug() << "OUPS";
    // }
}

void dtkDistributedContainerTestCase::testGlobalLocal(void)
{
    // qlonglong N = 1001;

    // qlonglong sum = 0;
    // for (qlonglong i = 0; i < N; ++i)
    //     sum += 2*i;

    // dtkDistributedCommunicator *comm = dtkDistributed::communicator::pluginFactory().create("mpi");
    
    // dtkDistributedContainer<qlonglong>& c = *(new dtkDistributedContainer<qlonglong>(N, comm));

    // QVERIFY(N == c.size());

    // comm->barrier();
    // if (comm->pid() == 0) {

    //     dtkDistributedGlobalIterator<qlonglong>& g_it  = c.globalIterator();

    //     while(g_it.hasNext()) {
    //         c.set(g_it.globalIndex(), g_it.globalIndex());
    //         g_it.next();
    //     }
    // }
    // comm->barrier();

    // dtkDistributedLocalIterator<qlonglong>& l_it  = c.localIterator();

    // while(l_it.hasNext()) {
    //     c.setLocal(l_it.localIndex(), 2 * l_it.peekNext());
    //     l_it.next();
    // }

    // l_it.toFront();
    // while(l_it.hasNext()) {
    //     qDebug() << comm->pid() << l_it.localIndex() << l_it.peekNext();
    //     l_it.next();
    // }
>>>>>>> Stashed changes

}

<<<<<<< Updated upstream
void dtkDistributedContainerTestCase::testGlobalLocal(void)
{

    dtkDistributedPolicy policy;
    QByteArray numprocs = qgetenv("DTK_NUM_THREADS");
    QByteArray policyEnv   = qgetenv("DTK_DISTRIBUTED_POLICY");
    int np = 2;

    policy.setType(dtkDistributedPolicy::MP);

    if (!numprocs.isEmpty()) {
        np = numprocs.toInt();
        qDebug() << "got num procs from env" << np;
    }
    if (!policyEnv.isEmpty()) {
        qDebug() << "got policy from env" << policyEnv;
        if (QString(policyEnv) == "MT"){
            policy.setType(dtkDistributedPolicy::MT);
        } else if (QString(policyEnv) == "MP") {
            policy.setType(dtkDistributedPolicy::MP);
        } else {
            qDebug() << "unknown policy" << policyEnv;
        }
    }
=======
    // comm->barrier();
    // if (comm->pid() == 0) {

    //     qlonglong check_sum = 0;

    //     dtkDistributedGlobalIterator<qlonglong>& g_it  = c.globalIterator();

    //     while(g_it.hasNext()) {
    //         check_sum += c.at(g_it.globalIndex());
    //         qDebug() << g_it.globalIndex() << g_it.peekNext();
    //         g_it.next();
    //     }

    //     qDebug() << "TOTAL SUM" << check_sum;
    //     QVERIFY(sum == check_sum);
    // }
>>>>>>> Stashed changes

    for (int i=0; i < np; ++i)
        policy.addHost("localhost");

    dtkDistributedWorkerManager manager;
    myWork *work = new myWork();

<<<<<<< Updated upstream
    manager.setPolicy(&policy);
    qDebug() << "spawn";
    manager.spawn(work);
    manager.unspawn();
=======
    // comm->barrier();
    // delete &c;
    // comm->barrier();
    // comm->uninitialize();
    // delete comm;
}

void dtkDistributedContainerTestCase::testFunctor(void)
{
    dtkDistributedArray<qlonglong> array(1001);
    
    array.handler.setLocalMode();
    qDebug() << array.count();

    array.handler.setGlobalMode();
    qDebug() << array.count();

    array.handler.setLocalMode();
    qDebug() << array.count();
>>>>>>> Stashed changes
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)
