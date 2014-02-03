/* dtkComposerMachine.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:10:33 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 17:56:12 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerMachine.h"

class dtkComposerMachinePrivate
{
public:

};

dtkComposerMachine::dtkComposerMachine(QObject *parent) : QStateMachine(parent), d(new dtkComposerMachinePrivate)
{

}

dtkComposerMachine::~dtkComposerMachine(void)
{
    delete d;
    
    d = NULL;
}
