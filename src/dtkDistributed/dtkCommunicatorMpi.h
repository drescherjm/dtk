/* dtkCommunicatorMpi.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:50:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 16:52:48 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMMUNICATORMPI_H
#define DTKCOMMUNICATORMPI_H

#include "dtkAbstractCommunicator.h"

class dtkCommunicatorMpiPrivate;

class dtkCommunicatorMpi : public dtkAbstractCommunicator
{
    Q_OBJECT

public:
     dtkCommunicatorMpi(void);
    ~dtkCommunicatorMpi(void);

private:
    dtkCommunicatorMpiPrivate *d;
};

#endif
