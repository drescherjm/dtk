/* dtkComposerMachineState.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 11:13:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 18:21:01 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERMACHINESTATE_H
#define DTKCOMPOSERMACHINESTATE_H

#include <QtCore>

class dtkComposerMachineStatePrivate;

class dtkComposerMachineState : public QState
{
    Q_OBJECT

public:
             dtkComposerMachineState(dtkComposerMachineState *parent = 0);
    virtual ~dtkComposerMachineState(void);

protected:
    dtkComposerMachineStatePrivate *d;
};

#endif
