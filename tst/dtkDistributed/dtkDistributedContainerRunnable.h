/* @(#)dtkDistributedContainerRunnable.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/04/17 12:39:15
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <dtkDistributed>
#include <dtkCore>
#include <dtkDistributed/dtkDistributed.h>
#include <dtkDistributed/dtkDistributedGraphTopology.h>
#include <dtkDistributed/dtkDistributedItem.h>

class qvectorWork : public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        qlonglong N = 200;
        QVector<qlonglong> myvector(N);
        for (qlonglong i = 0; i < N; ++i) {
            myvector[i] = i;
        }

        dtkDistributedArray<qlonglong> array(myvector.size(), myvector.data());

        QCOMPARE(myvector.size(), array.size());

        dtkDistributedArray<qlonglong>::iterator it  = array.begin();
        dtkDistributedArray<qlonglong>::iterator ite = array.end();
        for(qlonglong i = 0; it != ite; ++it, ++i) {
            QCOMPARE(myvector.at(array.mapper()->localToGlobal(i, array.wid())), *it);
        }

        comm->barrier();
        if (array.wid() == 1) {
            for (qlonglong i = 0; i < N; ++i) {
                qDebug() << i << array.at(i);
                QCOMPARE(myvector.at(i), array.at(i));
            }
        }
        comm->barrier();
    }
};

class containerWork : public QRunnable
{
public:
    void run(void)
    {
        QTime time;
        qlonglong max= 150;
        dtkDistributedArray<qlonglong> array(max);

        QVERIFY(array.size() == static_cast<qlonglong>(max));

        DTK_DISTRIBUTED_BEGIN_GLOBAL;

        qDebug() << "****** CONTAINER MAPPER TEST ******" ;

        for (qlonglong i = 0; i < array.size(); ++i)
            array.setAt(i, i);

        qDebug() << "init done" ;

        qDebug() << "check mapper";
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        for (qlonglong i = 0; i < comm->size(); ++i) {
            qlonglong start = array.mapper()->firstIndex(i);
            qlonglong end = array.mapper()->lastIndex(i);
            qDebug() << "start end" << i<< start << end;

            for (qlonglong j = start; j <= end; ++j) {
                qDebug() << "owner" << j <<array.mapper()->owner(j) << i;
                QVERIFY(array.mapper()->owner(j) == i);
            }
        }

        qDebug() << array.first() << array.last() << comm->wid();

        for (qlonglong i = 0; i < array.size(); ++i) {
            qlonglong val = array.at(i);
            QVERIFY(val == i);
        }

        DTK_DISTRIBUTED_END_GLOBAL;


        /* DTK_DISTRIBUTED_BEGIN_GLOBAL; */
        /* for (qlonglong i = 0; i < array.count(); ++i) */
        /*     qDebug() << i << array.at(i) << wid(); */
        /* qDebug() << array.first() << array.last() << wid(); */
        /* DTK_DISTRIBUTED_END_GLOBAL; */

        /* DTK_DISTRIBUTED_BEGIN_LOCAL; */
        /* for (qlonglong i = 0; i < array.count(); ++i) */
        /*     array[i] += array.localToGlobal(i); */
        /* DTK_DISTRIBUTED_END_LOCAL; */

        /* DTK_DISTRIBUTED_BEGIN_GLOBAL; */
        /* for (qlonglong i = 0; i < array.count(); ++i) */
        /*     array[i] -= i; */
        /* for (qlonglong i = 0; i < array.count(); ++i) */
        /*     qDebug() << i << array.at(i) << wid(); */
        /* DTK_DISTRIBUTED_END_GLOBAL; */
    }
};

int randInt(int max)
{
    return double(qrand()) / RAND_MAX * max;
}

class sumWork : public QRunnable
{
public:
    void       run(void);
};

void sumWork::run(void)
{
    qDebug() << "run!!!!";

    /* qlonglong N = 50000001; */
    /* qlonglong sum = 0; */

    /* for (qlonglong i = 0; i < N; ++i) */
    /*     sum += 2*i; */

    /* QTime time, maintime; */
    /* maintime.start(); */
    /* time.start(); */

    /* qlonglong check_sum = 0; */

    /* dtkDistributedArray<qlonglong> c(N, this->worker()); */

    /* dtkDistributedArray<qlonglong> partial_sum(wct(), this->worker()); */

    /* QVERIFY(N == c.count()); */

    /* qDebug()<< "allocation time:" << time.elapsed() << "ms"; time.restart(); */

    /* barrier(); */

    /* DTK_DISTRIBUTED_BEGIN_LOCAL; */
    /* qlonglong local_count = c.count(); */
    /* dtkDistributedArray<qlonglong>::iterator c_it  = c.begin(); */
    /* dtkDistributedArray<qlonglong>::iterator c_itb = c.begin(); */
    /* dtkDistributedArray<qlonglong>::iterator c_ite = c.end(); */
    /* while(c_it != c_ite) { */
    /*     *c_it = (2 * c.localToGlobal(c_it-c_itb));  */
    /*     ++c_it; */
    /* } */
    /* for (qlonglong i = 0; i < local_count; ++i) */
    /*     check_sum += c.at(i); */
    /* partial_sum.setAt(0, check_sum); */
    /* DTK_DISTRIBUTED_END_LOCAL; */

    /* DTK_DISTRIBUTED_BEGIN_GLOBAL; */
    /* check_sum = 0; */
    /* dtkDistributedArray<qlonglong>::const_iterator partial_it  = partial_sum.constBegin(); */
    /* dtkDistributedArray<qlonglong>::const_iterator partial_ite = partial_sum.constEnd(); */
    /* while(partial_it != partial_ite) { */
    /*     check_sum += *partial_it++; */
    /* } */
    /* qDebug() << "TOTAL SUM" << check_sum << sum << maintime.elapsed() << "ms"; */
    /* QVERIFY(sum == check_sum); */
    /* DTK_DISTRIBUTED_END_GLOBAL; */
}

class sumItemWork : public QRunnable
{
public:
    void           run(void);
};

void sumItemWork::run(void)
{
    QTime time;
    dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

    int N = 10000001;
    dtkArray<qlonglong> myvector(N);
    qlonglong check_sum = 0;
    for (qlonglong i = 0; i < N; ++i) {
        myvector[i] = i;
        check_sum += i;
    }

    dtkDistributedArray<qlonglong> array(myvector);
    dtkDistributedItem<qlonglong> item(comm);
    item = 0;
    qDebug() << "SUM ITEM TEST" << *item << array.size();
    qlonglong part_sum = 0;

    dtkDistributedArray<qlonglong>::iterator ite = array.begin();
    dtkDistributedArray<qlonglong>::iterator end = array.end();
    for(int i = 0; ite != end; ++ite, ++i) {
        item += *ite;
        part_sum += *ite;
    }

    comm->barrier();
    QVERIFY(*item == check_sum);
    qDebug() << *item << check_sum << part_sum;
}

class graphWork : public QRunnable
{
public:
    void           run(void);
};

void graphWork::run(void)
{
    QTime time;

    int N = 31;
    dtkDistributedGraphTopology graph(N);

    QVector<qlonglong> myvector(N);

    for (qlonglong i = 0; i < N; ++i) {
        myvector[i] = i;
    }

    dtkDistributedArray<qlonglong> array(myvector.size(), myvector.data());
    dtkDistributedArray<qlonglong> max_array(myvector.size(), myvector.data());

    graph.addEdge(0,1);
    graph.addEdge(0,12);
    graph.addEdge(0,13);
    graph.addEdge(1,2);
    graph.addEdge(1,12);
    graph.addEdge(2,12);
    graph.addEdge(2,11);
    graph.addEdge(2,10);
    graph.addEdge(2,3);
    graph.addEdge(3,10);
    graph.addEdge(3,4);
    graph.addEdge(4,10);
    graph.addEdge(4,9);
    graph.addEdge(4,8);
    graph.addEdge(4,5);
    graph.addEdge(5,8);
    graph.addEdge(5,6);
    graph.addEdge(6,8);
    graph.addEdge(6,7);
    graph.addEdge(7,8);
    graph.addEdge(7,20);
    graph.addEdge(8,9);
    graph.addEdge(8,19);
    graph.addEdge(8,20);
    graph.addEdge(9,10);
    graph.addEdge(9,18);
    graph.addEdge(9,19);
    graph.addEdge(10,11);
    graph.addEdge(10,17);
    graph.addEdge(10,18);
    graph.addEdge(11,12);
    graph.addEdge(11,16);
    graph.addEdge(11,17);
    graph.addEdge(12,13);
    graph.addEdge(12,15);
    graph.addEdge(12,16);
    graph.addEdge(13,14);
    graph.addEdge(13,15);
    graph.addEdge(14,15);
    graph.addEdge(14,26);
    graph.addEdge(14,27);
    graph.addEdge(15,16);
    graph.addEdge(15,25);
    graph.addEdge(15,26);
    graph.addEdge(15,28);
    graph.addEdge(16,17);
    graph.addEdge(16,23);
    graph.addEdge(16,24);
    graph.addEdge(16,25);
    graph.addEdge(17,18);
    graph.addEdge(17,22);
    graph.addEdge(17,23);
    graph.addEdge(18,19);
    graph.addEdge(18,21);
    graph.addEdge(18,22);
    graph.addEdge(19,20);
    graph.addEdge(19,21);
    graph.addEdge(20,21);
    graph.addEdge(20,30);
    graph.addEdge(21,22);
    graph.addEdge(21,30);
    graph.addEdge(22,23);
    graph.addEdge(22,24);
    graph.addEdge(22,29);
    graph.addEdge(22,30);
    graph.addEdge(23,24);
    graph.addEdge(24,25);
    graph.addEdge(24,28);
    graph.addEdge(24,29);
    graph.addEdge(25,28);
    graph.addEdge(26,27);
    graph.addEdge(26,28);
    graph.addEdge(27,28);
    graph.addEdge(28,29);
    graph.addEdge(29,30);

    graph.build();

    dtkDistributedGraphTopology::iterator it  = graph.begin();
    dtkDistributedGraphTopology::iterator end = graph.end();

    qDebug() << "compute max";
    for(;it != end; ++it) {

        dtkDistributedGraphTopology::Neighbours n = *it;
        dtkDistributedGraphTopology::Neighbours::iterator nit  = n.begin();
        dtkDistributedGraphTopology::Neighbours::iterator nend = n.end();

        for(;nit != nend; ++nit) {

            dtkDistributedGraphTopology::Neighbours nn = graph[*nit];
            dtkDistributedGraphTopology::Neighbours::iterator nnit  = nn.begin();
            dtkDistributedGraphTopology::Neighbours::iterator nnend = nn.end();

            for(;nnit != nnend; ++nnit) {
                max_array.setAt(it.id(), qMax(max_array.at(it.id()), array.at(*nnit)));
            }
        }
    }

    if (N < 100) {
        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        for (qlonglong i = 0; i < N; ++i) {
            qDebug() << i << max_array.at(i);
        }

        DTK_DISTRIBUTED_END_GLOBAL;
}
    /* qDebug() << " done"; */
}

class graphReadWork : public QRunnable
{
public:
    void           run(void);
};

void graphReadWork::run(void)
{
    QTime time;

    dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

    dtkDistributedGraphTopology graph;

    DTK_DISTRIBUTED_BEGIN_LOCAL;
    QVERIFY(graph.read("../customGraph.graph"));
    DTK_DISTRIBUTED_END_LOCAL;

    qDebug() << "vertex count" << graph.vertexCount();
    qDebug() << "edges count" << graph.edgeCount();

    /* int size = comm->size(); */

    int N = graph.vertexCount();

    QVector<qlonglong> myvector(N);
    for (qlonglong i = 0; i < N; ++i) {
        myvector[i] = i;
    }

    dtkDistributedArray<qlonglong> array(myvector.size(), myvector.data());
    dtkDistributedArray<qlonglong> max_array(myvector.size(), myvector.data());

    dtkDistributedGraphTopology::iterator it  = graph.cbegin();
    dtkDistributedGraphTopology::iterator end = graph.cend();

    qDebug() << "compute max";

    if (array.wid() == 0)
        time.restart();
    // max array will be modified locally, but not accessed remotely, wlock
    max_array.wlock(comm->wid());
    array.rlock();
    graph.rlock();
    qlonglong  current_max;
    for(;it != end; ++it) {

        current_max =0;
        dtkDistributedGraphTopology::Neighbours n = graph[it.id()];
        dtkDistributedGraphTopology::Neighbours::iterator nit  = n.begin();
        dtkDistributedGraphTopology::Neighbours::iterator nend = n.end();

        for(;nit != nend; ++nit) {
            dtkDistributedGraphTopology::Neighbours nn = graph[*nit];
            dtkDistributedGraphTopology::Neighbours::iterator nnit  = nn.begin();
            dtkDistributedGraphTopology::Neighbours::iterator nnend = nn.end();

            for(;nnit != nnend; ++nnit) {
                current_max= qMax(current_max, array.at(*nnit));
            }
        }
        max_array.setAt(it.id(), current_max);
    }
    graph.unlock();
    array.unlock();
    max_array.unlock(comm->wid());

    comm->barrier();
    if (comm->wid() == 0) {
        qDebug() << "max of all vertices done in" << time.elapsed() << "ms";

        graph.stats();
    }

    if (N < 100) {
        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        for (qlonglong i = 0; i < N; ++i) {
            qDebug() << i << max_array.at(i);
        }

        DTK_DISTRIBUTED_END_GLOBAL;
    }
}



namespace communicator_container_test
{
    void runAll(QString type)
    {
        dtkDistributed::policy()->setType(type);

        while (dtkDistributed::policy()->hosts().size() < 2)
            dtkDistributed::policy()->addHost("localhost");

        containerWork work3;
        qvectorWork   work4;
        sumItemWork   work5;
        graphWork     work6;
        graphReadWork work7;

        dtkDistributed::spawn();
        dtkDistributed::exec(&work3);
        dtkDistributed::exec(&work4);
        dtkDistributed::exec(&work5);
        dtkDistributed::exec(&work6);
        dtkDistributed::exec(&work7);
        dtkDistributed::unspawn();

    }
}
