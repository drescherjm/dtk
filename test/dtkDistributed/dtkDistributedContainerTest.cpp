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
#include <dtkDistributed/dtkDistributedPolicy.h>
#include <dtkDistributed/dtkDistributedWork.h>
#include <dtkDistributed/dtkDistributedWorker.h>
#include <dtkDistributed/dtkDistributedWorkerManager.h>

class myWork : public dtkDistributedWork
{
    myWork *clone(void) {return new myWork(*this); };

    void run(void)
        {
            qDebug()<< "run!!!!";
            qlonglong N = 10000000;

            qlonglong sum = 0;
            for (qlonglong i = 0; i < N; ++i)
                sum += 2*i;

            dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();

            dtkDistributedContainer<qlonglong>& c = *(new dtkDistributedContainer<qlonglong>(N,dtkDistributedWork::worker() ));

            QVERIFY(N == c.size());

            QTime time, maintime;
            maintime.start();
            time.start();

            DTK_DISTRIBUTED_BEGIN_LOCAL

            dtkDistributedIterator<qlonglong>& it  = c.iterator();

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
            comm->barrier();

            dtkDistributedIterator<qlonglong>& it_partial  = partial_sum.iterator();
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

}

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

    for (int i=0; i < np; ++i)
        policy.addHost("localhost");

    dtkDistributedWorkerManager manager;
    myWork *work = new myWork();

    manager.setPolicy(&policy);
    qDebug() << "spawn";
    manager.spawn(work);
    manager.unspawn();
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)
