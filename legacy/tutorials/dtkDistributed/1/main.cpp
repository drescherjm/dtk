/* main.cpp --- 
 * 
 * Author: 
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep  6 14:15:35 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Nov 15 10:15:04 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 182
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

#include <mpi.h>

#define SEND_TAG 2001
#define RECV_TAG 2002

int main(int argc, char **argv)
{
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

    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

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

            MPI::COMM_WORLD.Send(          &send,    1, MPI_INT, slave, SEND_TAG);
            MPI::COMM_WORLD.Send(&m_array[start], send, MPI_INT, slave, SEND_TAG);
        }

// /////////////////////////////////////////////////////////////////
// Root - compute partial sum
// /////////////////////////////////////////////////////////////////

        long         sum = 0;
        long partial_sum = 0;
            
        for(int i = 0; i < average; i++)
            sum += m_array[i];
        
        qDebug() << "Rank" << rank << "has partial sum" << sum;
        
// /////////////////////////////////////////////////////////////////
// Root - collect slaves partial sums
// /////////////////////////////////////////////////////////////////

        for(int slave = 1; slave < size; slave++) {

            MPI::COMM_WORLD.Recv(&partial_sum, 1, MPI_LONG, slave, RECV_TAG);

            qDebug() << "Rank" << slave << "has partial sum" << partial_sum;

            sum += partial_sum;
        }

        qDebug() << "Sum is" << sum;

    } else {

// /////////////////////////////////////////////////////////////////
// Slave
// /////////////////////////////////////////////////////////////////

        int recv;

        MPI::COMM_WORLD.Recv(   &recv,    1, MPI_INT, 0, SEND_TAG);
        MPI::COMM_WORLD.Recv(&s_array, recv, MPI_INT, 0, SEND_TAG);

// /////////////////////////////////////////////////////////////////
// Slave - compute the partial sum
// /////////////////////////////////////////////////////////////////

        long partial_sum = 0;

        for(int i = 0; i < recv; i++)
            partial_sum += s_array[i];

        MPI::COMM_WORLD.Send(&partial_sum, 1, MPI_LONG, 0, RECV_TAG);
    }

finalize:
    MPI::Finalize();

    return 0;
}
