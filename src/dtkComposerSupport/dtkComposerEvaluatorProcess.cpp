/* dtkComposerEvaluatorProcess.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2013/10/07 10:25:39
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerEvaluator.h"
#include "dtkComposerEvaluatorProcess.h"
#include "dtkComposerFactory.h"
#include "dtkComposerGraph.h"
#include "dtkComposerReader.h"
#include "dtkComposerScene.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerStack.h"
#include "dtkComposerNodeSpawn.h"

#include <dtkDistributedSupport/dtkDistributedCommunicator.h>

#include <dtkLog/dtkLog>

class dtkComposerEvaluatorProcessPrivate
{
public:
    dtkDistributedCommunicator *comm;
    dtkDistributedCommunicator *parent_comm;

public:
    QString application;

public:
    dtkComposerScene     *scene;
    dtkComposerStack     *stack;
    dtkComposerGraph     *graph;
    dtkComposerFactory   *factory;
    dtkComposerReader    *reader;
    dtkComposerEvaluator *evaluator;

};

dtkComposerEvaluatorProcess::dtkComposerEvaluatorProcess(void) : QObject(), d(new dtkComposerEvaluatorProcessPrivate)
{
    d->scene     = new dtkComposerScene;
    d->stack     = new dtkComposerStack;
    d->evaluator = new dtkComposerEvaluator;
    d->reader    = new dtkComposerReader;
    d->graph     = new dtkComposerGraph;

    d->factory   = NULL;

    d->scene->setStack(d->stack);
    d->scene->setGraph(d->graph);

    d->evaluator->setGraph(d->graph);
    d->evaluator->setNotify(false);

    d->reader->setScene(d->scene);
    d->reader->setGraph(d->graph);
}

dtkComposerEvaluatorProcess::~dtkComposerEvaluatorProcess(void)
{
    delete d->scene;
    delete d->stack;
    delete d->graph;
    delete d->reader;
    delete d->evaluator;
    delete d;

    d = NULL;
}

void dtkComposerEvaluatorProcess::setFactory(dtkComposerFactory *factory)
{
    d->factory = factory;
    d->scene->setFactory(d->factory);
    d->reader->setFactory(d->factory);
}

void dtkComposerEvaluatorProcess::setApplication(QString application)
{
    d->application = application;
}

void dtkComposerEvaluatorProcess::setInternalCommunicator(dtkDistributedCommunicator *communicator)
{
    d->comm = communicator;
}

void dtkComposerEvaluatorProcess::setParentCommunicator(dtkDistributedCommunicator *communicator)
{
    d->parent_comm = communicator;
}

int dtkComposerEvaluatorProcess::exec(void)
{

    if (!d->factory) {
        dtkCritical() << "No factory set ! abort process execution";
        return 1;
    }

    int rank = d->comm->rank();
    int size = d->comm->size();
    bool new_composition;

    QByteArray data;

    d->parent_comm->broadcast(data,0);

    dtkDebug() << "Ok, composition received, parse" ;

    QString composition(data);

    if (composition == "not-modified") {
        dtkInfo() << "composition hasn't changed";
        new_composition = false;
    } else {
        new_composition = true;
    }

    if (new_composition && composition.isEmpty()) {
        dtkCritical() << "Empty composition, abort" ;
        return 1;
    }

    if (new_composition) {
        dtkDebug() << "parse composition" ;
        d->reader->readString(composition);

        if (dtkComposerNodeSpawn *spawn = dynamic_cast<dtkComposerNodeSpawn *>(d->scene->root()->nodes().first()->wrapee())) {
            spawn->setCommunicator(d->parent_comm);
            spawn->setInternalCommunicator(d->comm);
            spawn->setApplication(d->application);
        } else {
            dtkCritical() <<  "Can't find spawn node in composition, abort";
            return 1;
        }
    }
    dtkDebug() << "run composition" ;
    d->evaluator->run();
    dtkDebug() << "finished" ;

    return 0;
}
