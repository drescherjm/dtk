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
        dtkDistributedArray<qlonglong> array(11, dtkDistributedWork::worker());

        // ---
        DTK_DISTRIBUTED_BEGIN_LOCAL;

        for (qlonglong i = 0; i < array.count(); ++i)
            array.setAt(i, array.localToGlobal(i));

        qDebug() << array.first() << array.last() << wid();

        DTK_DISTRIBUTED_END_LOCAL;

        // ---
        DTK_DISTRIBUTED_BEGIN_GLOBAL;

        for (qlonglong i = 0; i < array.count(); ++i)
            qDebug() << i << array.at(i) << wid();

        qDebug() << array.first() << array.last() << wid();

        DTK_DISTRIBUTED_END_GLOBAL;

        DTK_DISTRIBUTED_BEGIN_LOCAL;

        for (qlonglong i = 0; i < array.count(); ++i)
            array[i] += array.localToGlobal(i);

        DTK_DISTRIBUTED_END_LOCAL;

        DTK_DISTRIBUTED_BEGIN_GLOBAL;

        for (qlonglong i = 0; i < array.count(); ++i)
            array[i] -= i;

        for (qlonglong i = 0; i < array.count(); ++i)
            qDebug() << i << array.at(i) << wid();

        DTK_DISTRIBUTED_END_GLOBAL;
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

    dtkDistributedCommunicator *comm = dtkDistributedWork::worker()->communicator();

    QTime time, maintime;
    maintime.start();
    time.start();

    DTK_DISTRIBUTED_BEGIN_LOCAL;
    dtkDistributedArray<qlonglong>::iterator it  = c.begin();
    dtkDistributedArray<qlonglong>::iterator ite = c.end();
    qsrand(wid());
    while(it != ite) {
        *it++ = randInt(N);
    }
    DTK_DISTRIBUTED_END_LOCAL;

    DTK_DISTRIBUTED_BEGIN_GLOBAL;
    dtkDistributedArray<qlonglong>::const_iterator it  = c.cbegin();
    dtkDistributedArray<qlonglong>::const_iterator itb = c.cbegin();
    dtkDistributedArray<qlonglong>::const_iterator ite = c.cend();
    while(it != ite)
        qDebug() << it-itb << *it++;    
    DTK_DISTRIBUTED_END_GLOBAL;
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

    qlonglong N = 500000001;
    qlonglong sum = 0;

    for (qlonglong i = 0; i < N; ++i)
        sum += 2*i;

    QTime time, maintime;
    maintime.start();
    time.start();

    qlonglong check_sum = 0;

    dtkDistributedArray<qlonglong> c(N, dtkDistributedWork::worker());

    dtkDistributedArray<qlonglong> partial_sum(wct(), dtkDistributedWork::worker() );

    QVERIFY(N == c.count());

    qDebug()<< "allocation time:" << time.elapsed() << "ms"; time.restart();

    barrier();

    DTK_DISTRIBUTED_BEGIN_LOCAL;
    // Do the computation in parallel
    qlonglong local_count = c.count();
    dtkDistributedArray<qlonglong>::iterator c_it  = c.begin();
    dtkDistributedArray<qlonglong>::iterator c_itb = c.begin();
    dtkDistributedArray<qlonglong>::iterator c_ite = c.end();
    while(c_it != c_ite) {
        *c_it = (2 * c.localToGlobal(c_it-c_itb)); 
        ++c_it;
    }
    // Do the partial sum in parallel, and put the result in a parallel container (of size = number of process/threads)
    for (qlonglong i = 0; i < local_count; ++i)
        check_sum += c.at(i);
    partial_sum.setAt(0, check_sum);

    DTK_DISTRIBUTED_END_LOCAL;

    DTK_DISTRIBUTED_BEGIN_GLOBAL;
    // Sum the partial sums in sequential mode
    check_sum = 0;
    dtkDistributedArray<qlonglong>::const_iterator partial_it  = partial_sum.constBegin();
    dtkDistributedArray<qlonglong>::const_iterator partial_ite = partial_sum.constEnd();
    while(partial_it != partial_ite) {
        check_sum += *partial_it++;
    }
    qDebug() << "TOTAL SUM" << check_sum << sum << maintime.elapsed() << "ms";

    QVERIFY(sum == check_sum);
    DTK_DISTRIBUTED_END_GLOBAL;
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

    manager.exec(work2);

    manager.exec(work3);

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
