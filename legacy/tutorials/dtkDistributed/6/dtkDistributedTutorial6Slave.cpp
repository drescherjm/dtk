/* dtkDistributedTutorial6Slave.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:26:49 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:18:53 2012 (+0200)
 *           By: tkloczko
 *     Update #: 272
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedTutorial6Slave.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>

class dtkDistributedTutorial6SlavePrivate
{
public:
    int count;
};

dtkDistributedTutorial6Slave::dtkDistributedTutorial6Slave(void) : dtkDistributedSlave(), d(new dtkDistributedTutorial6SlavePrivate)
{
    d->count = 0;
}

dtkDistributedTutorial6Slave::~dtkDistributedTutorial6Slave(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedTutorial6Slave::setCount(int count)
{
    d->count = count;
}

int dtkDistributedTutorial6Slave::exec(void)
{
#if defined(DTK_HAVE_MPI)
    dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorMpi;
#else
    dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorTcp;
#endif
    communicator->initialize();

    int rank = communicator->rank();
    int size = communicator->size();

    if (this->isConnected()) {
        this->communicator()->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::SETRANK,this->jobId(),rank));
    }

    dtkAbstractData *s_array = dtkAbstractDataFactory::instance()->create("dtkDataArray");
    dtkAbstractProcess *summer = dtkAbstractProcessFactory::instance()->create("dtkProcessArray");

    if(!s_array) {
        qDebug() << "No dtkDataArray implementation found.";
        return 0;
    }

    if(!summer) {
        qDebug() << "No dtkProcessArray implementation found.";
        return 0;
    }


    if(!rank) {

        qDebug() << "OK, initialization done, wait for array from controller";
        dtkAbstractData *m_array = dtkAbstractDataFactory::instance()->create("dtkDataArray");
        this->communicator()->receive(m_array, dtkDistributedMessage::CONTROLLER_RANK, 0);

        d->count = m_array->metadata("count").toLongLong();
        qDebug() << "count is" << d->count << "(was:)"<< m_array->metadata("count");

        int average = ceil(double(d->count)/double(size));

        for(int slave = 1; slave < size; slave++) {

            int start =   (slave)*average;
            int   end = (1+slave)*average;

            if (end > d->count)
                end = d->count;

            int send = end-start;

            s_array->setMetaData("count", QString::number(send));
            int *rawdata = reinterpret_cast<int *>(m_array->data()) + start;
            s_array->setData( rawdata );
            communicator->send(s_array,slave,0);
        }

        long         sum = 0;
        long partial_sum = 0;

        summer->setInput(m_array);
        summer->setMetaData("until", QString::number(average));
        sum += summer->run();

#if defined(DTK_HAVE_MPI)
        qDebug() << "Rank" << rank << "(" << ((dtkDistributedCommunicatorMpi *)communicator)->name() << ")" << "has partial sum" << sum;
#else
        qDebug() << "Rank" << rank << "has partial sum" << sum;
#endif

        for(int slave = 1; slave < size; slave++) {

            communicator->receive(&partial_sum, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorLong, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorReceive);

            qDebug() << "Rank" << slave << "has partial sum" << partial_sum;

            sum += partial_sum;
        }

        qDebug() << "Sum is" << sum;

// /////////////////////////////////////////////////////////////////
// Slave of rank 0 sends result to server
// /////////////////////////////////////////////////////////////////

        if (this->isConnected()) {

            QByteArray data = QByteArray::number((qlonglong)sum);

            this->communicator()->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::DATA, this->jobId(), dtkDistributedMessage::CONTROLLER_RANK ,data.size(),"text", data));

        } else
            qDebug() << "unable to send result to server: not connected ";

// /////////////////////////////////////////////////////////////////

        delete m_array;

    } else {

        // int recv;

        communicator->receive(s_array, 0, 0);

        long partial_sum = 0;

        summer->setInput(s_array);

        partial_sum = summer->run();

        communicator->send(&partial_sum, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorLong, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorReceive);
    }

    delete s_array;

    delete summer;

    if(!rank) {
        if (this->isConnected()) {
            this->communicator()->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::ENDJOB, this->jobId()));
            this->communicator()->socket()->close();
        } else
            qDebug() << "unable to send result to server: not connected ";
    }

    communicator->uninitialize();

    return DTK_SUCCEED;
}
