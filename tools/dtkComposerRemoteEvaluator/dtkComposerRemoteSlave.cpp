/* @(#)dtkComposerRemoteSlave.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/06 14:25:39
 * Version: $Id$
 * Last-Updated: ven. avril  6 18:51:53 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 84
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerRemoteSlave.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>

#include "dtkComposer/dtkComposerEvaluator.h"
#include "dtkComposer/dtkComposerReader.h"

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>

#include <dtkLog/dtkLog.h>

class dtkComposerRemoteSlavePrivate
{
public:
    dtkDistributedCommunicator *communicator_i;

public:
    QUrl server;
    int  count;
};

dtkComposerRemoteSlave::dtkComposerRemoteSlave(void) : dtkDistributedSlave(), d(new dtkComposerRemoteSlavePrivate)
{
    d->count = 0;
}

dtkComposerRemoteSlave::~dtkComposerRemoteSlave(void)
{
    delete d->communicator_i;
    delete d;

    d = NULL;
}

void dtkComposerRemoteSlave::setCount(int count)
{
    d->count = count;
}

void dtkComposerRemoteSlave::setServer(QUrl server)
{
    d->server = server;
}

void dtkComposerRemoteSlave::setInternalCommunicator(dtkDistributedCommunicator *communicator)
{
    d->communicator_i = communicator;
}

int dtkComposerRemoteSlave::exec(void)
{

    int rank = d->communicator_i->rank();
    int size = d->communicator_i->size();
    dtkDebug() << "communicator size is" << size;
    dtkDebug() << "our rank is" << rank;

    dtkComposerReader *reader;
    reader = new dtkComposerReader;
    dtkComposerEvaluator *evaluator;
    evaluator = new dtkComposerEvaluator;

    // reader->setFactory(factory);
    // reader->setScene(scene);
    // reader->setGraph(graph);

    if ( rank == 0) {

        dtkDebug() << "connect to server" << d->server;
        this->connect(d->server);

        if (this->isConnected()) {
            dtkDebug() << "connected, send our jobid to server" << this->jobId();
            this->communicator()->socket()->sendRequest(new dtkDistributedMessage(dtkDistributedMessage::SETRANK,this->jobId(),rank));
        } else  {
            dtkFatal() << "Can't connect to server" << d->server;
            return 1;
        }

        QString composition;

        dtkDebug() << "Wait for composition from controller " ;

        this->communicator()->receive(composition, dtkDistributedMessage::CONTROLLER_RANK, 0);
        if (composition.isEmpty()) {
            dtkFatal() << "Empty composition, abort" ;
            return 1;
        }

        dtkDebug() << "got composition from controller:" << composition;

        if  (size > 1) {
            for (int i=1; i< size; i++) {
                d->communicator_i->send(composition,i,0);
            }
        }

        reader->readString(composition);
        evaluator->run();

    } else {
        QString composition;
        d->communicator_i->receive(composition,0,0);
        reader->readString(composition);
        evaluator->run();
    }

}
