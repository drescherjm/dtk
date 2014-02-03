/* dtkComposerNodeLeafProcess.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Thu Jun 28 14:08:54 2012 (+0200)
 * Version: $Id$
 * Last-Updated: ven. nov.  8 16:17:19 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 123
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
    dtkAbstractProcess *old_process;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLeafProcess implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeLeafProcess::dtkComposerNodeLeafProcess(void) : dtkComposerNodeLeaf(), d(new dtkComposerNodeLeafProcessPrivate)
{
    d->old_process = NULL;
}

dtkComposerNodeLeafProcess::~dtkComposerNodeLeafProcess(void)
{
    if (d->old_process)
        delete d->old_process;

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
    return (this->currentImplementation() != implementation);
}

QString dtkComposerNodeLeafProcess::currentImplementation(void) const
{
    if (this->process())
        return this->process()->identifier();

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
    if (implementation.isEmpty() || implementation == "Choose implementation")
        return NULL;

    if (implementation == "default")
        const_cast<QString&>(implementation) = this->abstractProcessType();
    
    if (!this->process()) {
        this->setProcess(dtkAbstractProcessFactory::instance()->create(implementation));
    } else if (this->process()->identifier() != implementation) {
        this->setProcess(dtkAbstractProcessFactory::instance()->create(implementation));
    }

    if (d->old_process != this->process()) {
        if (d->old_process) {
            delete d->old_process;
        }
        d->old_process = this->process();
    }

    return this->process();
}

void dtkComposerNodeLeafProcess::clearProcess(void)
{
    dtkAbstractProcess *p = this->process();
    if (p)
        delete p;
    this->setProcess(NULL);
}
