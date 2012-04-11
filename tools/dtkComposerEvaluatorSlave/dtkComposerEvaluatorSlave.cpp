/* @(#)dtkComposerEvaluatorSlave.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/06 14:25:39
 * Version: $Id$
 * Last-Updated: mer. avril 11 17:46:58 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 113
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include "dtkComposerEvaluatorSlave.h"

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>

#include "dtkComposer/dtkComposerEvaluator.h"
#include "dtkComposer/dtkComposerFactory.h"
#include "dtkComposer/dtkComposerGraph.h"
#include "dtkComposer/dtkComposerReader.h"
#include "dtkComposer/dtkComposerScene.h"
#include "dtkComposer/dtkComposerSceneNodeComposite.h"
#include "dtkComposer/dtkComposerStack.h"
#include "dtkComposer/dtkComposerNodeRemote.h"

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>

#include <dtkLog/dtkLog.h>

class dtkComposerEvaluatorSlavePrivate
{
public:
    dtkDistributedCommunicator *communicator_i;

public:
    QUrl server;
    int  count;
};

dtkComposerEvaluatorSlave::dtkComposerEvaluatorSlave(void) : dtkDistributedSlave(), d(new dtkComposerEvaluatorSlavePrivate)
{
    d->count = 0;
}

dtkComposerEvaluatorSlave::~dtkComposerEvaluatorSlave(void)
{
    delete d->communicator_i;
    delete d;

    d = NULL;
}

void dtkComposerEvaluatorSlave::setCount(int count)
{
    d->count = count;
}

void dtkComposerEvaluatorSlave::setServer(QUrl server)
{
    d->server = server;
}

void dtkComposerEvaluatorSlave::setInternalCommunicator(dtkDistributedCommunicator *communicator)
{
    d->communicator_i = communicator;
}

int dtkComposerEvaluatorSlave::exec(void)
{

    int rank = d->communicator_i->rank();
    int size = d->communicator_i->size();
    dtkDebug() << "communicator size is" << size;
    dtkDebug() << "our rank is" << rank;

    dtkComposerScene *scene;
    dtkComposerStack *stack;
    dtkComposerGraph *graph;
    dtkComposerFactory *factory;

    factory   = new dtkComposerFactory;
    stack     = new dtkComposerStack;
    scene     = new dtkComposerScene;
    graph     = new dtkComposerGraph;

    scene->setFactory(factory);
    scene->setStack(stack);
    scene->setGraph(graph);

    dtkComposerReader *reader;
    reader = new dtkComposerReader;
    dtkComposerEvaluator *evaluator;
    evaluator = new dtkComposerEvaluator;

    reader->setFactory(factory);
    reader->setScene(scene);
    reader->setGraph(graph);

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

//        this->communicator()->parseRequest(composition, dtkDistributedMessage::CONTROLLER_RANK, 0);
        dtkDistributedMessage *msg = this->communicator()->socket()->parseRequest();
        if (msg->type() == "xml")
            composition = QString(msg->content());
        else {
            dtkFatal() << "Bad composition type, abort" << msg->type();
            return 1;
        }

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
        if (dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(scene->root()->nodes().first()->wrapee())) {
            remote->setSlave(this);
            remote->setJob(this->jobId());
            evaluator->run();
        } else {
            dtkFatal() <<  "Can't find remote node in composition, abort";
        }

    } else {
        QString composition;
        d->communicator_i->receive(composition,0,0);
        reader->readString(composition);
        evaluator->run();
    }

}
