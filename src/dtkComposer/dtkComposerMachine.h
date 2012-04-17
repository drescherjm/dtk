/* dtkComposerMachine.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 10:58:55 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jan 31 17:56:20 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERMACHINE_H
#define DTKCOMPOSERMACHINE_H

#include <QtCore>
#include <QtGui>

class dtkComposerMachinePrivate;

class dtkComposerMachine : public QStateMachine
{
    Q_OBJECT

public:
     dtkComposerMachine(QObject *parent = 0);
    ~dtkComposerMachine(void);

private:
    dtkComposerMachinePrivate *d;
};

#endif
