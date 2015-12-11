/* @(#)dtkDistributedCommRunnable.h ---
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
#include <dtkCore/dtkArray.h>

class PingPongWork : public QRunnable
{
public:
    void run(void)
    {
        QTime time;
        /* QByteArray y; */
        /* QByteArray x("ping"); */
        QString x = "ping";
        QString y;

        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        int iter = 10000;

        if (QThread::idealThreadCount() == 1)
            iter = 10;

        qlonglong size = x.size() * iter / 8;

        if (comm->size() <2 ) {
            qWarning() << "only one thread/process, skip PINGPONG test";
            return;
        }

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "****** PINGPONG TEST ******" << iter;
        DTK_DISTRIBUTED_END_GLOBAL;


        DTK_DISTRIBUTED_BEGIN_LOCAL;

        QTime time2; time2.start();
        for (int i =0; i< iter; ++i) {
            for (int source = 0; source < comm->size(); ++source) {
                for (int target = 0; target < comm->size(); ++target) {
                    if (source == target)
                        continue;
                    if (comm->wid() == source) {
                        comm->send(x, target, 0);
                        comm->receive(y, target, 0);
                    }  else if (comm->wid() == target) {
                        comm->receive(y, source, 0);
                        comm->send(y, source, 0);
                    }
                }
            }
        }
        double elapsed = time2.elapsed();
        DTK_DISTRIBUTED_END_LOCAL;

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "throughput" << size/elapsed << "kbits/sec";
        qDebug() << "latency"    << 1000.0 * elapsed / iter << "microsec";
        QVERIFY(y == "ping");
        DTK_DISTRIBUTED_END_GLOBAL;
    }
};


class ReduceWork : public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        int iter = 10000;
        if (QThread::idealThreadCount() == 1)
            iter = 10;
        qlonglong input  = comm->rank()+1;
        qlonglong result = 0;
        qlonglong pu_count = comm->size();

        if (comm->size() <2 ) {
            qWarning() << "only one thread/process, skip REDUCE variant test";
            return;
        }

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "****** Reduce  TEST ******" << iter;
        DTK_DISTRIBUTED_END_GLOBAL;

        QTime time2; time2.start();

        qlonglong product = 1;
        for (int i = 0; i< comm->size(); ++i) {
            product  *= i+1;
        }
        qlonglong sum = comm->size() * (comm->size()+1) / 2;

        for (int i =0; i< iter; ++i) {

            comm->reduce(&input,&result, 1, dtkDistributedCommunicator::Sum,0, false);


            DTK_DISTRIBUTED_BEGIN_GLOBAL;
            QVERIFY(result == sum);
            DTK_DISTRIBUTED_END_GLOBAL;

            comm->reduce(&input,&result, 1, dtkDistributedCommunicator::Max,0, false);
            DTK_DISTRIBUTED_BEGIN_GLOBAL;
            QVERIFY(result == comm->size());
            DTK_DISTRIBUTED_END_GLOBAL;

            comm->reduce(&input,&result, 1, dtkDistributedCommunicator::Min,0, false);
            DTK_DISTRIBUTED_BEGIN_GLOBAL;
            QVERIFY(result == 1);
            DTK_DISTRIBUTED_END_GLOBAL;

            //ALL REDUCE
            comm->reduce(&input,&result, 1, dtkDistributedCommunicator::Sum,0, true);
            QVERIFY(result == sum);

            comm->reduce(&input,&result, 1, dtkDistributedCommunicator::Product,0, true);
            QVERIFY(result == product);

            double a;
            double b;
            if (comm->rank() ==0)
                a=3.14;
            else
                a=1.42;
            comm->reduce(&a,&b, 1, dtkDistributedCommunicator::Min,1, true);
            QVERIFY(b == 1.42);
        }
        double elapsed = time2.elapsed();

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "REDUCE latency"    << 1000.0 * elapsed / (pu_count *iter *4) << "microsec";
        DTK_DISTRIBUTED_END_GLOBAL;

    }
};


class GatherWork : public QRunnable
{
public:
    void run(void)
    {
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        int iter = 10000;
        if (QThread::idealThreadCount() == 1)
            iter = 10;
        qlonglong input  = comm->rank()+1;
        qlonglong * result;
        qlonglong pu_count = comm->size();
        result = static_cast<qlonglong*>(calloc(pu_count,sizeof(qlonglong)));

        if (comm->size() <2 ) {
            qWarning() << "only one thread/process, skip GATHER variant test";
            return;
        }

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "****** Gather  TEST ******" << iter;
        DTK_DISTRIBUTED_END_GLOBAL;

        QTime time2; time2.start();

        qlonglong sum = comm->size() * (comm->size()+1) / 2;

        for (int i =0; i< iter; ++i) {

            comm->gather(&input,result, 1, 0, false);

            DTK_DISTRIBUTED_BEGIN_GLOBAL;
            for (int i = 0; i< comm->size(); ++i) {
                QVERIFY(result[i] == i+1);
            }
            DTK_DISTRIBUTED_END_GLOBAL;

            //ALL GATHER
            comm->gather(&input,result, 1, 0, true);
            for (int i = 0; i< comm->size(); ++i) {
                QVERIFY(result[i] == i+1);
            }

        }
        double elapsed = time2.elapsed();

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "GATHER latency"    << 1000.0 * elapsed / (pu_count *iter *4) << "microsec";
        DTK_DISTRIBUTED_END_GLOBAL;

    }
};



class SendVariantWork : public QRunnable
{
public:
    void run(void)
    {
        QTime time;
        dtkArray<qlonglong> a;
        dtkArray<qlonglong> *b;
        qlonglong arraySize = 1000000;
        a.resize(arraySize);

        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        int iter = 5;
        qlonglong size = a.size() * iter;

        if (comm->size() <2 ) {
            qWarning() << "only one thread/process, skip Send/Receive variant test";
            return;
        }

        for (int i = 0; i< arraySize ; ++i) {
            a[i] = i;
        }

        qRegisterMetaTypeStreamOperators<dtkArray<qlonglong>>("dtkArray<qlonglong>");
        qRegisterMetaTypeStreamOperators<dtkArray<qlonglong> *>("dtkArray<qlonglong>*");
        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "****** SEND/RECEIVE Variant TEST ******" << iter << size;
        DTK_DISTRIBUTED_END_GLOBAL;


        DTK_DISTRIBUTED_BEGIN_LOCAL;

        QTime time2; time2.start();
        int source = 0;
        int target = 1;
        QVariant v;
        if (comm->rank() < 2) {
            for (int i =0; i< iter; ++i) {
                if (comm->wid() == source) {
                    v = QVariant::fromValue(&a);
                    comm->send(v, target, 0);
                }  else if (comm->wid() == target) {
                    comm->receive(v,source, 0);
                    b = v.value< dtkArray<qlonglong> *>();
                    for (int j = 0; j< arraySize ; ++j) {
                        QVERIFY(a[j] == (*b)[j]);
                    }
                }
            }
        }
        double elapsed = time2.elapsed();
        DTK_DISTRIBUTED_END_LOCAL;

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "throughput" << size/elapsed << "kbits/sec";
        qDebug() << "latency"    << 1000.0 * elapsed / iter << "microsec";
        DTK_DISTRIBUTED_END_GLOBAL;
    }
};

class iReceiveWork : public QRunnable
{
public:
    void run(void)
    {
        QTime time;
        dtkArray<qlonglong> a, b;
        qlonglong arraySize = 1000000;
        a.resize(arraySize);
        b.resize(arraySize);

        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();
        int iter = 5;
        qlonglong size = a.size() * iter;

        if (comm->size() <2 ) {
            qWarning() << "only one thread/process, skip IRECEIVE test";
            return;
        }

        for (int i = 0; i< arraySize ; ++i) {
            a[i] = i;
            b[i] = 0;
        }

        qRegisterMetaTypeStreamOperators<dtkArray<qlonglong>>("dtkArray<qlonglong>");
        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "****** IRECEIVE TEST ******" << iter << size;
        DTK_DISTRIBUTED_END_GLOBAL;


        DTK_DISTRIBUTED_BEGIN_LOCAL;

        QTime time2; time2.start();
        int source = 0;
        int target = 1;
        QVariant v;
        if (comm->rank() < 2) {
            for (int i =0; i< iter; ++i) {
                if (comm->wid() == source) {
                    comm->send(a.data(), a.size(), target, 0);
                }  else if (comm->wid() == target) {
                    dtkDistributedRequest *req = comm->ireceive(b.data(), b.size(),source, 0);
                    comm->wait(req);
                    for (int j = 0; j< arraySize ; ++j) {
                        QVERIFY(a[j] == b[j]);
                    }
                }
            }
        }
        double elapsed = time2.elapsed();
        DTK_DISTRIBUTED_END_LOCAL;

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "throughput" << size/elapsed << "kbits/sec";
        qDebug() << "latency"    << 1000.0 * elapsed / iter << "microsec";
        DTK_DISTRIBUTED_END_GLOBAL;
    }
};
class BroadcastWork : public QRunnable
{
public:
    void run(void)
    {
        QTime time;
        QByteArray x;
        QByteArray msg("ping broadcast");
        dtkDistributedCommunicator *comm = dtkDistributed::app()->communicator();

        int iter = 10000;
        if (comm->size() <2 ) {
            qWarning() << "only one thread/process, skip broadcast test";
            return;
        }
        qlonglong size = msg.size() * iter * (comm->size()-1)  * comm->size() / 8;

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "****** BROADCAST TEST ******" << iter * comm->size();
        DTK_DISTRIBUTED_END_GLOBAL;

        DTK_DISTRIBUTED_BEGIN_LOCAL;

        QTime time2; time2.start();
        for (qint32 source = 0; source < comm->size(); ++source) {
            for (int i =0; i< iter; ++i) {
                if (comm->wid() == source) {
                    x = msg;
                    dtkDistributed::app()->communicator()->broadcast(x, source);
                }  else {
                    dtkDistributed::app()->communicator()->broadcast(x, source);
                    QVERIFY(x == msg);
                }
            }
        }
        double elapsed = time2.elapsed();
        DTK_DISTRIBUTED_END_LOCAL;

        DTK_DISTRIBUTED_BEGIN_GLOBAL;
        qDebug() << "throughput" << size/elapsed << "kbits/sec";
        qDebug() << "latency"    << 1000.0 * elapsed / (iter * comm->size()) << "microsec";
        DTK_DISTRIBUTED_END_GLOBAL;
    }
};

namespace communicator_send_test
{
    void runAll(QString type)
    {
        dtkDistributed::policy()->setType(type);

        while (dtkDistributed::policy()->hosts().size() < 2)
            dtkDistributed::policy()->addHost("localhost");

        PingPongWork           work;
        BroadcastWork     bcastwork;
        iReceiveWork   ireceiveWork;
        SendVariantWork variantWork;
        ReduceWork       reduceWork;
        GatherWork       gatherWork;

        dtkDistributed::spawn();
        dtkDistributed::exec(&work);
        dtkDistributed::exec(&bcastwork);
        dtkDistributed::exec(&ireceiveWork);
        dtkDistributed::exec(&variantWork);
        dtkDistributed::exec(&reduceWork);
        dtkDistributed::exec(&gatherWork);
        /* dtkDistributed::policy()->communicator()->run(reduceWork, &ReduceWork::run); */
        dtkDistributed::unspawn();

    }
}
