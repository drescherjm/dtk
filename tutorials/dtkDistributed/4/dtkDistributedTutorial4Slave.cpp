/* dtkDistributedTutorial4Slave.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:26:49 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep 14 15:59:45 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 48
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedTutorial4Slave.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>

class dtkDistributedTutorial4SlavePrivate
{
public:
    int count;
};

dtkDistributedTutorial4Slave::dtkDistributedTutorial4Slave(void) : dtkDistributedSlave(), d(new dtkDistributedTutorial4SlavePrivate)
{
    d->count = 0;
}

dtkDistributedTutorial4Slave::~dtkDistributedTutorial4Slave(void)
{
    delete d;

    d = NULL;
}

void dtkDistributedTutorial4Slave::setCount(int count)
{
    d->count = count;
}

int dtkDistributedTutorial4Slave::exec(void)
{
#if defined(DTK_HAVE_MPI)
    dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorMpi;
#else
    dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorTcp;
#endif
    communicator->initialize();

    int rank = communicator->rank();
    int size = communicator->size();

    dtkAbstractData *m_array = dtkAbstractDataFactory::instance()->create("dtkDataArray");
    dtkAbstractData *s_array = dtkAbstractDataFactory::instance()->create("dtkDataArray");

    dtkAbstractProcess *summer = dtkAbstractProcessFactory::instance()->create("dtkProcessArray");

    if(size > d->count/2) {
        
        qDebug() << "Too many slaves. Some would not perform any computation. For count" << d->count << "use at most" << d->count/2 << "processes";
        
        goto finalize;
    }

    if(!m_array && !s_array) {
        qDebug() << "No dtkDataArray implementation found.";
        return 0;
    }

    if(!summer) {
        qDebug() << "No dtkProcessArray implementation found.";
        return 0;
    }

    if(!rank) {

        int average = ceil(double(d->count)/double(size));

        m_array->setMetaData("count", QString::number(d->count));

        for(int slave = 1; slave < size; slave++) {

            int start =   (slave)*average;
            int   end = (1+slave)*average;

            if (end > d->count)
                end = d->count;

            int send = end-start;

            communicator->send(                                      &send,    1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);
            communicator->send(static_cast<int *>(m_array->data()) + start, send, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);
        }

        int         sum = 0;
        int partial_sum = 0;
        
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

        this->write(QByteArray::number(sum));
        
// /////////////////////////////////////////////////////////////////


    } else {

        int recv;

        communicator->receive(          &recv,    1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);

        s_array->setMetaData("count", QString::number(recv));

        communicator->receive(s_array->data(), recv, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);

        long partial_sum = 0;

        summer->setInput(s_array);
        
        partial_sum = summer->run();

        communicator->send(&partial_sum, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorLong, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorReceive);
    }

finalize:
    delete m_array;
    delete s_array;

    delete summer;

    communicator->uninitialize();

    return DTK_SUCCEED;
}
