/* dtkComposerNodeControl.cpp ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  4 09:52:34 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 37
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerNodeControl.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:
    QList<dtkComposerTransmitterProxyLoop *>  input_twins;
    QList<dtkComposerTransmitterProxyLoop *> output_twins;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControl::dtkComposerNodeControl(void) : dtkComposerNode(), d(new dtkComposerNodeControlPrivate)
{

}

dtkComposerNodeControl::~dtkComposerNodeControl(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeControl::appendInputTwin(dtkComposerTransmitterProxyLoop *twin)
{
    if (!d->input_twins.contains(twin))
        d->input_twins << twin;
}

void dtkComposerNodeControl::removeInputTwin(dtkComposerTransmitterProxyLoop *twin)
{
    d->input_twins.removeOne(twin);
}

void dtkComposerNodeControl::appendOutputTwin(dtkComposerTransmitterProxyLoop *twin)
{
    if (!d->output_twins.contains(twin))
        d->output_twins << twin;
}

void dtkComposerNodeControl::removeOutputTwin(dtkComposerTransmitterProxyLoop *twin)
{
    d->output_twins.removeOne(twin);
}

QList<dtkComposerTransmitterProxyLoop *> dtkComposerNodeControl::inputTwins(void)
{
    return d->input_twins;
}

QList<dtkComposerTransmitterProxyLoop *> dtkComposerNodeControl::outputTwins(void)
{
    return d->output_twins;
}

void dtkComposerNodeControl::setInputs(void)
{

}

void dtkComposerNodeControl::setOutputs(void)
{

}

void dtkComposerNodeControl::setVariables(void)
{

}

int dtkComposerNodeControl::selectBranch(void)
{
    return -1;
}

void dtkComposerNodeControl::begin(void)
{

}

void dtkComposerNodeControl::end(void)
{

}
