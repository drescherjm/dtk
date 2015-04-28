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

class testArrayCreateDestroy: public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 21;

        dtkDistributedArray<qlonglong> *array = new dtkDistributedArray<qlonglong>(N);
        QVERIFY(!array->empty());
        QCOMPARE(array->size(), N);

        delete array;

        dtkDistributedMapper *mapper = new dtkDistributedMapper;
        array = new dtkDistributedArray<qlonglong>(N, mapper);
        QVERIFY(!array->empty());
        QCOMPARE(array->size(), N);
        QCOMPARE(array->mapper(), mapper);


        dtkDistributedArray<qlonglong> *copy = new dtkDistributedArray<qlonglong>(*array);
        QVERIFY(!copy->empty());
        QVERIFY(!array->empty());
        QCOMPARE(copy->size(), N);
        QCOMPARE(copy->mapper(), mapper);

        delete array;
        delete copy;

        array = new dtkDistributedArray<qlonglong>(N, -1);
        QVERIFY(!array->empty());
        QCOMPARE(array->size(), N);

        delete array;

        qlonglong *input = new qlonglong[N];
        for (int i = 0; i < N; ++i)
            input[i] = i;

        array = new dtkDistributedArray<qlonglong>(N, input);
        QVERIFY(!array->empty());
        QCOMPARE(array->size(), N);

        delete array;
        delete[] input;
    }
};

class testArrayAtFirstLast : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 67;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        qlonglong *input = new qlonglong[N];
        for (int i = 0; i < N; ++i)
            input[i] = i;

        dtkDistributedArray<qlonglong> array(N, input);

        for(int i = 0; i < comm->size(); ++i) {
            if (comm->wid() == i) {
                QCOMPARE(array.first(), input[0]);
                for (int j = 0; j < N; ++j) {
                    QCOMPARE(array.at(j), input[j]);
                }
                QCOMPARE(array.last(), input[N-1]);
            }
            comm->barrier();
        }

        delete[] input;
        comm->barrier();
    }
};

class testArrayFill : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 67;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        qlonglong input = 52687;

        dtkDistributedArray<qlonglong> array(N, input);

        for(int i = 0; i < comm->size(); ++i) {
            if (comm->wid() == i) {
                for (int j = 0; j < N; ++j) {
                    QCOMPARE(array.at(j), input);
                }
            }
            comm->barrier();
        }
        comm->barrier();
    }
};

class testArrayOperatorGet : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 107;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        qlonglong *input = new qlonglong[N];
        for (int i = 0; i < N; ++i)
            input[i] = i;

        dtkDistributedArray<qlonglong> array(N, input);

        for(int i = 0; i < comm->size(); ++i) {
            if (comm->wid() == i) {
                for (int j = 0; j < N; ++j) {
                    QCOMPARE(array[j], input[j]);
                }
            }
            comm->barrier();
        }

        delete[] input;
    }
};

class testArraySetAt : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 107;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        qlonglong *input = new qlonglong[N];
        for (int i = 0; i < N; ++i)
            input[i] = i;

        dtkDistributedArray<qlonglong> array(N);

        for(int i = 0; i < comm->size(); ++i) {
            if (comm->wid() == i) {
                for (int j = 0; j < N; ++j) {
                    array.setAt(j, input[j]);
                }
                for (int j = 0; j < N; ++j) {
                    QCOMPARE(array[j], input[j]);
                }
            }
            comm->barrier();
        }

        array.fill(0);
        comm->barrier();

        if (comm->wid() == 0) {
            array.setAt(0, input, N);
        }
        for(int i = 0; i < comm->size(); ++i) {
            if (comm->wid() == i) {
                for (int j = 0; j < N; ++j) {
                    QCOMPARE(array[j], input[j]);
                }
            }
            comm->barrier();
        }

        delete[] input;
    }
};

class testArrayIterator : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 16257;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        qlonglong *input = new qlonglong[N];
        for (int i = 0; i < N; ++i)
            input[i] = i;

        dtkDistributedArray<qlonglong> array(N, input);

        dtkDistributedArray<qlonglong>::iterator ite = array.begin();
        dtkDistributedArray<qlonglong>::iterator end = array.end();
        for(int i = 0; ite != end; ++ite, ++i) {
            QCOMPARE(*ite, input[array.mapper()->localToGlobal(i, comm->wid())]);
        }

        dtkDistributedArray<qlonglong>::const_iterator cite = array.cbegin();
        dtkDistributedArray<qlonglong>::const_iterator cend = array.cend();
        for(int i = 0; cite != cend; ++cite, ++i) {
            QCOMPARE(*cite, input[array.mapper()->localToGlobal(i, comm->wid())]);
        }

        for(int i = 0; ite != end; ++ite, ++i) {
            *ite += i;
            QCOMPARE(*ite, input[array.mapper()->localToGlobal(i, comm->wid())] + i);
        }

        delete[] input;
            comm->barrier();
    }
};

class testArrayRemap : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 200;
        qlonglong pu_size = dtkDistributed::app()->communicator()->size();

        dtkDistributedArray<qlonglong> array(N);

        qlonglong local_size = array.mapper()->count(dtkDistributed::app()->communicator()->wid());
        dtkDistributedMapper *mapper = new dtkDistributedMapper;
        mapper->initMap(N, pu_size);
        qlonglong offset = 0;
        for(int i = 0; i < pu_size; ++i) {
            mapper->setMap(offset, i);
            offset += (local_size + i);
        }

        array.remap(mapper);

        qlonglong distance = std::distance(array.begin(), array.end());
        local_size = array.mapper()->count(dtkDistributed::app()->communicator()->wid());
        QCOMPARE(distance, local_size);
    }
};

class testArrayCopyIntoArray : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 107;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        qlonglong *input = new qlonglong[N];
        for (int i = 0; i < N; ++i)
            input[i] = i;

        dtkDistributedArray<qlonglong> array(N, input);

        if (comm->wid() == 0) {
            for(int i = 0; i < comm->size(); ++i) {
                qlonglong size = array.mapper()->count(i);
                qlonglong fid = array.mapper()->firstIndex(i);

                qlonglong *output = new qlonglong[size];
                array.copyIntoArray(fid, output, size);
                for (int j = 0; j < size; ++j) {
                    QCOMPARE(array[fid + j], output[j]);
                }
                delete[] output;
            }
        }
        comm->barrier();
        
        delete[] input;
        }
};

class testArrayToNavigator : public QRunnable
{
public:
    void run(void)
    {
        qlonglong N = 107;
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        qlonglong *input = new qlonglong[N];
        for (int i = 0; i < N; ++i)
            input[i] = i;

        dtkDistributedArray<qlonglong> array(N, input);

        if (comm->wid() == 0) {
            dtkDistributedArray<qlonglong>::navigator nav = array.toNavigator();
            dtkDistributedArray<qlonglong>::navigator::iterator ite = nav.begin();
            dtkDistributedArray<qlonglong>::navigator::iterator end = nav.end();
            for(qlonglong i = 0; ite != end; ++i, ++ite) {
                QCOMPARE(*ite, input[i]);
            }
        }
        comm->barrier();

        delete[] input;

        dtkDistributedArray<qlonglong>::navigator nav = array.toNavigator();
        nav.setRange(array.mapper()->firstIndex(comm->wid()), array.mapper()->count(comm->wid()));

        dtkDistributedArray<qlonglong>::navigator::iterator nite = nav.begin();
        dtkDistributedArray<qlonglong>::navigator::iterator nend = nav.end();

        dtkDistributedArray<qlonglong>::iterator ite = array.begin();

        for(; nite != nend; ++nite, ++ite) {
            QCOMPARE(*nite, *ite);
        }
    }
};


//
// dtkDistributedArrayRunnable.h ends here
