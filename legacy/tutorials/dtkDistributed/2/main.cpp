/* main.cpp --- 
 * 
 * Author: 
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep  6 14:15:35 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Nov 15 11:32:28 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 219
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

#include <dtkConfig.h>

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    if(argc < 2) {
        qDebug() << "Usage:" << argv[0] << "count";
        return 0;
    }

    const int max = 100000;
    
    int count = atoi(argv[1]);

    if(count > max) {
        qDebug() << "Count is too large";
        return 0;
    }
    
// /////////////////////////////////////////////////////////////////
// Initialize distribution
// /////////////////////////////////////////////////////////////////

#if defined(DTK_HAVE_MPI)
    dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorMpi;
#else
    dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorTcp;
#endif
    communicator->initialize();

    int rank = communicator->rank();
    int size = communicator->size();

    if(size > count/2) {
        
        qDebug() << "Too many slaves. Some would not perform any computation. For count" << count << "use at most" << count/2 << "processes";
        
        goto finalize;
    }

    int m_array[max];
    int s_array[max];

// /////////////////////////////////////////////////////////////////
// Root
// /////////////////////////////////////////////////////////////////

    if(!rank) {

        int average = ceil(double(count)/double(size));

// /////////////////////////////////////////////////////////////////
// Root - initialize data
// /////////////////////////////////////////////////////////////////

        for(int i = 0; i < count; i++)
            m_array[i] = i+1;

// /////////////////////////////////////////////////////////////////
// Root - distribute data
// /////////////////////////////////////////////////////////////////

        for(int slave = 1; slave < size; slave++) {

            int start =   (slave)*average;
            int   end = (1+slave)*average;

            if (end > count)
                end = count;

            int send = end-start;

// /////////////////////////////////////////////////////////////////
// Root - send sub array size
// /////////////////////////////////////////////////////////////////

            communicator->send(          &send,    1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);
            communicator->send(&m_array[start], send, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);
        }

// /////////////////////////////////////////////////////////////////
// Root - compute partial sum
// /////////////////////////////////////////////////////////////////

        long         sum = 0;
        long partial_sum = 0;
        
        for(int i = 0; i < average; i++)
            sum += m_array[i];
        
#if defined(DTK_HAVE_MPI)
        qDebug() << "Rank" << rank << "(" << ((dtkDistributedCommunicatorMpi *)communicator)->name() << ")" << "has partial sum" << sum;
#else
        qDebug() << "Rank" << rank << "has partial sum" << sum;
#endif
        
// /////////////////////////////////////////////////////////////////
// Root - collect slaves partial sums
// /////////////////////////////////////////////////////////////////

        for(int slave = 1; slave < size; slave++) {

            communicator->receive(&partial_sum, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorLong, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorReceive);

            qDebug() << "Rank" << slave << "has partial sum" << partial_sum;
            
            sum += partial_sum;
        }

        qDebug() << "Sum is" << sum;

    } else {

// /////////////////////////////////////////////////////////////////
// Slave
// /////////////////////////////////////////////////////////////////

        int recv;

        communicator->receive(   &recv,    1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);
        communicator->receive(&s_array, recv, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);

// /////////////////////////////////////////////////////////////////
// Slave - compute the partial sum
// /////////////////////////////////////////////////////////////////

        long partial_sum = 0;

        for(int i = 0; i < recv; i++)
            partial_sum += s_array[i];

        communicator->send(&partial_sum, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorLong, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorReceive);
    }

finalize:
    communicator->uninitialize();

    return 0;
}
