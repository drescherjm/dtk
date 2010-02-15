/* dtkVrProcess.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:11:31 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:17:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 93
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrProcess.h"

#include <QtGui>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

void dtk_atomize(const QVector3D& vector, double *coordinates)
{
    coordinates[0] = vector.x();
    coordinates[1] = vector.y();
    coordinates[2] = vector.z();
}

void dtk_atomize(const QQuaternion& quaternion, double *coordinates)
{
    coordinates[0] = quaternion.scalar();
    coordinates[1] = quaternion.x();
    coordinates[2] = quaternion.y();
    coordinates[3] = quaternion.z();
}

// /////////////////////////////////////////////////////////////////
// dtkVrProcess
// /////////////////////////////////////////////////////////////////

class dtkVrProcessPrivate
{
public:
    int rank;
    int size;

    char running;
};

dtkVrProcess::dtkVrProcess(void) : d(new dtkVrProcessPrivate)
{
    // d->rank = MPI::COMM_WORLD.Get_rank(); // Replace with dtkDistributed
    // d->size = MPI::COMM_WORLD.Get_size(); // Replace with dtkDistributed
}

dtkVrProcess::~dtkVrProcess(void)
{

}

void dtkVrProcess::start(void)
{
    d->running = 0;

    this->initialize();
    this->synchronize();
    this->broadcast();

    while(this->running()) {
        this->broadcast();
        this->process();
        this->synchronize();
    }

    this->uninitialize();
}

void dtkVrProcess::stop(void)
{
    d->running++;
}

int dtkVrProcess::rank(void) const
{
    return d->rank;
}

int dtkVrProcess::size(void) const
{
    return d->size;
}

bool dtkVrProcess::running(void)
{
    return d->running ? (++(d->running) < 3) : true;
}

void dtkVrProcess::broadcast(void)
{
    char status[1]; status[0] = d->running;

    // MPI::COMM_WORLD.Bcast(&status, 1, MPI_CHAR, 0); // Replace with dtk distributed

    d->running = status[0];
}

void dtkVrProcess::synchronize(void)
{
    // MPI::COMM_WORLD.Barrier(); // Replace with dtkDistributed
}
