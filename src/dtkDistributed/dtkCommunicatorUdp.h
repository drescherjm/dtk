/* dtkCommunicatorUdp.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:50:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 15 21:10:38 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMMUNICATORUDP_H
#define DTKCOMMUNICATORUDP_H

#include "dtkAbstractCommunicator.h"

class dtkCommunicatorUdpPrivate;

class DTKDISTRIBUTED_EXPORT dtkCommunicatorUdp : public dtkAbstractCommunicator
{
    Q_OBJECT

public:
     dtkCommunicatorUdp(void);
    ~dtkCommunicatorUdp(void);

private:
    dtkCommunicatorUdpPrivate *d;
};

#endif
