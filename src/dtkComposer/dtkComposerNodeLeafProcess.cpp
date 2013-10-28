/* dtkComposerNodeLeafProcess.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:08:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: ven. oct. 25 15:51:09 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 49
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
    dtkAbstractProcess *old_process;

    bool implementation_has_changed;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcess implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeafProcess::dtkComposerNodeLeafProcess(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLeafProcessPrivate)
{
    d->process = NULL;
    d->old_process = NULL;
    d->implementation_has_changed = false;
}

dtkComposerNodeLeafProcess::~dtkComposerNodeLeafProcess(void)
{
    if (d->process)
        delete d->process;

    if (d->old_process)
        delete d->old_process;

    d->process = NULL;
    d->old_process = NULL;

    delete d;

    d = NULL;
}

bool dtkComposerNodeLeafProcess::enableDefaultImplementation(void) const
{
    return false;
}

bool dtkComposerNodeLeafProcess::implementationHasChanged(const QString& implementation) const
{
    return (d->implementation_has_changed && implementation != d->process->identifier());
}

QString dtkComposerNodeLeafProcess::currentImplementation(void) const
{
    if (d->process)
        return d->process->identifier();

    return QString();
}

QStringList dtkComposerNodeLeafProcess::implementations(void)
{
    QStringList implementations;
    if (this->enableDefaultImplementation())
        implementations << "default";
    QStringList all_implementations = dtkAbstractProcessFactory::instance()->implementations(this->abstractProcessType());

    for (int i = 0; i < all_implementations.count(); ++i)
        implementations << all_implementations.at(i);

    return implementations;
}

dtkAbstractProcess *dtkComposerNodeLeafProcess::createProcess(const QString& implementation)
{
    if (d->old_process)
        delete d->old_process;

    d->implementation_has_changed = false;

    if (implementation.isEmpty() || implementation == "Choose implementation")
        return NULL;

    if (implementation == "default")
        const_cast<QString&>(implementation) = this->abstractProcessType();

    if (!d->process) {
        d->process = dtkAbstractProcessFactory::instance()->create(implementation);

        d->implementation_has_changed = true;

    } else if (d->process->identifier() != implementation) {
        // since createProcess can be executed while the evaluator
        // thread is running the update() method of d->process, we
        // can't delete the object now.  We will delete object next
        // time the implementation changes (we could use mutex
        // instead)
        d->old_process = d->process;

        d->process = dtkAbstractProcessFactory::instance()->create(implementation);

        d->implementation_has_changed = true;

    }

    return d->process;
}

dtkAbstractProcess *dtkComposerNodeLeafProcess::process(void)
{
    return d->process;
}
