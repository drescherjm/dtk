/* @(#)dtkComposerEvaluatorSlave.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/06 14:25:39
 * Version: $Id$
 * Last-Updated: lun. mai 21 09:08:22 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 223
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
    dtkComposerScene     *scene;
    dtkComposerStack     *stack;
    dtkComposerGraph     *graph;
    dtkComposerFactory   *factory;
    dtkComposerReader    *reader;
    dtkComposerEvaluator *evaluator;

public:
    QUrl server;
    int  count;
};

dtkComposerEvaluatorSlave::dtkComposerEvaluatorSlave(void) : dtkDistributedSlave(), d(new dtkComposerEvaluatorSlavePrivate)
{
    d->scene     = new dtkComposerScene;
    d->factory   = new dtkComposerFactory;
    d->stack     = new dtkComposerStack;
    d->evaluator = new dtkComposerEvaluator;
    d->reader    = new dtkComposerReader;
    d->graph     = new dtkComposerGraph;

    d->scene->setFactory(d->factory);
    d->scene->setStack(d->stack);
    d->scene->setGraph(d->graph);

    d->evaluator->setGraph(d->graph);

    d->reader->setFactory(d->factory);
    d->reader->setScene(d->scene);
    d->reader->setGraph(d->graph);
    d->count = 0;
}

dtkComposerEvaluatorSlave::~dtkComposerEvaluatorSlave(void)
{
    delete d->communicator_i;
    delete d->scene;
    delete d->stack;
    delete d->graph;
    delete d->factory;
    delete d->reader;
    delete d->evaluator;
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
    bool new_composition;

    if ( rank == 0) {

        dtkDebug() << "connect to server" << d->server;
        if (!this->isConnected()) {
            this->connect(d->server);
            if (this->isConnected()) {
                dtkDebug() << "connected, send our jobid to server" << this->jobId();
                dtkDistributedMessage *msg = new dtkDistributedMessage(dtkDistributedMessage::SETRANK,this->jobId(),rank);
                this->communicator()->socket()->sendRequest(msg);
                delete msg;
            } else  {
                dtkFatal() << "Can't connect to server" << d->server;
                return 1;
            }
        }

        QString composition;

        dtkDebug() << "Wait for composition from controller " ;

        if (this->communicator()->socket()->bytesAvailable() > 10) {
            dtkInfo() << "data already available, try to parse composition " << this->communicator()->socket()->bytesAvailable();
        } else if (!this->communicator()->socket()->waitForReadyRead(600000)) {
            dtkFatal() << "No data received from server after 10mn, abort " ;
            return 1;
        } else
            dtkDebug() << "Ok, data received, parse" ;

        dtkDistributedMessage *msg = this->communicator()->socket()->parseRequest();
        if (msg->type() == "xml") {
            new_composition = true;
            composition = QString(msg->content());
        } else if (msg->type() == "not-modified") { // reuse the old composition
            new_composition = false;
        } else {
            dtkFatal() << "Bad composition type, abort" << msg->type() << msg->content();
            return 1;
        }

        if (new_composition && composition.isEmpty()) {
            dtkFatal() << "Empty composition, abort" ;
            return 1;
        }

        dtkDebug() << "got composition from controller:" << composition;
        if (new_composition) {
            dtkDebug() << "new composition";
            if  (size > 1) {
                dtkDebug() << "send composition to our slaves";
                for (int i=1; i< size; i++) {
                    d->communicator_i->send(composition,i,0);
                }
            }
            dtkDebug() << "parse composition" ;
            d->reader->readString(composition);
        } else {
            dtkInfo() << "composition hasn't changed";
            for (int i=1; i< size; i++)
                d->communicator_i->send(QString("rerun"),i,0);
        }
        if (new_composition) {
            if (dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(d->scene->root()->nodes().first()->wrapee())) {
                remote->setSlave(this);
                remote->setJob(this->jobId());
                remote->setCommunicator(d->communicator_i);
            } else {
                dtkFatal() <<  "Can't find remote node in composition, abort";
                return 1;
            }
        }
        dtkDebug() << "run composition" ;
        d->evaluator->run();

    } else {
        QString composition;
        d->communicator_i->receive(composition,0,0);

        if (composition != "rerun") {
            dtkDebug() << "new/changed composition, read" ;
            d->reader->readString(composition);
        } else
            dtkDebug() << "reuse composition" ;

        if (dtkComposerNodeRemote *remote = dynamic_cast<dtkComposerNodeRemote *>(d->scene->root()->nodes().first()->wrapee())) {
            remote->setSlave(this);
            remote->setJob(this->jobId());
            remote->setCommunicator(d->communicator_i);
            dtkDebug() << "run composition" ;
            d->evaluator->run();
        } else {
            dtkFatal() <<  "Can't find remote node in composition, abort";
            return 1;
        }
    }

    return 0;
}
