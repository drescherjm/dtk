// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <dtkDistributed>

#include <QtCore>

class testBufferManagerCreateDestroy: public QRunnable
{
public:
    void run(void) {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        QVERIFY(buffer_manager);

        comm->destroyBufferManager(buffer_manager);
        QVERIFY(!buffer_manager);
    }
};

class testBufferManagerAllocateDeallocate : public QRunnable
{
public:
    void run(void) {
        qlonglong size = 10001;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();

        qlonglong *array = buffer_manager->allocate<qlonglong>(size);
        QVERIFY(array);

        for (qlonglong i = 0; i < size; ++i) {
            array[i] = i;
        }

        buffer_manager->deallocate(array);
        QVERIFY(!array);

        comm->destroyBufferManager(buffer_manager);
    }
};

class testBufferManagerLocks : public QRunnable
{
public:
    void run(void) {
        qlonglong size = 10001;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        qlonglong *array = buffer_manager->allocate<qlonglong>(size);
        qlonglong wid = comm->wid();

        buffer_manager->rlock(wid);
        QVERIFY(buffer_manager->locked(wid));

        buffer_manager->unlock(wid);
        QVERIFY(!buffer_manager->locked(wid));

        buffer_manager->wlock(wid);
        QVERIFY(buffer_manager->locked(wid));

        buffer_manager->unlock(wid);
        QVERIFY(!buffer_manager->locked(wid));

        buffer_manager->deallocate(array);
        comm->destroyBufferManager(buffer_manager);
    }
};

class testBufferManagerPut : public QRunnable
{
public:
    void run(void) {
        qlonglong N = 10001;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong pu_count = comm->size();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        qlonglong *array = buffer_manager->allocate<qlonglong>(N);
        qlonglong wid = comm->wid();

        comm->barrier();

        if (comm->wid() == 0) {
            for (qlonglong i = 0; i < pu_count * N; ++i) {
                buffer_manager->put(i / N, i % N, &i);
            }
        }

        comm->barrier();

        buffer_manager->rlock(wid);

        for (qlonglong i = 0; i < N; ++i) {
            QCOMPARE(array[i], i + wid * N);
        }

        buffer_manager->unlock(wid);

        buffer_manager->deallocate(array);
        comm->destroyBufferManager(buffer_manager);
    }

};

class testBufferManagerAdd : public QRunnable
{
public:
    void run(void) {
        qlonglong N = 11;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong pu_count = comm->size();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        double *array = buffer_manager->allocate<double>(N);
        qlonglong wid = comm->wid();

        double one = 1;
        comm->barrier();

        if (comm->wid() == 0) {
            for (qlonglong i = 0; i < pu_count * N; ++i) {
                buffer_manager->put(i / N, i % N, &one);
                double val = i;
                buffer_manager->addAssign(i / N, i % N, &val);
            }
        }

        comm->barrier();

        buffer_manager->rlock(wid);

        for (qlonglong i = 0; i < N; ++i) {
            double tmp = i + wid * N + one;
            QCOMPARE(array[i], tmp);
        }

        buffer_manager->unlock(wid);

        buffer_manager->deallocate(array);
        comm->destroyBufferManager(buffer_manager);
    }

};

class testBufferManagerSub : public QRunnable
{
public:
    void run(void) {
        qlonglong N = 11;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong pu_count = comm->size();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        double *array = buffer_manager->allocate<double>(N);
        qlonglong wid = comm->wid();

        double one = 1;
        comm->barrier();

        if (comm->wid() == 0) {
            for (qlonglong i = 0; i < pu_count * N; ++i) {
                buffer_manager->put(i / N, i % N, &one);
                double val = i;
                buffer_manager->subAssign(i / N, i % N, &val);
            }
        }

        comm->barrier();

        buffer_manager->rlock(wid);

        for (qlonglong i = 0; i < N; ++i) {
            double tmp = one - (i + wid * N);
            QCOMPARE(array[i], tmp);
        }

        buffer_manager->unlock(wid);

        buffer_manager->deallocate(array);
        comm->destroyBufferManager(buffer_manager);
    }

};

class testBufferManagerMul : public QRunnable
{
public:
    void run(void) {
        qlonglong N = 11;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong pu_count = comm->size();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        double *array = buffer_manager->allocate<double>(N);
        qlonglong wid = comm->wid();

        double one = 1;
        comm->barrier();

        if (comm->wid() == 0) {
            for (qlonglong i = 0; i < pu_count * N; ++i) {
                buffer_manager->put(i / N, i % N, &one);
                double val = i;
                buffer_manager->mulAssign(i / N, i % N, &val);
            }
        }

        comm->barrier();

        buffer_manager->rlock(wid);

        for (qlonglong i = 0; i < N; ++i) {
            double tmp = i + wid * N;
            QCOMPARE(array[i], tmp);
        }

        buffer_manager->unlock(wid);

        buffer_manager->deallocate(array);
        comm->destroyBufferManager(buffer_manager);
    }

};

class testBufferManagerDiv : public QRunnable
{
public:
    void run(void) {
        qlonglong N = 11;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong pu_count = comm->size();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        double *array = buffer_manager->allocate<double>(N);
        qlonglong wid = comm->wid();

        double one = 1;
        comm->barrier();

        if (comm->wid() == 0) {
            for (qlonglong i = 0; i < pu_count * N; ++i) {
                buffer_manager->put(i / N, i % N, &one);
                double val = i + one;
                buffer_manager->divAssign(i / N, i % N, &val);
            }
        }

        comm->barrier();

        buffer_manager->rlock(wid);

        for (qlonglong i = 0; i < N; ++i) {
            double tmp = one / (one + i + wid * N);
            QCOMPARE(array[i], tmp);
        }

        buffer_manager->unlock(wid);

        buffer_manager->deallocate(array);
        comm->destroyBufferManager(buffer_manager);
    }

};

class testBufferManagerGet : public QRunnable
{
public:
    void run(void) {
        qlonglong N = 10001;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong pu_count = comm->size();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        qlonglong *array = buffer_manager->allocate<qlonglong>(N);
        qlonglong wid = comm->wid();

        for (qlonglong i = 0; i < N; ++i) {
            array[i] = i + wid * N;
        }

        comm->barrier();

        if (comm->wid() == 0) {
            qlonglong temp;

            for (qlonglong i = 0; i < N * pu_count; ++i) {
                buffer_manager->get(i / N, i % N, &temp);
                QCOMPARE(temp, i);
            }
        }

    }
};

class testBufferManagerLockGetUnlock : public QRunnable
{
public:
    void run(void) {
        qlonglong N = 10001;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        dtkDistributedBufferManager *buffer_manager = comm->createBufferManager();
        qlonglong *array = buffer_manager->allocate<qlonglong>(N);
        qlonglong wid = comm->wid();

        for (qlonglong i = 0; i < N; ++i) {
            array[i] = i + wid * N;
        }

        comm->barrier();
        buffer_manager->rlock(wid);
        qlonglong temp;

        for (qlonglong i = 0; i < N; ++i) {
            qlonglong global_id = i + wid * N;
            buffer_manager->get(wid, i, &temp);
            QCOMPARE(temp, global_id);
        }

        buffer_manager->unlock(wid);
    }
};


class testBufferManagerPerf : public QRunnable
{
public:
    void run(void) {
        /* QTime time; */

        /* qlonglong N = 1000001; */
        /* dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();    */
        /* qlonglong pu_count = comm->size();     */
        /* qlonglong wid = comm->wid(); */

        /* { */
        /*     comm->barrier(); */
        /*     dtkDistributedBufferManager *buffer_manager = comm->createBufferManager(); */


        /*     qlonglong *array = buffer_manager->allocate<qlonglong>(N); */

        /*     comm->barrier(); */
        /*     if (comm->wid() == 0) { */
        /*         time.restart(); */
        /*         for(qlonglong i = 0; i < pu_count * N; ++i) { */
        /*             buffer_manager->put(i/N, i%N, &i); */
        /*         } */
        /*         qDebug() << "put time =" << time.elapsed() << "ms"; */
        /*     } */
        /*     comm->barrier(); */

        /*     buffer_manager->rlock(wid); */
        /*     for(qlonglong i = 0; i < N; ++i) { */
        /*         QCOMPARE(array[i], i + wid * N); */
        /*     } */
        /*     buffer_manager->unlock(wid); */

        /*     buffer_manager->deallocate(array); */
        /*     comm->destroyBufferManager(buffer_manager); */
        /* }         */

        /* comm->barrier();    */
    }
};

//
// dtkDistributedBufferManagerRunnable.h ends here
