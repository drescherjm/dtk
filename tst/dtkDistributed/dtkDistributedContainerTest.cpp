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
#include <dtkDistributed/dtkDistributedArray.h>
#include <dtkDistributed/dtkDistributedPolicy.h>
#include <dtkDistributed/dtkDistributedWork.h>
#include <dtkDistributed/dtkDistributedWorker.h>
#include <dtkDistributed/dtkDistributedWorkerManager.h>

class containerWork : public dtkDistributedWork
{
    containerWork *clone(void) { return new containerWork(*this); };

    void run(void)
    {
        QTime time;
        dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();
        dtkDistributedArray<qlonglong> array(11, dtkDistributedWork::worker());
        
        // ---
        DTK_DISTRIBUTED_BEGIN_LOCAL
        
        for (qlonglong i = 0; i < array.count(); ++i)
            array.set(i, array.localToGlobal(i));
        
        qDebug() << array.first() << array.last() << dtkDistributedWork::worker()->wid();
        
        DTK_DISTRIBUTED_END_LOCAL

        // ---
        DTK_DISTRIBUTED_BEGIN_GLOBAL

        for (qlonglong i = 0; i < array.count(); ++i)
            qDebug() << i << array.at(i) << dtkDistributedWork::worker()->wid();

        qDebug() << array.first() << array.last() << dtkDistributedWork::worker()->wid();

        DTK_DISTRIBUTED_END_GLOBAL
            
        DTK_DISTRIBUTED_BEGIN_LOCAL
            
        for (qlonglong i = 0; i < array.count(); ++i)
            array[i] += array.localToGlobal(i);
        
        DTK_DISTRIBUTED_END_LOCAL

        DTK_DISTRIBUTED_BEGIN_GLOBAL
        
        for (qlonglong i = 0; i < array.count(); ++i)
            array[i] -= i;
        
        for (qlonglong i = 0; i < array.count(); ++i)
            qDebug() << i << array.at(i) << dtkDistributedWork::worker()->wid();
        
        DTK_DISTRIBUTED_END_GLOBAL
    }
};

class randomWork : public dtkDistributedWork
{

    randomWork *clone(void);
    void        run(void);

};

int randInt(int max)
{
    return double(qrand()) / RAND_MAX * max;
}

randomWork *randomWork::clone(void)
{
    return new randomWork(*this);
}

void randomWork::run(void)
{
    qlonglong N = 20;

    dtkDistributedArray<qlonglong> c(N, dtkDistributedWork::worker());
    c.m_handler->setGlobalMode();

    dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();

    QTime time, maintime;
    maintime.start();
    time.start();

    DTK_DISTRIBUTED_BEGIN_LOCAL

    dtkDistributedIterator<qlonglong> it  = c.iterator();

    qsrand(dtkDistributedWork::worker()->wid());

    while(it.hasNext()) {
        c.set(it.index(), randInt(N));
        it.toNext();
    }

    qlonglong np = dtkDistributedWork::worker()->wct();

    DTK_DISTRIBUTED_END_LOCAL

    DTK_DISTRIBUTED_BEGIN_GLOBAL

    dtkDistributedIterator<qlonglong> it  = c.iterator();

    it.toFirst();
    while(it.hasNext()) {
        qDebug() << it.index() << it.current();
         it.toNext();
    }

    DTK_DISTRIBUTED_END_GLOBAL
}

class sumWork : public dtkDistributedWork
{
public:
    sumWork *clone(void);
    void       run(void);
};

sumWork *sumWork::clone(void)
{
    return new sumWork(*this);
}

void sumWork::run(void)
{
    qDebug()<< "run!!!!";

    qlonglong N = 100000001;
    qlonglong sum = 0;

    for (qlonglong i = 0; i < N; ++i)
        sum += 2*i;

    dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();

    QTime time, maintime;
    maintime.start();
    time.start();

    qlonglong check_sum = 0;

    dtkDistributedArray<qlonglong> c(N, dtkDistributedWork::worker());
    c.m_handler->setGlobalMode();

    dtkDistributedArray<qlonglong> partial_sum(dtkDistributedWork::worker()->wct(), dtkDistributedWork::worker() );
    partial_sum.m_handler->setGlobalMode();

    QVERIFY(N == c.count());

    qDebug()<< "allocation time:" <<time.elapsed() << "ms"; time.restart();

    DTK_DISTRIBUTED_BEGIN_LOCAL
    c.m_handler->setLocalMode();
    partial_sum.m_handler->setLocalMode();

    dtkDistributedIterator<qlonglong> it  = c.iterator();

    // Fill the container in parallel
    while(it.hasNext()) {
        c[it.index()] = c.localToGlobal(it.index());
        it.toNext();
    }

    comm->barrier();

    it.toFirst();

    // Do the computation in parallel
    while(it.hasNext()) {
        c.set(it.index(),  2 * it.current() );
        it.toNext();
    }

    // it.toFirst();
    // while(it.hasNext()) {
    //     qDebug() << dtkDistributedWork::worker()->wid() << it.index() << it.current();
    //     it.toNext();
    // }

    comm->barrier();

    comm->barrier();
    it.toFirst();

    // Do the partial sum in parallel, and put the result in a parallel container (of size = number of process/threads)
    while(it.hasNext()) {
        check_sum += c.at(it.index());
        it.toNext();
    }
    partial_sum.set(0, check_sum);

    DTK_DISTRIBUTED_END_LOCAL

    DTK_DISTRIBUTED_BEGIN_GLOBAL
    c.m_handler->setGlobalMode();
    partial_sum.m_handler->setGlobalMode();

    // Sum the partial sums in sequential mode

    check_sum = 0;

    dtkDistributedIterator<qlonglong> it_partial = partial_sum.iterator();
    while(it_partial.hasNext()) {

        check_sum += partial_sum.at(it_partial.index());
        it_partial.toNext();
    }

    qDebug() << "TOTAL SUM" << check_sum << sum << maintime.elapsed() << "ms";

    QVERIFY(sum == check_sum);

    DTK_DISTRIBUTED_END_GLOBAL
}

void dtkDistributedContainerTestCase::initTestCase(void)
{
    dtkDistributedSettings settings;
    settings.beginGroup("communicator");
    dtkDistributed::communicator::pluginManager().initialize(settings.value("plugins").toString());
    settings.endGroup();
}

void dtkDistributedContainerTestCase::init(void)
{

}

void dtkDistributedContainerTestCase::testAll(void)
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
    sumWork     *work = new    sumWork();
    randomWork *work2 = new randomWork();
    containerWork *work3 = new containerWork();

    manager.setPolicy(&policy);
    qDebug() << "spawn";
    manager.spawn();
    manager.exec(work);

    //manager.exec(work2);

    //manager.exec(work3);

    manager.unspawn();

    qDebug() << "parallel section is over";
}

void dtkDistributedContainerTestCase::cleanupTestCase(void)
{
    dtkDistributed::communicator::pluginManager().uninitialize();
}

void dtkDistributedContainerTestCase::cleanup(void)
{

}

DTKTEST_MAIN_NOGUI(dtkDistributedContainerTest, dtkDistributedContainerTestCase)
