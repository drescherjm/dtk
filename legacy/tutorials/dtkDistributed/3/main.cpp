/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Sep 12 09:58:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Nov 15 11:33:06 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 82
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

#include <dtkConfig.h>

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkPluginManager.h>

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
// Initialize dtk plugin manager
// /////////////////////////////////////////////////////////////////

    dtkPluginManager::instance()->initialize();

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

    dtkAbstractData *m_array = dtkAbstractDataFactory::instance()->create("dtkDataArray");
    dtkAbstractData *s_array = dtkAbstractDataFactory::instance()->create("dtkDataArray");

    dtkAbstractProcess *summer = dtkAbstractProcessFactory::instance()->create("dtkProcessArray");

    if(size > count/2) {
        
        qDebug() << "Too many slaves. Some would not perform any computation. For count" << count << "use at most" << count/2 << "processes";
        
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

// /////////////////////////////////////////////////////////////////
// Root
// /////////////////////////////////////////////////////////////////

    if(!rank) {

        int average = ceil(double(count)/double(size));

// /////////////////////////////////////////////////////////////////
// Root - initialize data
// /////////////////////////////////////////////////////////////////

        m_array->setMetaData("count", QString::number(count));

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

            communicator->send(                                      &send,    1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);
            communicator->send(static_cast<int *>(m_array->data()) + start, send, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, slave, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);
        }

// /////////////////////////////////////////////////////////////////
// Root - compute partial sum
// /////////////////////////////////////////////////////////////////

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

        communicator->receive(          &recv,    1, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);

        s_array->setMetaData("count", QString::number(recv));

        communicator->receive(s_array->data(), recv, dtkDistributedCommunicator::dtkDistributedCommunicatorInt, 0, dtkDistributedCommunicator::dtkDistributedCommunicatorSend);

// /////////////////////////////////////////////////////////////////
// Slave - compute the partial sum
// /////////////////////////////////////////////////////////////////

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

// /////////////////////////////////////////////////////////////////
// Uninitialize dtk plugin manager
// /////////////////////////////////////////////////////////////////

    dtkPluginManager::instance()->uninitialize();

    return 0;
}
