/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar 26 14:42:09 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 33
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeControl.h"
#include "dtkComposerTransmitterVariant.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlPrivate definition
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:    
    QList<dtkComposerTransmitterVariant *>  input_twins;
    QList<dtkComposerTransmitterVariant *> output_twins;
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

void dtkComposerNodeControl::appendInputTwin(dtkComposerTransmitterVariant *twin)
{
    if (!d->input_twins.contains(twin))
        d->input_twins << twin;
}

void dtkComposerNodeControl::removeInputTwin(dtkComposerTransmitterVariant *twin)
{
    d->input_twins.removeOne(twin);
}

void dtkComposerNodeControl::appendOutputTwin(dtkComposerTransmitterVariant *twin)
{
    if (!d->output_twins.contains(twin))
        d->output_twins << twin;
}

void dtkComposerNodeControl::removeOutputTwin(dtkComposerTransmitterVariant *twin)
{
    d->output_twins.removeOne(twin);
}

QList<dtkComposerTransmitterVariant *> dtkComposerNodeControl::inputTwins(void)
{
    return d->input_twins;
}

QList<dtkComposerTransmitterVariant *> dtkComposerNodeControl::outputTwins(void)
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
