/* dtkComposerMachine.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 10:58:55 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May 14 14:26:05 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 37
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERMACHINE_H
#define DTKCOMPOSERMACHINE_H

#include "dtkComposerExport.h"

#include <QtCore>
#include <QtGui>

class dtkComposerMachinePrivate;

class DTKCOMPOSER_EXPORT dtkComposerMachine : public QStateMachine
{
    Q_OBJECT

public:
     dtkComposerMachine(QObject *parent = 0);
    ~dtkComposerMachine(void);

private:
    dtkComposerMachinePrivate *d;
};

#endif
