/* dtkComposerMachineState.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:12:24 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:21:17 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 155
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerMachineState.h"

class dtkComposerMachineStatePrivate
{
public:
};

dtkComposerMachineState::dtkComposerMachineState(dtkComposerMachineState *parent) : QState(parent), d(new dtkComposerMachineStatePrivate)
{

}

dtkComposerMachineState::~dtkComposerMachineState(void)
{
    delete d;

    d = NULL;
}
