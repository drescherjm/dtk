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
            qlonglong N = 2000000;

            qlonglong sum = 0;
            for (qlonglong i = 0; i < N; ++i)
                sum += 2*i;

            dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();

            dtkDistributedContainer<qlonglong>& c = *(new dtkDistributedContainer<qlonglong>(N,dtkDistributedWork::worker() ));

            QVERIFY(N == c.size());

            QTime time, maintime;
            maintime.start();
            time.start();
            dtkDistributed::setMode(dtkDistributed::Global);
            comm->barrier();
            if (dtkDistributedWork::worker()->master()) {
                qDebug() << "first barrier " <<  time.elapsed() << "ms";
                time.restart();
            }
            dtkDistributedIterator<qlonglong>& it  = c.iterator();

            while(it.hasNext()) {
                c.set(it.index(), it.index());
                it.next();
            }

            comm->barrier();

            if (dtkDistributedWork::worker()->master()) {
                qDebug() << "global section:" <<  time.elapsed() << "ms";
                time.restart();
            }
            dtkDistributed::setMode(dtkDistributed::Local);
            it.toFront();

            while(it.hasNext()) {
                c.setLocal(it.index(),  2 * it.peekNext() );
                it.next();
            }

            it.toFront();
            while(it.hasNext()) {
//                qDebug() << dtkDistributedWork::worker()->wid() << it.index() << it.peekNext();
                it.next();
            }


            comm->barrier();
            if (dtkDistributedWork::worker()->master()) {
                qDebug() << "local section:" <<  time.elapsed() << "ms";
                time.restart();
            }
            dtkDistributed::setMode(dtkDistributed::Global);

            qlonglong check_sum = 0;

            it.toFront();

            while(it.hasNext()) {
                check_sum += c.at(it.index());
//                qDebug() << it.index() << it.peekNext();
                it.next();
            }


            if (dtkDistributedWork::worker()->master()) {
                qDebug() << "global section:" <<  time.elapsed() << "ms";
                qDebug() << "TOTAL SUM" << check_sum << maintime.elapsed() << "ms";
                comm->barrier();
                QVERIFY(sum == check_sum);
            } else
                comm->barrier();

            delete &c;

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
