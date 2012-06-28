/* dtkComposerNodeLeafProcess.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:08:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jun 28 14:09:35 2012 (+0200)
 *           By: tkloczko
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeLeafProcess.h"

#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcessPrivate interface
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeafProcessPrivate
{
public:
    dtkAbstractProcess *process;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcess implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeafProcess::dtkComposerNodeLeafProcess(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLeafProcessPrivate)
{
    d->process = NULL;
}

dtkComposerNodeLeafProcess::~dtkComposerNodeLeafProcess(void)
{
    if (d->process)
        delete d->process;

    d->process = NULL;

    delete d;

    d = NULL;
}

QString dtkComposerNodeLeafProcess::currentImplementation(void)
{
    if (d->process)
        return d->process->identifier();

    return QString();
}

QStringList dtkComposerNodeLeafProcess::implementations(void)
{
    QStringList implementations;

    foreach(QString implementation, dtkAbstractProcessFactory::instance()->implementations(this->abstractProcessType()))
        implementations << implementation;

    return implementations;
}

dtkAbstractProcess *dtkComposerNodeLeafProcess::createProcess(const QString& implementation)
{
    if (implementation.isEmpty() || implementation == "Choose implementation")
        return NULL;
    
    if (!d->process) {

        d->process = dtkAbstractProcessFactory::instance()->create(implementation);

    } else if (d->process->identifier() != implementation) {

        delete d->process;

        d->process = dtkAbstractProcessFactory::instance()->create(implementation);

    }        

    return d->process;
}

dtkAbstractProcess *dtkComposerNodeLeafProcess::process(void)
{
    return d->process;
}
