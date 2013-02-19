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
            qlonglong N = 11;

            qlonglong sum = 0;
            for (qlonglong i = 0; i < N; ++i)
                sum += 2*i;

            dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();

            dtkDistributedContainer<qlonglong>& c = *(new dtkDistributedContainer<qlonglong>(N,dtkDistributedWork::worker() ));

            QVERIFY(N == c.size());

            dtkDistributed::setMode(dtkDistributed::Global);
            comm->barrier();
            dtkDistributedIterator<qlonglong>& it  = c.iterator();

            if (dtkDistributedWork::worker()->wid() == 0) {

                while(it.hasNext()) {
                    c.set(it.index(), it.index());
                    it.next();
                }
            }
            comm->barrier();

            dtkDistributed::setMode(dtkDistributed::Local);
            it.toFront();

            while(it.hasNext()) {
                c.setLocal(it.index(), 2 * it.peekNext());
                it.next();
            }

            it.toFront();
            while(it.hasNext()) {
                qDebug() << dtkDistributedWork::worker()->wid() << it.index() << it.peekNext();
                it.next();
            }


            comm->barrier();
            dtkDistributed::setMode(dtkDistributed::Global);

            qlonglong check_sum = 0;

            it.toFront();

            while(it.hasNext()) {
                check_sum += c.at(it.index());
                qDebug() << it.index() << it.peekNext();
                it.next();
            }


            if (dtkDistributedWork::worker()->master()) {
                qDebug() << "TOTAL SUM" << check_sum;
                QVERIFY(sum == check_sum);
            }


            comm->barrier();
            delete &c;
            comm->barrier();

        }
};

void dtkDistributedContainerTestCase::initTestCase(void)
{
    dtkDistributed::communicator::pluginManager().initialize();
}

void dtkDistributedContainerTestCase::init(void)
{

}

void dtkDistributedContainerTestCase::testGlobalLocalMT(void)
{

    dtkDistributedPolicy policy;
    policy.setType(dtkDistributedPolicy::MT);
    policy.addHost("localhost");
    policy.addHost("localhost");

    dtkDistributedWorkerManager manager;
    myWork *work = new myWork();

    qDebug() << "set policy to MT";
    manager.setPolicy(&policy);
    qDebug() << "spawn";
    manager.spawn(work);
    manager.unspawn();
}

void dtkDistributedContainerTestCase::testGlobalLocalMP(void)
{

    dtkDistributedPolicy policy;
    policy.setType(dtkDistributedPolicy::MP);
    policy.addHost("localhost");
    policy.addHost("localhost");

    dtkDistributedWorkerManager manager;
    myWork *work = new myWork();

    qDebug() << "set policy to MP";
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
