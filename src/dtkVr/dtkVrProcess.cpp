/* dtkVrProcess.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb 10 21:11:31 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 11:17:50 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 135
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkVrProcess.h"
#include "dtkVrSlave.h"

#include <dtkCore/dtkLog.h>

#include <dtkDistributed/dtkDistributedCommunicator.h>

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
    char running;

    dtkDistributedCommunicator *communicator;
};

dtkVrProcess::dtkVrProcess(dtkDistributedCommunicator *communicator) : d(new dtkVrProcessPrivate)
{
    d->communicator = communicator;
}

dtkVrProcess::~dtkVrProcess(void)
{

}

void dtkVrProcess::show(bool fullscreen)
{
    if (!this->rank())
        return;

    if (!fullscreen) {
        dynamic_cast<dtkVrSlave *>(this)->show();
        dynamic_cast<dtkVrSlave *>(this)->resize(500, 320);
        dynamic_cast<dtkVrSlave *>(this)->move(
            this->rank()-1 == 3 ? 500 : (this->rank()-1)*500,
            this->rank()-1 == 3 ? 350 : 0);
    } else {
        dynamic_cast<dtkVrSlave *>(this)->showFullScreen();
    }
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
        qApp->processEvents(QEventLoop::AllEvents, 10);
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
    return d->communicator->rank();
}

int dtkVrProcess::size(void) const
{
    return d->communicator->size();
}

bool dtkVrProcess::running(void)
{
    return d->running ? (++(d->running) < 3) : true;
}

void dtkVrProcess::broadcast(void)
{
    char status[1]; status[0] = d->running;

    d->communicator->broadcast(&status, 1, dtkDistributedCommunicator::dtkDistributedCommunicatorChar, 0);

    d->running = status[0];
}

void dtkVrProcess::synchronize(void)
{
    d->communicator->barrier();
}
